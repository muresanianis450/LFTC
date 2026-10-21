/* symtab.c - hash table with separate chaining; the key is (lexeme, kind) */
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

static char *dup_str(const char *s) {
    size_t n = strlen(s) + 1;
    char *p = malloc(n);
    if (!p) { perror("malloc"); exit(1); }
    memcpy(p, s, n);
    return p;
}

SymTab *st_create(int size) {
    SymTab *st = malloc(sizeof *st);
    if (!st) { perror("malloc"); exit(1); }
    st->size = size;
    st->count = 0;
    st->capacity = 64;
    st->buckets = calloc(size, sizeof(StEntry *));
    st->by_index = malloc(st->capacity * sizeof(StEntry *));
    if (!st->buckets || !st->by_index) { perror("alloc"); exit(1); }
    return st;
}

/* djb2 over the lexeme, then the kind is mixed in so that the number 5 and
   the identifier/string with the same text never share a slot by design */
unsigned st_hash(const char *lexeme, StKind kind, int size) {
    unsigned long h = 5381;
    for (const unsigned char *p = (const unsigned char *)lexeme; *p; p++)
        h = ((h << 5) + h) + *p;
    h = h * 31 + (unsigned)kind;
    return (unsigned)(h % (unsigned long)size);
}

StEntry *st_lookup(const SymTab *st, const char *lexeme, StKind kind) {
    unsigned b = st_hash(lexeme, kind, st->size);
    for (StEntry *e = st->buckets[b]; e; e = e->next)
        if (e->kind == kind && strcmp(e->lexeme, lexeme) == 0)
            return e;
    return NULL;
}

int st_insert(SymTab *st, const char *lexeme, StKind kind) {
    StEntry *e = st_lookup(st, lexeme, kind);
    if (e) return e->index;                       /* already present */

    unsigned b = st_hash(lexeme, kind, st->size);
    e = malloc(sizeof *e);
    if (!e) { perror("malloc"); exit(1); }
    e->lexeme = dup_str(lexeme);
    e->kind   = kind;
    e->index  = st->count;
    e->bucket = (int)b;
    e->next   = st->buckets[b];                   /* insert at head of chain */
    st->buckets[b] = e;

    if (st->count == st->capacity) {
        st->capacity *= 2;
        st->by_index = realloc(st->by_index, st->capacity * sizeof(StEntry *));
        if (!st->by_index) { perror("realloc"); exit(1); }
    }
    st->by_index[st->count++] = e;
    return e->index;
}

static const char *kind_name(StKind k) {
    switch (k) {
        case ST_IDENTIFIER: return "identifier";
        case ST_INT_CONST:  return "int constant";
        default:            return "string constant";
    }
}

void st_print(const SymTab *st, FILE *out) {
    int longest = 0, used = 0;
    for (int b = 0; b < st->size; b++) {
        int len = 0;
        for (StEntry *e = st->buckets[b]; e; e = e->next) len++;
        if (len) used++;
        if (len > longest) longest = len;
    }
    fprintf(out, "SYMBOL TABLE (hash table, %d buckets, separate chaining)\n", st->size);
    fprintf(out, "entries: %d | buckets used: %d | longest chain: %d | load factor: %.3f\n\n",
            st->count, used, longest, (double)st->count / st->size);
    fprintf(out, "%-9s %-8s %-16s %s\n", "ST_POS", "BUCKET", "KIND", "LEXEME");
    for (int i = 0; i < st->count; i++) {
        StEntry *e = st->by_index[i];
        fprintf(out, "%-9d %-8d %-16s %s\n", e->index, e->bucket, kind_name(e->kind), e->lexeme);
    }
}

void st_free(SymTab *st) {
    for (int b = 0; b < st->size; b++) {
        StEntry *e = st->buckets[b];
        while (e) { StEntry *n = e->next; free(e->lexeme); free(e); e = n; }
    }
    free(st->buckets);
    free(st->by_index);
    free(st);
}
