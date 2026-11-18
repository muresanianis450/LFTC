# Makefile - Lab 6 (lex + yacc), needs flex, bison, gcc
CC     = gcc
CFLAGS = -Wall -Wextra -std=gnu11 -g

all: brainrot_parser

# bison: -d makes brainrot.tab.h (the token numbers), -v makes brainrot.output
# (the states of the automaton and the conflicts, if any)
brainrot.tab.c brainrot.tab.h: brainrot.y
	bison -d -v brainrot.y

lex.yy.c: brainrot.l brainrot.tab.h token_map.h tokens.h symtab.h
	flex brainrot.l

brainrot_parser: brainrot.tab.c lex.yy.c symtab.c symtab.h token_map.h tokens.h
	$(CC) $(CFLAGS) -o $@ brainrot.tab.c lex.yy.c symtab.c

# the three valid programs must be accepted, the others rejected; the last
# line gives the parser the PIF written by the scanner instead of the source
test: brainrot_parser
	@mkdir -p out
	@for t in program1 program2 v11_features errors; do \
	  ./brainrot_parser tests/$$t.br out/$$t || true; done
	@for t in tests/syntax/*.br; do \
	  ./brainrot_parser $$t out/syntax_`basename $$t .br` || true; done
	@for t in program1 program2 v11_features; do \
	  ./brainrot_parser -pif out/$${t}_PIF.txt out/pif_$$t || true; done

clean:
	rm -f brainrot_parser brainrot_parser.exe brainrot.tab.c brainrot.tab.h brainrot.output lex.yy.c
