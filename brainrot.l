%{
/* brainrot.l - lexical analyser for the Brainrot DSL (grammar v1.1)
   Output: Program Internal Form (PIF), Symbol Table (ST), lexical errors. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include "tokens.h"
#include "symtab.h"

static SymTab *st;
static FILE   *pif_out, *err_out;
static int     error_count = 0, token_count = 0;
static int     col = 1, tok_col = 1;

static void add_pif(int code, const char *text, int st_pos) {
    if (st_pos >= 0) fprintf(pif_out, "%-6d %-24s %d\n", code, text, st_pos);
    else             fprintf(pif_out, "%-6d %-24s -\n", code, text);
    token_count++;
}
static void emit(int code)                 { add_pif(code, TOKEN_NAME[code], -1); }

static void lex_error(const char *msg, const char *text) {
    char shown[64]; int j = 0;
    for (const unsigned char *p = (const unsigned char *)text; *p && j < 58; p++) {
        if (*p >= 32 && *p < 127) shown[j++] = (char)*p;
        else j += sprintf(shown + j, "\\x%02X", *p);
    }
    shown[j] = 0;
    fprintf(err_out, "Lexical error at line %d, column %d: %s: '%s'\n",
            yylineno, tok_col, msg, shown);
    error_count++;
}

/* number: must fit a signed 32-bit integer */
static void number_token(const char *text) {
    errno = 0;
    long long v = strtoll(text, NULL, 10);
    if (errno == ERANGE || v < INT_MIN || v > INT_MAX) {
        lex_error("integer constant does not fit in 32 bits", text);
        return;
    }
    add_pif(T_CONSTANT, text, st_insert(st, text, ST_INT_CONST));
}

#define YY_USER_ACTION { tok_col = col; col += yyleng; }
%}

%option noyywrap yylineno

ALPHA    [A-Za-z]
LETTER   [A-Za-z_]
DIGIT    [0-9]

%%

[ \t\r]+                      { /* whitespace: ignored */ }
\n                            { col = 1; }
"//"[^\n]*                    { /* line comment: ignored */ }

"Peigengoo"                   { emit(T_PEIGENGOO); }
"Gojo_Satoru"                 { emit(T_GOJO_SATORU); }
"SIXSEVEN"                    { emit(T_SIXSEVEN); }
"Tralalero_Tralala"           { emit(T_TRALALERO_TRALALA); }
"Cappuccino_Assassino"        { emit(T_CAPPUCCINO_ASSASSINO); }
"Hipocactus"                  { emit(T_HIPOCACTUS); }
"Bombombini_Gusini"           { emit(T_BOMBOMBINI_GUSINI); }
"Trippi_Troppi"               { emit(T_TRIPPI_TROPPI); }
"Bombardiro_Crocodilo"        { emit(T_BOMBARDIRO_CROCODILO); }
"Tung_Tung_Tung_Sahur"        { emit(T_TUNG_TUNG_TUNG_SAHUR); }
"Cheese_Rattatino"            { emit(T_CHEESE_RATTATINO); }
"Shpioniro_Golubiro"          { emit(T_SHPIONIRO_GOLUBIRO); }
"Chimpanzini_Bananini"        { emit(T_CHIMPANZINI_BANANINI); }

{LETTER}({LETTER}|{DIGIT})*   { add_pif(T_IDENTIFIER, yytext, st_insert(st, yytext, ST_IDENTIFIER)); }

0                             { number_token(yytext); }
-?[1-9]{DIGIT}*               { number_token(yytext); }
-0{DIGIT}*|0{DIGIT}+          { lex_error("leading zero or negative zero in number", yytext); }
-?{DIGIT}+{LETTER}({LETTER}|{DIGIT})* { lex_error("number glued to letters", yytext); }

\"({ALPHA}|{DIGIT}|" ")*\"    { add_pif(T_CONSTANT, yytext, st_insert(st, yytext, ST_STR_CONST)); }
\"[^"\n]*\"                   { lex_error("string contains a character other than letter, digit or space", yytext); }
\"[^"\n]*                     { lex_error("unterminated string", yytext); }

"=="                          { emit(T_EQ); }
"!="                          { emit(T_NE); }
">="                          { emit(T_GE); }
"<="                          { emit(T_LE); }
">"                           { emit(T_GT); }
"<"                           { emit(T_LT); }
"->"                          { emit(T_ARROW); }
"="                           { emit(T_ASSIGN); }
"+"                           { emit(T_PLUS); }
"-"                           { emit(T_MINUS); }
"("                           { emit(T_LPAREN); }
")"                           { emit(T_RPAREN); }
"["                           { emit(T_LBRACKET); }
"]"                           { emit(T_RBRACKET); }
"{"                           { emit(T_LBRACE); }
"}"                           { emit(T_RBRACE); }
","                           { emit(T_COMMA); }
":"                           { emit(T_COLON); }
"."                           { emit(T_DOT); }

.                             { lex_error("invalid character", yytext); }

%%

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s source.br [output_prefix]\n", argv[0]);
        return 2;
    }
    FILE *in = fopen(argv[1], "r");
    if (!in) { perror(argv[1]); return 2; }
    yyin = in;

    char prefix[512];
    if (argc >= 3) snprintf(prefix, sizeof prefix, "%s", argv[2]);
    else {
        snprintf(prefix, sizeof prefix, "%s", argv[1]);
        char *dot = strrchr(prefix, '.');
        if (dot) *dot = 0;
    }
    char name[560];
    snprintf(name, sizeof name, "%s_PIF.txt", prefix);    pif_out = fopen(name, "w");
    snprintf(name, sizeof name, "%s_errors.txt", prefix); err_out = fopen(name, "w");
    snprintf(name, sizeof name, "%s_ST.txt", prefix);
    FILE *st_out = fopen(name, "w");
    if (!pif_out || !err_out || !st_out) { perror("output files"); return 2; }

    st = st_create(101);
    fprintf(pif_out, "%-6s %-24s %s\n", "CODE", "TOKEN", "ST_POS");
    yylex();

    st_print(st, st_out);
    if (error_count == 0) fprintf(err_out, "No lexical errors.\n");
    printf("%s: %d tokens, %d ST entries, %d lexical error(s) -> %s_PIF.txt, %s_ST.txt, %s_errors.txt\n",
           argv[1], token_count, st->count, error_count, prefix, prefix, prefix);

    st_free(st);
    fclose(in); fclose(pif_out); fclose(err_out); fclose(st_out);
    return error_count ? 1 : 0;
}
