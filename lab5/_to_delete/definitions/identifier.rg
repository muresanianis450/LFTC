name: identifier
nonterminals: I R
start: I
I -> [A-Za-z_] R | [A-Za-z_]
R -> [A-Za-z0-9_] R | [A-Za-z0-9_]
