name: int_constant
nonterminals: S N D
start: S
S -> 0 | '-' N | [1-9] D | [1-9]
N -> [1-9] D | [1-9]
D -> [0-9] D | [0-9]
