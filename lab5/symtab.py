"""symtab.py - Symbol Table: hash table with separate chaining (as in Lab 3).
One table for identifiers and constants; each lexeme gets one ST position."""


class SymTab:
    def __init__(self, size=101):
        self.size = size
        self.buckets = [[] for _ in range(size)]    # each bucket is a chain of positions
        self.entries = []                           # entries[pos] = lexeme

    def hash(self, lexeme):
        return sum(ord(ch) for ch in lexeme) % self.size

    def insert(self, lexeme):
        """Returns the ST position of lexeme (adds it if it is new)."""
        chain = self.buckets[self.hash(lexeme)]
        for pos in chain:
            if self.entries[pos] == lexeme:
                return pos
        self.entries.append(lexeme)
        chain.append(len(self.entries) - 1)
        return len(self.entries) - 1

    def dump(self):
        out = ["SYMBOL TABLE (hash table, %d buckets, separate chaining)" % self.size,
               "%-7s %-7s %-16s %s" % ("ST_POS", "BUCKET", "KIND", "LEXEME")]
        for pos, lexeme in enumerate(self.entries):
            if lexeme.startswith('"'):
                kind = "string constant"
            elif lexeme.lstrip("-").isdigit():
                kind = "int constant"
            else:
                kind = "identifier"
            out.append("%-7d %-7d %-16s %s" % (pos, self.hash(lexeme), kind, lexeme))
        return "\n".join(out) + "\n"
