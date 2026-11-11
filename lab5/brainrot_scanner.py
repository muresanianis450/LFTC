"""
brainrot_scanner.py - Lab 5, Brainrot DSL
Scanner where identifiers and constants are recognised by finite automata
read from files (fa/identifier.fa, fa/int_constant.fa, fa/string_constant.fa).

Usage:  python3 brainrot_scanner.py tests/program1.br out/p1
Output: out/p1_PIF.txt, out/p1_ST.txt, out/p1_errors.txt
"""
import os
import sys

from symtab import SymTab

KEYWORDS = ["Peigengoo", "Gojo_Satoru", "SIXSEVEN", "Tralalero_Tralala",
            "Cappuccino_Assassino", "Hipocactus", "Bombombini_Gusini", "Trippi_Troppi",
            "Bombardiro_Crocodilo", "Tung_Tung_Tung_Sahur", "Cheese_Rattatino",
            "Shpioniro_Golubiro", "Chimpanzini_Bananini"]
# longest first, so "->" is tried before "-" and ">=" before ">"
OPERATORS = ["==", "!=", ">=", "<=", "->", ">", "<", "=", "+", "-",
             "(", ")", "[", "]", "{", "}", ",", ":", "."]
# token codes (same as tokens.h): identifier 0, constant 1, keywords 2..14, then operators
ALL_TOKENS = ["identifier", "constant"] + KEYWORDS + ["==", "!=", ">", "<", ">=", "<=",
              "=", "+", "-", "->", "(", ")", "[", "]", "{", "}", ",", ":", "."]
CODE = {tok: i for i, tok in enumerate(ALL_TOKENS)}


# ---------------------------------------------------------------------------
#  Finite automaton read from a file
#     states: q0 q1        start: q0        final: q1
#     q0 [A-Za-z_] q1      (one transition per line: state symbol state)
#  A symbol is a character class [..] with ranges, a quoted char '"' or a char.
# ---------------------------------------------------------------------------
def symbol_chars(sym):
    """'[A-Za-z_]' -> set of letters and '_';   "'-'" -> {'-'};   '0' -> {'0'}"""
    if sym.startswith("["):
        inside, chars, i = sym[1:-1], set(), 0
        while i < len(inside):
            if i + 2 < len(inside) and inside[i + 1] == "-":     # a range like A-Z
                chars.update(chr(c) for c in range(ord(inside[i]), ord(inside[i + 2]) + 1))
                i += 3
            else:
                chars.add(inside[i])
                i += 1
        return chars
    if sym.startswith("'"):
        return {sym[1]}
    return {sym}


class FA:
    def __init__(self, path):
        self.start, self.finals, self.delta = None, set(), {}   # delta[(state, char)] = state
        with open(path, encoding="utf-8") as f:
            for line in f:
                line = line.strip()
                if not line or line.startswith("#") or line.startswith("name:") \
                        or line.startswith("states:"):
                    continue
                if line.startswith("start:"):
                    self.start = line[6:].strip()
                elif line.startswith("final:"):
                    self.finals = set(line[6:].split())
                else:                                   # transition: q symbol p
                    q, p = line.split()[0], line.split()[-1]
                    sym = line[len(q):len(line) - len(p)].strip()
                    for c in symbol_chars(sym):
                        self.delta[(q, c)] = p

    def longest_match(self, text, i):
        """Run the automaton from text[i]. Returns the end of the longest
        accepted prefix, or -1 if no prefix is accepted."""

        """For example, the identifier FA on squad = ... reads s q u a d, stops at the space, and returns the position after d."""
        state, best = self.start, -1
        while i < len(text) and (state, text[i]) in self.delta:
            state = self.delta[(state, text[i])]
            i += 1
            if state in self.finals:
                best = i
        return best


# ---------------------------------------------------------------------------
#  Scanner
# ---------------------------------------------------------------------------
FA_DIR = os.path.join(os.path.dirname(os.path.abspath(__file__)), "fa")
IDENT_FA = FA(os.path.join(FA_DIR, "identifier.fa"))
INT_FA = FA(os.path.join(FA_DIR, "int_constant.fa"))
STRING_FA = FA(os.path.join(FA_DIR, "string_constant.fa"))


def scan(text):
    #PIF= [code, token, st_stop]
    pif, st, errors = [], SymTab(), []
    i, line, line_start = 0, 1, 0

    while i < len(text):
        c, col = text[i], i - line_start + 1
        eol = text.find("\n", i)
        eol = len(text) if eol == -1 else eol           # end of the current line

        def error(msg, lexeme):
            errors.append("Lexical error at line %d, column %d: %s: '%s'" % (line, col, msg, lexeme))

        # whitespace and comments
        if c == "\n":
            line, line_start, i = line + 1, i + 1, i + 1
            continue
        if c in " \t\r":
            i += 1
            continue
        if text.startswith("//", i):
            i = eol
            continue

        # identifier or keyword -> identifier FA
        if c.isalpha() or c == "_":
            end = IDENT_FA.longest_match(text, i)
            word = text[i:end]
            if word in KEYWORDS:
                pif.append((CODE[word], word, -1))
            else:
                pif.append((0, word, st.insert(word)))
            i = end
            continue

        # integer constant -> integer FA  ("-" followed by a digit is a negative number)
        if c.isdigit() or (c == "-" and i + 1 < len(text) and text[i + 1].isdigit()):
            j = i + 1                                   # the whole word, e.g. 007, 5b, -12
            while j < len(text) and (text[j].isalnum() or text[j] == "_"):
                j += 1
            word = text[i:j]
            if INT_FA.longest_match(text, i) != j:
                if word.lstrip("-").isdigit():
                    error("leading zero or negative zero in number", word)
                else:
                    error("number glued to letters", word)
            elif not -2**31 <= int(word) <= 2**31 - 1:
                error("integer constant does not fit in 32 bits", word)
            else:
                pif.append((1, word, st.insert(word)))
            i = j
            continue

        # string constant -> string FA
        if c == '"':
            end = STRING_FA.longest_match(text, i)
            if end != -1:
                pif.append((1, text[i:end], st.insert(text[i:end])))
                i = end
            else:
                close = text.find('"', i + 1, eol)
                if close == -1:
                    error("unterminated string", text[i:eol])
                    i = eol
                else:
                    error("string contains a character other than letter, digit or space",
                          text[i:close + 1])
                    i = close + 1
            continue

        # operators and separators
        op = next((op for op in OPERATORS if text.startswith(op, i)), None)
        if op:
            pif.append((CODE[op], op, -1))
            i += len(op)
            continue

        error("invalid character", c)
        i += 1

    return pif, st, errors


def main():
    if len(sys.argv) != 3:
        print("usage: python3 brainrot_scanner.py source.br out/prefix")
        return 2
    source, prefix = sys.argv[1], sys.argv[2]
    with open(source, encoding="utf-8") as f:
        pif, st, errors = scan(f.read())

    os.makedirs(os.path.dirname(prefix) or ".", exist_ok=True)
    with open(prefix + "_PIF.txt", "w") as f:
        f.write("%-6s %-24s %s\n" % ("CODE", "TOKEN", "ST_POS"))
        for code, tok, pos in pif:
            f.write("%-6d %-24s %s\n" % (code, tok, "-" if pos == -1 else pos))
    with open(prefix + "_ST.txt", "w") as f:
        f.write(st.dump())
    with open(prefix + "_errors.txt", "w") as f:
        f.write("\n".join(errors) + "\n" if errors else "No lexical errors.\n")

    print("%s: %d tokens, %d ST entries, %d lexical errors" % (source, len(pif), len(st.entries), len(errors)))
    return 1 if errors else 0


if __name__ == "__main__":
    sys.exit(main())
