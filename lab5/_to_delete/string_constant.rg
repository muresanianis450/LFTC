name: string_constant
nonterminals: S B
start: S
S -> '"' B
B -> [A-Za-z0-9] B | ' ' B | '"'
