%{
/* brainrot.y - syntactic analyser (parser) for the Brainrot DSL (grammar v1.1)
   Input : the tokens of the scanner (brainrot.l), or a PIF file made in Lab 3
   Output: the string of productions, syntax errors. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

/* shared with the scanner (defined in brainrot.l) */
extern SymTab *st;
extern FILE   *pif_out, *err_out;
extern int     error_count, token_count, tok_col;
extern int     yylineno;
extern FILE   *yyin;
extern char   *yytext;
int scan_token(void);                       /* the scanner made by flex */

int  yylex(void);
void yyerror(const char *msg);

static int   use_pif = 0;                   /* 0 = scan a source file, 1 = read a PIF file */
static FILE *pif_in, *syntax_out;
static int   pif_token_no = 0;              /* position of the last token given to the parser */
static int   syntax_errors = 0;
static char  last_text[128] = "";           /* text of the last token, used in the messages */
static int   at_eof = 0;

/* the string of productions: yacc runs PROD(n) every time it reduces the
   production n; the numbers follow the order of the rules in this file
   (they are the same as the rule numbers of brainrot.output) */
static int *prods = NULL;
static int  prod_count = 0, prod_cap = 0;

static void add_prod(int n) {
    if (prod_count == prod_cap) {
        prod_cap = prod_cap ? prod_cap * 2 : 256;
        prods = realloc(prods, prod_cap * sizeof(int));
        if (!prods) { perror("realloc"); exit(1); }
    }
    prods[prod_count++] = n;
}
#define PROD(n) add_prod(n)
%}

%define parse.error verbose

%token END_OF_INPUT 0 "end of file"
%token IDENTIFIER "identifier"
%token NUMBER     "number"
%token STRING     "string"
/* keywords (the 13 reserved words, same order as tokens.h) */
%token PEIGENGOO "Peigengoo"
%token GOJO_SATORU "Gojo_Satoru"
%token SIXSEVEN "SIXSEVEN"
%token TRALALERO_TRALALA "Tralalero_Tralala"
%token CAPPUCCINO_ASSASSINO "Cappuccino_Assassino"
%token HIPOCACTUS "Hipocactus"
%token BOMBOMBINI_GUSINI "Bombombini_Gusini"
%token TRIPPI_TROPPI "Trippi_Troppi"
%token BOMBARDIRO_CROCODILO "Bombardiro_Crocodilo"
%token TUNG_TUNG_TUNG_SAHUR "Tung_Tung_Tung_Sahur"
%token CHEESE_RATTATINO "Cheese_Rattatino"
%token SHPIONIRO_GOLUBIRO "Shpioniro_Golubiro"
%token CHIMPANZINI_BANANINI "Chimpanzini_Bananini"
/* comparison operators */
%token EQ "==" NE "!=" GT ">" LT "<" GE ">=" LE "<="
/* separators and symbols */
%token ASSIGN "=" PLUS "+" MINUS "-" ARROW "->" LPAREN "(" RPAREN ")"
%token LBRACKET "[" RBRACKET "]" LBRACE "{" RBRACE "}" COMMA "," COLON ":" DOT "."

%start program

%%

/* 2.1 program structure */
program          : const_decls statement statements                 { PROD(1); }
                 ;
statements       : statement statements                             { PROD(2); }
                 | /* epsilon */                                    { PROD(3); }
                 ;
statement        : assignment                                       { PROD(4); }
                 | input_statement                                  { PROD(5); }
                 | if_statement                                     { PROD(6); }
                 | for_loop                                         { PROD(7); }
                 | print_statement                                  { PROD(8); }
                 ;

/* 2.2 constants */
const_decls      : const_decl const_decls                           { PROD(9); }
                 | /* epsilon */                                    { PROD(10); }
                 ;
const_decl       : "Chimpanzini_Bananini" IDENTIFIER "=" const_value { PROD(11); }
                 ;
const_value      : STRING                                           { PROD(12); }
                 | NUMBER                                           { PROD(13); }
                 | "SIXSEVEN"                                       { PROD(14); }
                 | IDENTIFIER                                       { PROD(15); }
                 ;

/* 2.3 simple statements */
assignment       : IDENTIFIER "=" list_expression                   { PROD(16); }
                 ;
input_statement  : "Tung_Tung_Tung_Sahur" IDENTIFIER                { PROD(17); }
                 ;
print_statement  : "Bombardiro_Crocodilo" print_arg                 { PROD(18); }
                 ;
print_arg        : list_expression                                  { PROD(19); }
                 | STRING                                           { PROD(20); }
                 ;

/* 2.4 list expressions */
list_expression  : list_base list_ops                               { PROD(21); }
                 ;
list_base        : list_creation                                    { PROD(22); }
                 | IDENTIFIER                                       { PROD(23); }
                 ;
list_ops         : list_op list_ops                                 { PROD(24); }
                 | /* epsilon */                                    { PROD(25); }
                 ;
list_op          : filter_op                                        { PROD(26); }
                 | add_op                                           { PROD(27); }
                 | remove_op                                        { PROD(28); }
                 | select_op                                        { PROD(29); }
                 ;

list_creation    : "Peigengoo" "(" record_list ")"                  { PROD(30); }
                 ;
record_list      : "[" record_list_content "]"                      { PROD(31); }
                 ;
record_list_content : record more_records                           { PROD(32); }
                 | /* epsilon */                                    { PROD(33); }
                 ;
more_records     : "," record more_records                          { PROD(34); }
                 | /* epsilon */                                    { PROD(35); }
                 ;
record           : "{" pair more_pairs "}"                          { PROD(36); }
                 ;
more_pairs       : "," pair more_pairs                              { PROD(37); }
                 | /* epsilon */                                    { PROD(38); }
                 ;
pair             : IDENTIFIER ":" value                             { PROD(39); }
                 ;

filter_op        : "Gojo_Satoru" condition                          { PROD(40); }
                 ;
add_op           : "+" IDENTIFIER "=" value                         { PROD(41); }
                 ;
remove_op        : "-" IDENTIFIER                                   { PROD(42); }
                 ;
select_op        : "->" "(" identifier_list ")"                     { PROD(43); }
                 ;
identifier_list  : IDENTIFIER more_identifiers                      { PROD(44); }
                 ;
more_identifiers : "," IDENTIFIER more_identifiers                  { PROD(45); }
                 | /* epsilon */                                    { PROD(46); }
                 ;

/* 2.5 conditions and values: "and" binds tighter than "or" because it is
   one level lower in the grammar */
condition        : and_cond or_rest                                 { PROD(47); }
                 ;
or_rest          : "Shpioniro_Golubiro" and_cond or_rest            { PROD(48); }
                 | /* epsilon */                                    { PROD(49); }
                 ;
and_cond         : simple_cond and_rest                             { PROD(50); }
                 ;
and_rest         : "Cheese_Rattatino" simple_cond and_rest          { PROD(51); }
                 | /* epsilon */                                    { PROD(52); }
                 ;
simple_cond      : field_ref operator value                         { PROD(53); }
                 | "(" condition ")"                                { PROD(54); }
                 ;
field_ref        : IDENTIFIER field_suffix                          { PROD(55); }
                 ;
field_suffix     : "." IDENTIFIER                                   { PROD(56); }
                 | /* epsilon */                                    { PROD(57); }
                 ;
operator         : "==" { PROD(58); } | "!=" { PROD(59); } | ">" { PROD(60); }
                 | "<" { PROD(61); } | ">=" { PROD(62); } | "<=" { PROD(63); }
                 ;
value            : STRING                                           { PROD(64); }
                 | NUMBER                                           { PROD(65); }
                 | "SIXSEVEN"                                       { PROD(66); }
                 | field_ref                                        { PROD(67); }
                 ;

/* 2.6 compound statements */
if_statement     : "Tralalero_Tralala" condition statement_block optional_else "Hipocactus" { PROD(68); }
                 ;
optional_else    : "Cappuccino_Assassino" statement_block           { PROD(69); }
                 | /* epsilon */                                    { PROD(70); }
                 ;
for_loop         : "Bombombini_Gusini" IDENTIFIER "Trippi_Troppi" list_expression statement_block "Hipocactus" { PROD(71); }
                 ;
statement_block  : statement statements                             { PROD(72); }
                 ;

%%

/* the text of every production, indexed by its number (PRODUCTION[0] is unused) */
static const char *PRODUCTION[] = {
    "",
    "<program> ::= <const_decls> <statement> <statements>",
    "<statements> ::= <statement> <statements>",
    "<statements> ::= epsilon",
    "<statement> ::= <assignment>",
    "<statement> ::= <input_statement>",
    "<statement> ::= <if_statement>",
    "<statement> ::= <for_loop>",
    "<statement> ::= <print_statement>",
    "<const_decls> ::= <const_decl> <const_decls>",
    "<const_decls> ::= epsilon",
    "<const_decl> ::= \"Chimpanzini_Bananini\" <identifier> \"=\" <const_value>",
    "<const_value> ::= <string>",
    "<const_value> ::= <number>",
    "<const_value> ::= \"SIXSEVEN\"",
    "<const_value> ::= <identifier>",
    "<assignment> ::= <identifier> \"=\" <list_expression>",
    "<input_statement> ::= \"Tung_Tung_Tung_Sahur\" <identifier>",
    "<print_statement> ::= \"Bombardiro_Crocodilo\" <print_arg>",
    "<print_arg> ::= <list_expression>",
    "<print_arg> ::= <string>",
    "<list_expression> ::= <list_base> <list_ops>",
    "<list_base> ::= <list_creation>",
    "<list_base> ::= <identifier>",
    "<list_ops> ::= <list_op> <list_ops>",
    "<list_ops> ::= epsilon",
    "<list_op> ::= <filter_op>",
    "<list_op> ::= <add_op>",
    "<list_op> ::= <remove_op>",
    "<list_op> ::= <select_op>",
    "<list_creation> ::= \"Peigengoo\" \"(\" <record_list> \")\"",
    "<record_list> ::= \"[\" <record_list_content> \"]\"",
    "<record_list_content> ::= <record> <more_records>",
    "<record_list_content> ::= epsilon",
    "<more_records> ::= \",\" <record> <more_records>",
    "<more_records> ::= epsilon",
    "<record> ::= \"{\" <pair> <more_pairs> \"}\"",
    "<more_pairs> ::= \",\" <pair> <more_pairs>",
    "<more_pairs> ::= epsilon",
    "<pair> ::= <identifier> \":\" <value>",
    "<filter_op> ::= \"Gojo_Satoru\" <condition>",
    "<add_op> ::= \"+\" <identifier> \"=\" <value>",
    "<remove_op> ::= \"-\" <identifier>",
    "<select_op> ::= \"->\" \"(\" <identifier_list> \")\"",
    "<identifier_list> ::= <identifier> <more_identifiers>",
    "<more_identifiers> ::= \",\" <identifier> <more_identifiers>",
    "<more_identifiers> ::= epsilon",
    "<condition> ::= <and_cond> <or_rest>",
    "<or_rest> ::= \"Shpioniro_Golubiro\" <and_cond> <or_rest>",
    "<or_rest> ::= epsilon",
    "<and_cond> ::= <simple_cond> <and_rest>",
    "<and_rest> ::= \"Cheese_Rattatino\" <simple_cond> <and_rest>",
    "<and_rest> ::= epsilon",
    "<simple_cond> ::= <field_ref> <operator> <value>",
    "<simple_cond> ::= \"(\" <condition> \")\"",
    "<field_ref> ::= <identifier> <field_suffix>",
    "<field_suffix> ::= \".\" <identifier>",
    "<field_suffix> ::= epsilon",
    "<operator> ::= \"==\"",
    "<operator> ::= \"!=\"",
    "<operator> ::= \">\"",
    "<operator> ::= \"<\"",
    "<operator> ::= \">=\"",
    "<operator> ::= \"<=\"",
    "<value> ::= <string>",
    "<value> ::= <number>",
    "<value> ::= \"SIXSEVEN\"",
    "<value> ::= <field_ref>",
    "<if_statement> ::= \"Tralalero_Tralala\" <condition> <statement_block> <optional_else> \"Hipocactus\"",
    "<optional_else> ::= \"Cappuccino_Assassino\" <statement_block>",
    "<optional_else> ::= epsilon",
    "<for_loop> ::= \"Bombombini_Gusini\" <identifier> \"Trippi_Troppi\" <list_expression> <statement_block> \"Hipocactus\"",
    "<statement_block> ::= <statement> <statements>",
};

#include "token_map.h"      /* after the token numbers made by bison */

/* ---------- reading the tokens from a PIF file (Lab 3 format) ---------- */

/* a PIF line is:  CODE  TOKEN  ST_POS   (the token text of a string can contain spaces) */
static int pif_token(void) {
    static int line_no = 0;
    char line[1024];
    while (fgets(line, sizeof line, pif_in)) {
        line_no++;

        size_t n = strlen(line);
        while (n > 0 && (line[n - 1] == '\n' || line[n - 1] == '\r' || line[n - 1] == ' ')) line[--n] = 0;
        if (n == 0 || strncmp(line, "CODE", 4) == 0) continue;     /* empty line or header */

        char *end;
        long code = strtol(line, &end, 10);
        char *last = strrchr(line, ' ');                           /* the ST_POS column starts after it */
        if (end == line || !last || last <= end || code < 0 || code >= TOKEN_COUNT) {
            fprintf(syntax_out, "PIF error at line %d: not a valid PIF line: '%s'\n", line_no, line);
            error_count++;
            continue;
        }
        while (*end == ' ') end++;
        size_t len = (size_t)(last - end);
        while (len > 0 && end[len - 1] == ' ') len--;
        if (len >= sizeof last_text) len = sizeof last_text - 1;
        memcpy(last_text, end, len);
        last_text[len] = 0;
        /* keywords and symbols have a fixed text, so the code and the text must agree */
        if (code >= T_PEIGENGOO && strcmp(last_text, TOKEN_NAME[code]) != 0) {
            fprintf(syntax_out, "PIF error at line %d: code %ld is '%s', not '%s'\n",
                    line_no, code, TOKEN_NAME[code], last_text);
            error_count++;
            continue;
        }
        pif_token_no++;
        return yacc_token((int)code, last_text);
    }
    return 0;                                                       /* end of the PIF */
}

/* yacc asks for the next token here; the scanner and the PIF reader give the same tokens */
int yylex(void) {
    int t = use_pif ? pif_token() : scan_token();
    if (!use_pif) {
        snprintf(last_text, sizeof last_text, "%s", yytext);
        pif_token_no++;
    }
    at_eof = (t == 0);
    return t;
}

void yyerror(const char *msg) {
    const char *m = strncmp(msg, "syntax error, ", 14) == 0 ? msg + 14 : msg;
    if (at_eof)       fprintf(syntax_out, "Syntax error: %s", m);       /* no position: the file just ended */
    else if (use_pif) fprintf(syntax_out, "Syntax error at PIF token #%d: %s (found '%s')", pif_token_no, m, last_text);
    else              fprintf(syntax_out, "Syntax error at line %d, column %d: %s (found '%s')", yylineno, tok_col, m, last_text);
    fprintf(syntax_out, "\n");
    syntax_errors++;
}

/* ---------- output ---------- */

static void write_productions(FILE *out) {
    /* yacc reduces in the order of a rightmost derivation read backwards, so
       the derivation of <program> is the same list from the end to the start */
    fprintf(out, "STRING OF PRODUCTIONS (%d productions)\n", prod_count);
    fprintf(out, "rightmost derivation of <program>, first production applied first:\n\n");
    for (int i = prod_count - 1; i >= 0; i--)
        fprintf(out, "%d%c", prods[i], (i % 20 == 0) ? '\n' : ' ');
    fprintf(out, "\n\nREDUCTIONS made by the parser, in order:\n");
    fprintf(out, "%-6s %-6s %s\n", "STEP", "PROD", "PRODUCTION");
    for (int i = 0; i < prod_count; i++)
        fprintf(out, "%-6d %-6d %s\n", i + 1, prods[i], PRODUCTION[prods[i]]);
}

int main(int argc, char **argv) {
    int a = 1;
    if (a < argc && strcmp(argv[a], "-pif") == 0) { use_pif = 1; a++; }
    if (a >= argc) {
        fprintf(stderr, "usage: %s source.br [output_prefix]\n"
                        "       %s -pif program_PIF.txt [output_prefix]\n", argv[0], argv[0]);
        return 2;
    }
    const char *input = argv[a++];
    FILE *in = fopen(input, "r");
    if (!in) { perror(input); return 2; }

    char prefix[512];
    if (a < argc) snprintf(prefix, sizeof prefix, "%s", argv[a]);
    else {
        snprintf(prefix, sizeof prefix, "%s", input);
        char *tail = strstr(prefix, "_PIF.txt");
        char *dot  = strrchr(prefix, '.');
        if (use_pif && tail) *tail = 0;
        else if (dot)        *dot = 0;
    }

    char name[560];
    snprintf(name, sizeof name, "%s_syntax_errors.txt", prefix);
    syntax_out = fopen(name, "w");
    FILE *prod_out = NULL, *st_out = NULL;
    snprintf(name, sizeof name, "%s_productions.txt", prefix);
    prod_out = fopen(name, "w");
    if (!syntax_out || !prod_out) { perror("output files"); return 2; }

    if (use_pif) pif_in = in;
    else {
        /* source mode: the scanner of Lab 3 runs inside the parser and writes its own files */
        yyin = in;
        snprintf(name, sizeof name, "%s_PIF.txt", prefix);    pif_out = fopen(name, "w");
        snprintf(name, sizeof name, "%s_errors.txt", prefix); err_out = fopen(name, "w");
        snprintf(name, sizeof name, "%s_ST.txt", prefix);     st_out  = fopen(name, "w");
        if (!pif_out || !err_out || !st_out) { perror("output files"); return 2; }
        st = st_create(101);
        fprintf(pif_out, "%-6s %-24s %s\n", "CODE", "TOKEN", "ST_POS");
    }

    int parsed = (yyparse() == 0);
    /* after a syntax error the rest of the file is still scanned, so the PIF,
       the ST and the lexical errors are complete like in Lab 3 */
    if (!use_pif && !at_eof) while (scan_token() != 0) ;

    int accepted = parsed && error_count == 0;
    if (accepted) {
        write_productions(prod_out);
        fprintf(syntax_out, "No syntax errors.\n");
    } else {
        fprintf(prod_out, "No string of productions: the input was rejected (see the error files).\n");
    }

    if (accepted)
        printf("%s: accepted, %d tokens, %d productions -> %s_productions.txt\n",
               input, use_pif ? pif_token_no : token_count, prod_count, prefix);
    else
        printf("%s: REJECTED, %d %s error(s), %d syntax error(s) -> %s_syntax_errors.txt\n",
               input, error_count, use_pif ? "PIF" : "lexical", syntax_errors, prefix);

    if (!use_pif) {
        st_print(st, st_out);
        if (error_count == 0) fprintf(err_out, "No lexical errors.\n");
        st_free(st);
        fclose(pif_out); fclose(err_out); fclose(st_out);
    }
    fclose(in); fclose(syntax_out); fclose(prod_out);
    free(prods);
    return accepted ? 0 : 1;
}
