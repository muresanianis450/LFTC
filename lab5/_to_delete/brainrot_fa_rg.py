#!/usr/bin/env python3
"""
brainrot_fa_rg.py - Lab 4, Brainrot DSL
Finite Automata (FA) and Regular Grammars (RG) for identifiers and constants,
with the transformations  FA -> RG  and  RG -> FA.

A regular grammar here is RIGHT-LINEAR:   A -> a B  |  A -> a  |  A -> eps
(a is one terminal, A and B are non-terminals; eps only for the start symbol
when the language contains the empty string).

Usage
  python brainrot_fa_rg.py fa2rg  definitions/identifier.fa [-o out.rg]
  python brainrot_fa_rg.py rg2fa  definitions/identifier.rg [-o out.fa] [--dfa] [--min]
  python brainrot_fa_rg.py check  definitions/identifier.fa "my_var1"
  python brainrot_fa_rg.py dot    definitions/int_constant.fa [-o out.dot]   # Graphviz diagram
  python brainrot_fa_rg.py show   definitions/int_constant.rg
  python brainrot_fa_rg.py all                 # run every transformation, write results/
"""
import argparse
import glob
import os
import re
import sys
from functools import lru_cache

EPS = "eps"

# ----------------------------------------------------------------------------
#  Symbols: a symbol written in a definition file is a single character
#  (a, 0, '-', '"', ' ') or a class such as [A-Za-z0-9_].
# ----------------------------------------------------------------------------
TOKEN_RE = re.compile(r"\[(?:\\.|[^\]\\])+\]|'[^']'|->|\||[^\s|]+")


def expand_symbol(tok):
    """Token -> set of single characters."""
    if len(tok) > 2 and tok[0] == "[" and tok[-1] == "]":
        body, chars, i = tok[1:-1], set(), 0
        while i < len(body):
            c = body[i]
            if c == "\\" and i + 1 < len(body):
                chars.add(body[i + 1])
                i += 2
            elif i + 2 < len(body) and body[i + 1] == "-":
                lo, hi = ord(c), ord(body[i + 2])
                if lo > hi:
                    raise ValueError("bad range in " + tok)
                chars.update(chr(x) for x in range(lo, hi + 1))
                i += 3
            else:
                chars.add(c)
                i += 1
        return chars
    if len(tok) == 3 and tok[0] == "'" and tok[2] == "'":
        return {tok[1]}
    if len(tok) == 1:
        return {tok}
    raise ValueError("not a symbol: " + tok)


def _group(c):
    return 0 if c.isupper() else 1 if c.islower() else 2 if c.isdigit() else 3


def _esc(c):
    return "\\" + c if c in "\\]-[" else c


def fmt_symbols(chars, reserved=()):
    """Set of characters -> compact text that expand_symbol can read back."""
    cs = sorted(chars, key=lambda c: (_group(c), c))
    if len(cs) == 1:
        c = cs[0]
        if (c.isalnum() or c == "_") and c not in reserved:
            return c
        return "'" + c + "'"
    parts, i = [], 0
    while i < len(cs):
        j = i
        while (j + 1 < len(cs) and ord(cs[j + 1]) == ord(cs[j]) + 1
               and _group(cs[j + 1]) == _group(cs[j])):
            j += 1
        if j - i >= 2:
            parts.append(_esc(cs[i]) + "-" + _esc(cs[j]))
        else:
            parts.extend(_esc(c) for c in cs[i:j + 1])
        i = j + 1
    return "[" + "".join(parts) + "]"


# ----------------------------------------------------------------------------
#  Finite automaton  M = (Q, Sigma, delta, q0, F)   (deterministic or not)
# ----------------------------------------------------------------------------
class FA:
    def __init__(self, name, states, start, finals, delta):
        self.name = name        # Name of the language, such as identifier
        self.states = list(states)      # The set Q of states, in declaration order
        self.start = start              # The start state q0
        self.finals = set(finals)       # The final states F
        self.delta = {k: set(v) for k, v in delta.items()}   # (q, char) -> {q' }, the transition function

    @property
    def alphabet(self):
        """Return the sorted list of characters that appear in transition."""
        return sorted({c for (_, c) in self.delta})

    def is_deterministic(self):
        """True if every (state,char) has exactly one target, so the FA is deterministic."""
        return all(len(v) == 1 for v in self.delta.values())

    def accepts(self, word):
        """Runs the automation, It keeps the set of current states and, for each character,
            moves to all possible next states."""
        cur = {self.start}
        for ch in word:
            cur = {p for q in cur for p in self.delta.get((q, ch), ())}
            if not cur:
                return False
        return bool(cur & self.finals)

    # ---- text form ----------------------------------------------------
    def grouped(self):
        """(q, p) -> set of chars, for compact printing."""
        g = {}
        for (q, c), ps in self.delta.items():
            for p in ps:
                g.setdefault((q, p), set()).add(c)
        return g

    def to_text(self):
        """Produces the .fa file format (name, state, start, final, transition with classes"""
        res = set(self.states)
        order = {s: i for i, s in enumerate(self.states)}
        out = ["name: " + self.name,
               "states: " + " ".join(self.states),
               "start: " + self.start,
               "final: " + " ".join(s for s in self.states if s in self.finals)]
        for (q, p), cs in sorted(self.grouped().items(),
                                 key=lambda kv: (order[kv[0][0]], order[kv[0][1]])):
            out.append("%s %s %s" % (q, fmt_symbols(cs, res), p))
        return "\n".join(out) + "\n"

    def to_dot(self):
        """Graphviz source (render with: dot -Tpng file.dot -o file.png)."""
        res = set(self.states)
        q = lambda t: t.replace("\\", "\\\\").replace('"', '\\"')
        out = ["digraph %s {" % self.name, "  rankdir=LR; node [shape=circle];",
               '  __s [shape=point]; __s -> "%s";' % self.start]
        for s in self.states:
            out.append('  "%s"%s;' % (s, " [shape=doublecircle]" if s in self.finals else ""))
        for (a, b), cs in self.grouped().items():
            lab = (next(iter(cs)) if len(cs) == 1 else fmt_symbols(cs, res))
            out.append('  "%s" -> "%s" [label="%s"];' % (a, b, q(lab)))
        out.append("}")
        return "\n".join(out) + "\n"

    def describe(self):
        """Produces the readable summary M used in the console output"""
        res = set(self.states)
        alpha = fmt_symbols(set(self.alphabet), res)
        lines = ["M = (Q, Sigma, delta, q0, F)",
                 "  Q     = {%s}" % ", ".join(self.states),
                 "  Sigma = %s  (%d symbols)" % (alpha, len(self.alphabet)),
                 "  q0    = %s" % self.start,
                 "  F     = {%s}" % ", ".join(s for s in self.states if s in self.finals),
                 "  type  = %s" % ("deterministic (DFA)" if self.is_deterministic()
                                  else "non-deterministic (NFA)"),
                 "  delta:"]
        order = {s: i for i, s in enumerate(self.states)}
        for (q, p), cs in sorted(self.grouped().items(),
                                 key=lambda kv: (order[kv[0][0]], order[kv[0][1]])):
            lines.append("    delta(%s, %s) -> %s" % (q, fmt_symbols(cs, res), p))
        return "\n".join(lines)


# ----------------------------------------------------------------------------
#  Right-linear regular grammar  G = (N, T, P, S)
#  prods[A] = list of (a, B):   (a, B) = A->aB   (a, None) = A->a   (None, None) = A->eps
# ----------------------------------------------------------------------------
class RG:
    def __init__(self, name, nts, start, prods):
        self.name = name
        self.nts = list(nts)        # The non-terminals N, in declaration order
        self.start = start          # The start symbol S
        self.prods = {a: list(v) for a, v in prods.items()} # The productions. The key is a non-terminal A and the value is a list of paird (a,B)
        for a in self.nts:
            self.prods.setdefault(a, [])

    @property
    def terminals(self):
        """Returns the sorted list of terminals T actually used in the production"""
        return sorted({a for ps in self.prods.values() for (a, _) in ps if a is not None})

    def production_count(self):
        """Counts the productions with every character written separately"""
        return sum(len(v) for v in self.prods.values())

    def derives(self, word):
        """Direct membership test by trying derivations (independent of the
        RG->FA transformation): A =>* w  iff  A->eps and w='' , A->a and w=a,
        or A->aB and w=a w' with B =>* w'."""
        @lru_cache(maxsize=None)
        def d(A, i):
            rest = len(word) - i
            for (a, B) in self.prods[A]:
                if a is None:
                    if rest == 0:
                        return True
                elif rest > 0 and word[i] == a:
                    if B is None:
                        if rest == 1:
                            return True
                    elif d(B, i + 1):
                        return True
            return False
        return d(self.start, 0)

    # ---- text form ----------------------------------------------------
    def to_text(self):
        res = set(self.nts)
        out = ["name: " + self.name,
               "nonterminals: " + " ".join(self.nts),
               "start: " + self.start]
        for A in self.nts:
            ps = self.prods[A]
            if not ps:
                continue
            by_B, only_a, eps = {}, set(), False
            for (a, B) in ps:
                if a is None:
                    eps = True
                elif B is None:
                    only_a.add(a)
                else:
                    by_B.setdefault(B, set()).add(a)
            alts = ["%s %s" % (fmt_symbols(cs, res), B) for B, cs in by_B.items()]
            if only_a:
                alts.append(fmt_symbols(only_a, res))
            if eps:
                alts.append(EPS)
            out.append("%s -> %s" % (A, " | ".join(alts)))
        return "\n".join(out) + "\n"

    def describe(self):
        res = set(self.nts)
        lines = ["G = (N, T, P, S)",
                 "  N = {%s}" % ", ".join(self.nts),
                 "  T = %s  (%d symbols)" % (fmt_symbols(set(self.terminals), res),
                                              len(self.terminals)),
                 "  S = %s" % self.start,
                 "  P (a class such as [0-9] stands for one production per symbol;"
                 " %d productions in total):" % self.production_count()]
        for ln in self.to_text().splitlines()[3:]:
            lines.append("    " + ln)
        return "\n".join(lines)


# ----------------------------------------------------------------------------
#  Reading definition files
# ----------------------------------------------------------------------------
def _clean_lines(text):
    for raw in text.splitlines():
        line = re.sub(r"(^|\s)#.*$", "", raw).strip()
        if line:
            yield line


def parse_fa(text):
    name, states, start, finals, trans = "fa", [], None, [], []
    for line in _clean_lines(text):
        if line.startswith("name:"):
            name = line[5:].strip()
        elif line.startswith("states:"):
            states = line[7:].split()
        elif line.startswith("start:"):
            start = line[6:].strip()
        elif line.startswith("final:"):
            finals = line[6:].split()
        else:
            tk = TOKEN_RE.findall(line)
            if len(tk) != 3:
                raise ValueError("bad transition line: " + line)
            trans.append(tk)
    if start not in states:
        raise ValueError("start state is not declared")
    if not set(finals) <= set(states):
        raise ValueError("a final state is not declared")
    delta = {}
    for q, sym, p in trans:
        if q not in states or p not in states:
            raise ValueError("undeclared state in: %s %s %s" % (q, sym, p))
        for c in expand_symbol(sym):
            delta.setdefault((q, c), set()).add(p)
    return FA(name, states, start, finals, delta)


def parse_rg(text):
    name, nts, start, rules = "rg", [], None, []
    for line in _clean_lines(text):
        if line.startswith("name:"):
            name = line[5:].strip()
        elif line.startswith("nonterminals:"):
            nts = line[13:].split()
        elif line.startswith("start:"):
            start = line[6:].strip()
        else:
            rules.append(line)
    if start not in nts:
        raise ValueError("start symbol is not a declared non-terminal")
    prods = {A: [] for A in nts}
    for line in rules:
        tk = TOKEN_RE.findall(line)
        if len(tk) < 3 or tk[1] != "->" or tk[0] not in nts:
            raise ValueError("bad production: " + line)
        lhs, cur = tk[0], []
        for t in tk[2:] + ["|"]:
            if t != "|":
                cur.append(t)
                continue
            if cur == [EPS]:
                if lhs != start:
                    raise ValueError("eps is allowed only for the start symbol: " + line)
                prods[lhs].append((None, None))
            elif len(cur) == 1 and cur[0] not in nts:
                prods[lhs].extend((a, None) for a in expand_symbol(cur[0]))
            elif len(cur) == 2 and cur[0] not in nts and cur[1] in nts:
                prods[lhs].extend((a, cur[1]) for a in expand_symbol(cur[0]))
            else:
                raise ValueError("not right-linear (A -> aB | a | eps): " + line)
            cur = []
    return RG(name, nts, start, prods)


def load(path):
    with open(path, encoding="utf-8") as f:
        text = f.read()
    return parse_fa(text) if path.endswith(".fa") else parse_rg(text)


# ----------------------------------------------------------------------------
#  TRANSFORMATION 1:  FA -> RG
#    non-terminals = states, S = q0
#    delta(q,a) = p          gives   q -> a p
#    delta(q,a) = p in F     also    q -> a
#    q0 in F                 gives   S -> eps  (a new start symbol is added
#                                    when q0 occurs on a right-hand side)
#  Afterwards non-productive and unreachable non-terminals are removed.
# ----------------------------------------------------------------------------
def fa_to_rg(fa, steps=None):

    # `steps` is an optional list that receives a text log of the rules applied;
    log = steps if steps is not None else []

    # One entry per state: each state becomes a non-terminal of the grammar.
    # prods[q] will hold pairs (a, B):  (a, B) = "q -> a B",  (a, None) = "q -> a",
    #                                   (None, None) = "q -> eps"
    prods = {q: [] for q in fa.states}

    # Go through every transition delta(q, c) = {p1, p2, ...}
    # (sorted only to make the output order deterministic)
    for (q, c), ps in sorted(fa.delta.items()):
        for p in sorted(ps):
            # Rule 1: the transition q --c--> p becomes the production q -> c p
            prods[q].append((c, p))
            # Rule 2: if p is a final state the word may stop right after c,
            # so we also need the production without a non-terminal: q -> c
            if p in fa.finals:
                prods[q].append((c, None))
    # Non-terminals = the states, start symbol = the start state.
    nts, start = list(fa.states), fa.start
    log.append("rule 1: every transition delta(q,a)=p gives q -> a p")
    log.append("rule 2: if p is final, delta(q,a)=p also gives q -> a")

    # Rule 3: the empty word. If the start state is final, eps belongs to the language.
    if fa.start in fa.finals:
        # Is the start state the target of some transition
        uses_start = any(B == fa.start for ps in prods.values() for (_, B) in ps)
        if uses_start:
            # Safe solution: a NEW start symbol (q0') that never appears on a right-hand side
            new = fa.start + "'"
            prods[new] = list(prods[fa.start]) + [(None, None)]
            nts.insert(0, new)
            start = new
            log.append("rule 3: q0 is final and is reused -> new start %s with %s -> eps" % (new, new))
        else:
            # The start is never reused, so adding q0 -> eps is harmless.
            prods[fa.start].append((None, None))
            log.append("rule 3: q0 is final -> %s -> eps" % fa.start)
    else:
        # The Brainrot automata end up here: q0 is not final, so no eps-production.
        log.append("rule 3: q0 is not final, so eps is not in the language (no eps-production)")
    g = RG(fa.name, nts, start, prods)
    return remove_useless(g, log)


def remove_useless(g, log=None):
    # productive: derives a terminal string
    prod_nts, changed = set(), True
    while changed:
        changed = False
        for A, ps in g.prods.items():
            if A not in prod_nts and any(B is None or B in prod_nts for (_, B) in ps):
                prod_nts.add(A)
                changed = True
    prods = {A: [(a, B) for (a, B) in ps if B is None or B in prod_nts]
             for A, ps in g.prods.items() if A in prod_nts}
    # reachable from the start symbol
    reach, todo = set(), [g.start]
    while todo:
        A = todo.pop()
        if A in reach or A not in prods:
            continue
        reach.add(A)
        todo.extend(B for (_, B) in prods[A] if B is not None)
    removed = [A for A in g.nts if A not in reach]
    if removed and log is not None:
        log.append("cleanup: removed useless non-terminals: " + ", ".join(removed))
    nts = [A for A in g.nts if A in reach]
    return RG(g.name, nts, g.start, {A: prods[A] for A in nts})


# ----------------------------------------------------------------------------
#  TRANSFORMATION 2:  RG -> FA
#    states = non-terminals + one new final state F
#    A -> a B   gives  delta(A,a) contains B
#    A -> a     gives  delta(A,a) contains F
#    A -> eps   makes A final;      F is final;   q0 = S
#  The result is in general non-deterministic.  nfa_to_dfa() (subset
#  construction) and minimize() are provided as optional second steps.
# ----------------------------------------------------------------------------
def rg_to_fa(g, steps=None):
    # Optional log of the rules applied (same idea as in fa_to_rg).
    log = steps if steps is not None else []

    # Name of the one extra state that means "the derivation is finished".
    f = "F"
    while f in g.nts:
        f += "'"
    delta = {}      # (state, char) -> set of target states
    finals = {f}    # F is always final
    # Go through every production A -> ... of the grammar.
    for A in g.nts:
        for (a, B) in g.prods[A]:
            if a is None:
                # A -> eps : the word may end in state A, so A is also final
                finals.add(A)
            else:
                # A -> a B : reading 'a' in state A moves to state B.
                # A -> a   : reading 'a' in state A moves to the final state F.
                # setdefault + add collects ALL targets of (A, a); two productions
                # with the same terminal (I -> x R and I -> x) give two targets,
                # which is why the result can be non-deterministic.
                delta.setdefault((A, a), set()).add(B if B is not None else f)
    log.append("states: every non-terminal, plus the new final state " + f)
    log.append("A -> aB gives delta(A,a) containing B;  A -> a gives delta(A,a) containing " + f)
    if any(a is None for ps in g.prods.values() for (a, _) in ps):
        log.append("A -> eps makes A a final state")
    return FA(g.name, g.nts + [f], g.start, finals, delta)


def nfa_to_dfa(nfa, rename=True):
    # Subset construction: every state of the DFA is a SET of NFA states.
    # `rename=True` gives the sets short names q0, q1, ...; otherwise they are
    # named after their content, like {R,F}.
    alphabet = nfa.alphabet

    # The DFA start state is the set containing only the NFA start state.
    # frozenset is used because normal sets cannot be dictionary keys or
    # members of another set.
    start = frozenset([nfa.start])

    # seen  : sets already discovered (so each one is processed only once)
    # order : sets in discovery order (this decides the names q0, q1, ...)
    # todo  : queue of sets whose transitions are not computed yet
    # table : the DFA transitions, (set, char) -> set
    seen, order, todo, table = {start}, [start], [start], {}

    while todo:
        S = todo.pop(0)                      # take the next unprocessed set
        for c in alphabet:
            # Union of everything reachable from ANY state of S by reading c.
            # This is where the non-determinism disappears: the several
            # targets of the NFA become ONE target set.
            T = frozenset(p for q in S for p in nfa.delta.get((q, c), ()))
            if not T:
                continue                     # no move on c: no transition (the word is rejected)
            table[(S, c)] = T
            if T not in seen:                # a new set -> a new DFA state to process later
                seen.add(T)
                order.append(T)
                todo.append(T)

    def nm(S):
        # Readable name of a set, in the NFA's state order, e.g. "{R,F}".
        return "{" + ",".join(q for q in nfa.states if q in S) + "}"

    # Give every discovered set its DFA state name.
    names = {S: ("q%d" % i if rename else nm(S)) for i, S in enumerate(order)}

    # Rewrite the table with the names; the target is wrapped in a one-element
    # set because FA.delta always maps to sets.
    delta = {(names[S], c): {names[T]} for (S, c), T in table.items()}

    # A set is final if it contains at least one final NFA state
    # (S & nfa.finals is the intersection; it is non-empty -> True).
    finals = {names[S] for S in order if S & nfa.finals}

    d = FA(nfa.name, [names[S] for S in order], names[start], finals, delta)

    # Remember which NFA states each DFA state stands for (used to explain
    # the construction, e.g. q1 = {R,F}).
    d.subsets = {names[S]: nm(S) for S in order}
    return d


def minimize(dfa):
    """Moore partition refinement on the completed DFA; the dead state is dropped."""
    alphabet = dfa.alphabet
    dead = "#dead"
    states = dfa.states + [dead]
    def step(q, c):
        if q == dead:
            return dead
        s = dfa.delta.get((q, c))
        return next(iter(s)) if s else dead
    block = {q: (q in dfa.finals) for q in states}
    while True:
        sig = {q: (block[q],) + tuple(block[step(q, c)] for c in alphabet) for q in states}
        ids = {}
        new = {q: ids.setdefault(sig[q], len(ids)) for q in states}
        if len(set(new.values())) == len(set(block.values())):
            block = new
            break
        block = new
    # keep only blocks that can reach a final state and are reachable
    dead_b = block[dead]
    reps, names = {}, {}
    for q in dfa.states:
        reps.setdefault(block[q], q)
    delta = {}
    for q in dfa.states:
        for c in alphabet:
            p = step(q, c)
            if block[p] != dead_b and block[q] != dead_b:
                delta[(reps[block[q]], c)] = {reps[block[p]]}
    start = reps[block[dfa.start]]
    keep, todo = [], [start]
    while todo:
        q = todo.pop(0)
        if q in keep:
            continue
        keep.append(q)
        todo.extend(sorted(next(iter(delta[(q, c)])) for c in alphabet if (q, c) in delta))
    ren = {q: "m%d" % i for i, q in enumerate(keep)}
    d2 = {(ren[q], c): {ren[next(iter(p))]} for (q, c), p in delta.items() if q in ren}
    finals = {ren[q] for q in keep if q in dfa.finals}
    return FA(dfa.name, [ren[q] for q in keep], ren[start], finals, d2)


# ----------------------------------------------------------------------------
#  Command line
# ----------------------------------------------------------------------------
def cmd_all(outdir):
    os.makedirs(outdir, exist_ok=True)
    report = []
    for path in sorted(glob.glob("definitions/*.fa")):
        fa = load(path)
        steps = []
        rg = fa_to_rg(fa, steps)
        base = os.path.join(outdir, fa.name)
        with open(base + "_from_fa.rg", "w") as f:
            f.write("# generated by FA -> RG from " + path + "\n" + rg.to_text())
        report += ["=" * 70, "FA -> RG   " + path, "=" * 70, fa.describe(), "",
                   "steps:"] + ["  " + s for s in steps] + ["", rg.describe(), ""]
    for path in sorted(glob.glob("definitions/*.rg")):
        rg = load(path)
        steps = []
        nfa = rg_to_fa(rg, steps)
        dfa = nfa_to_dfa(nfa)
        mdfa = minimize(dfa)
        base = os.path.join(outdir, rg.name)
        with open(base + "_from_rg.fa", "w") as f:
            f.write("# generated by RG -> FA from " + path + "\n" + nfa.to_text())
        with open(base + "_from_rg_dfa.fa", "w") as f:
            f.write("# RG -> FA, then subset construction\n" + dfa.to_text())
        with open(base + "_from_rg_min.fa", "w") as f:
            f.write("# RG -> FA, subset construction, minimisation\n" + mdfa.to_text())
        report += ["=" * 70, "RG -> FA   " + path, "=" * 70, rg.describe(), "", "steps:"]
        report += ["  " + s for s in steps]
        report += ["", "-- result of the transformation --", nfa.describe(), "",
                   "-- after subset construction (%d states) --" % len(dfa.states),
                   dfa.describe(), "", "-- after minimisation (%d states) --" % len(mdfa.states),
                   mdfa.describe(), ""]
    text = "\n".join(report)
    with open(os.path.join(outdir, "transformations_report.txt"), "w") as f:
        f.write(text)
    print(text)
    print("files written to " + outdir + "/")


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    p = sub.add_parser("fa2rg"); p.add_argument("file"); p.add_argument("-o")
    p = sub.add_parser("rg2fa"); p.add_argument("file"); p.add_argument("-o")
    p.add_argument("--dfa", action="store_true", help="apply the subset construction")
    p.add_argument("--min", action="store_true", help="also minimise (implies --dfa)")
    p = sub.add_parser("check"); p.add_argument("file"); p.add_argument("word")
    p = sub.add_parser("show"); p.add_argument("file")
    p = sub.add_parser("dot"); p.add_argument("file"); p.add_argument("-o")
    p = sub.add_parser("all"); p.add_argument("-d", default="results")
    a = ap.parse_args(argv)

    if a.cmd == "all":
        cmd_all(a.d)
        return 0
    obj = load(a.file)
    if a.cmd == "show":
        print(obj.describe())
    elif a.cmd == "dot":
        fa = obj if isinstance(obj, FA) else minimize(nfa_to_dfa(rg_to_fa(obj)))
        if a.o:
            open(a.o, "w").write(fa.to_dot())
        else:
            print(fa.to_dot())
    elif a.cmd == "check":
        ok = obj.accepts(a.word) if isinstance(obj, FA) else obj.derives(a.word)
        print("%r %s %s" % (a.word, "IS in" if ok else "is NOT in", obj.name))
        return 0 if ok else 1
    elif a.cmd == "fa2rg":
        if not isinstance(obj, FA):
            sys.exit("fa2rg needs a .fa file")
        steps = []
        out = fa_to_rg(obj, steps)
        print("\n".join(steps) + "\n")
        print(out.describe())
        if a.o:
            open(a.o, "w").write(out.to_text())
    elif a.cmd == "rg2fa":
        if not isinstance(obj, RG):
            sys.exit("rg2fa needs a .rg file")
        steps = []
        out = rg_to_fa(obj, steps)
        print("\n".join(steps) + "\n")
        if a.dfa or a.min:
            out = nfa_to_dfa(out)
        if a.min:
            out = minimize(out)
        print(out.describe())
        if a.o:
            open(a.o, "w").write(out.to_text())
    return 0


if __name__ == "__main__":
    sys.exit(main())
