%{
/* brainrot.l - lexical analyser for the Brainrot DSL (grammar v1.1)
   Lab 3 scanner, now called by the parser (brainrot.y): every token that
   goes to the PIF is also returned to yacc.
   Output: Program Internal Form (PIF), Symbol Table (ST), lexical errors. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include "tokens.h"
#include "symtab.h"
#include "token_map.h"

/* not static: brainrot.y opens the files and prints the results */
SymTab *st;
FILE   *pif_out, *err_out;
int     error_count = 0, token_count = 0;
int     tok_col = 1;
static int col = 1;

/* the parser calls the scanner under this name; yylex() itself is in brainrot.y
   because it can also read the tokens from a PIF file */
#define YY_DECL int scan_token(void)

static void add_pif(int code, const char *text, int st_pos) {
    if (st_pos >= 0) fprintf(pif_out, "%-6d %-24s %d\n", code, text, st_pos);
    else             fprintf(pif_out, "%-6d %-24s -\n", code, text);
    token_count++;
}
/* writes the token in the PIF and gives back the number yacc knows it by */
static int emit(int code) {
    add_pif(code, TOKEN_NAME[code], -1);
    return YACC_TOKEN[code];
}

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

/* number: must fit a signed 32-bit integer; returns 0 if it does not, so
   no token goes to the parser (the scanner goes on, like in Lab 3) */
static int number_token(const char *text) {
    errno = 0;
    long long v = strtoll(text, NULL, 10);
    if (errno == ERANGE || v < INT_MIN || v > INT_MAX) {
        lex_error("integer constant does not fit in 32 bits", text);
        return 0;
    }
    add_pif(T_CONSTANT, text, st_insert(st, text, ST_INT_CONST));
    return yacc_token(T_CONSTANT, text);
}

#define YY_USER_ACTION { tok_col = col; col += yyleng; }
%}

%option noyywrap yylineno nounput noinput

ALPHA    [A-Za-z]
LETTER   [A-Za-z_]
DIGIT    [0-9]

%%

[ \t\r]+                      { /* whitespace: ignored */ }
\n                            { col = 1; }
"//"[^\n]*                    { /* line comment: ignored */ }

"Peigengoo"                   { return emit(T_PEIGENGOO); }
"Gojo_Satoru"                 { return emit(T_GOJO_SATORU); }
"SIXSEVEN"                    { return emit(T_SIXSEVEN); }
"Tralalero_Tralala"           { return emit(T_TRALALERO_TRALALA); }
"Cappuccino_Assassino"        { return emit(T_CAPPUCCINO_ASSASSINO); }
"Hipocactus"                  { return emit(T_HIPOCACTUS); }
"Bombombini_Gusini"           { return emit(T_BOMBOMBINI_GUSINI); }
"Trippi_Troppi"               { return emit(T_TRIPPI_TROPPI); }
"Bombardiro_Crocodilo"        { return emit(T_BOMBARDIRO_CROCODILO); }
"Tung_Tung_Tung_Sahur"        { return emit(T_TUNG_TUNG_TUNG_SAHUR); }
"Cheese_Rattatino"            { return emit(T_CHEESE_RATTATINO); }
"Shpioniro_Golubiro"          { return emit(T_SHPIONIRO_GOLUBIRO); }
"Chimpanzini_Bananini"        { return emit(T_CHIMPANZINI_BANANINI); }

{LETTER}({LETTER}|{DIGIT})*   { add_pif(T_IDENTIFIER, yytext, st_insert(st, yytext, ST_IDENTIFIER));
                                return IDENTIFIER; }

0                             { if (number_token(yytext)) return NUMBER; }
-?[1-9]{DIGIT}*               { if (number_token(yytext)) return NUMBER; }
-0{DIGIT}*|0{DIGIT}+          { lex_error("leading zero or negative zero in number", yytext); }
-?{DIGIT}+{LETTER}({LETTER}|{DIGIT})* { lex_error("number glued to letters", yytext); }

\"({ALPHA}|{DIGIT}|" ")*\"    { add_pif(T_CONSTANT, yytext, st_insert(st, yytext, ST_STR_CONST));
                                return STRING; }
\"[^"\n]*\"                   { lex_error("string contains a character other than letter, digit or space", yytext); }
\"[^"\n]*                     { lex_error("unterminated string", yytext); }

"=="                          { return emit(T_EQ); }
"!="                          { return emit(T_NE); }
">="                          { return emit(T_GE); }
"<="                          { return emit(T_LE); }
">"                           { return emit(T_GT); }
"<"                           { return emit(T_LT); }
"->"                          { return emit(T_ARROW); }
"="                           { return emit(T_ASSIGN); }
"+"                           { return emit(T_PLUS); }
"-"                           { return emit(T_MINUS); }
"("                           { return emit(T_LPAREN); }
")"                           { return emit(T_RPAREN); }
"["                           { return emit(T_LBRACKET); }
"]"                           { return emit(T_RBRACKET); }
"{"                           { return emit(T_LBRACE); }
"}"                           { return emit(T_RBRACE); }
","                           { return emit(T_COMMA); }
":"                           { return emit(T_COLON); }
"."                           { return emit(T_DOT); }

.                             { lex_error("invalid character", yytext); }

%%

/* no main() here: the parser (brainrot.y) is the main program now */
