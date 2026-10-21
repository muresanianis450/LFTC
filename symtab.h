/* symtab.h - Symbol Table implemented as a hash table (separate chaining) */
#ifndef SYMTAB_H
#define SYMTAB_H
#include <stdio.h>

typedef enum { ST_IDENTIFIER, ST_INT_CONST, ST_STR_CONST } StKind;

typedef struct StEntry {
    char           *lexeme;   /* text; string constants keep their quotes */
    StKind          kind;
    int             index;    /* unique ST position = insertion order (0,1,2,...) */
    int             bucket;   /* bucket where the entry lives */
    struct StEntry *next;     /* next entry of the same bucket (chain) */
} StEntry;

typedef struct {
    StEntry **buckets;        /* array of chain heads */
    int       size;           /* number of buckets */
    int       count;          /* number of entries */
    StEntry **by_index;       /* entries in insertion order (for printing) */
    int       capacity;       /* capacity of by_index */
} SymTab;

SymTab  *st_create(int size);
unsigned st_hash(const char *lexeme, StKind kind, int size);
StEntry *st_lookup(const SymTab *st, const char *lexeme, StKind kind);
int      st_insert(SymTab *st, const char *lexeme, StKind kind); /* returns ST position */
void     st_print(const SymTab *st, FILE *out);
void     st_free(SymTab *st);

#endif
