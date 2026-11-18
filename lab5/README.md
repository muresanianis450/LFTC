# Brainrot DSL - Lab 5: scanner with integrated FA

Identifiers, integer constants and string constants are recognised by finite
automata read from `fa/*.fa` (from Lab 4). The first character decides which
automaton runs:

| first char        | automaton              | after acceptance                  |
|-------------------|------------------------|-----------------------------------|
| letter or `_`     | `fa/identifier.fa`     | keyword? -> PIF, else ST + PIF    |
| digit or `-digit` | `fa/int_constant.fa`   | 32-bit check -> ST + PIF          |
| `"`               | `fa/string_constant.fa`| ST + PIF                          |

The automaton runs as long as it has a transition and remembers the last
final state reached (longest match). Everything else (operators, separators,
whitespace, `//` comments) is handled directly in the scanner.

    python3 brainrot_scanner.py tests/program1.br out/p1
    make test

Output: `out/<name>_PIF.txt`, `out/<name>_ST.txt`, `out/<name>_errors.txt`.

Files: `brainrot_scanner.py` (FA + scanner), `symtab.py` (hash-table ST),
`fa/` (the 3 automata), `tests/` (4 programs, `errors.br` has one error per line).
