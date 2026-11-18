# Brainrot DSL - Lab 6: parser (flex + bison)

The scanner of Lab 3 (`brainrot.l`) is called by a bison parser (`brainrot.y`).
The grammar is the syntactic part of grammar v1.1 (72 productions, LALR(1),
no conflicts). The parser prints the string of productions.

    make                                   # bison -d -v, flex, gcc -> brainrot_parser
    ./brainrot_parser tests/program1.br out/p1          # scan + parse a source file
    ./brainrot_parser -pif out/p1_PIF.txt out/p1_pif    # parse a PIF file
    make test

| file | what it is |
|------|------------|
| `brainrot.y`   | the grammar (rules numbered 1..72), the PIF reader, yylex/yyerror, main |
| `brainrot.l`   | scanner of Lab 3, returns the tokens to yacc and still writes PIF/ST/lexical errors |
| `token_map.h`  | PIF code (tokens.h) -> token number of yacc |
| `tokens.h`, `symtab.c/h` | unchanged from Lab 3 |
| `brainrot.tab.c/h`, `lex.yy.c` | generated, kept so the project builds without flex/bison |
| `Makefile`, `CMakeLists.txt` | build |
| `tests/`       | programs of Lab 2/3 (`program1`, `program2`, `v11_features`, `errors`) and `tests/syntax/` (one syntax error per file) |
| `out/`         | results of `make test` |

Output files for `<prefix>`: `<prefix>_productions.txt` (the string of productions and
the reductions step by step), `<prefix>_syntax_errors.txt`; in source mode also the
Lab 3 files `<prefix>_PIF.txt`, `<prefix>_ST.txt`, `<prefix>_errors.txt`.
Exit code: 0 accepted, 1 rejected, 2 usage.
