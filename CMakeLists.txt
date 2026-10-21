cmake_minimum_required(VERSION 3.15)
project(Lab3 C)
set(CMAKE_C_STANDARD 11)

# lex.yy.c was generated from brainrot.l with: flex brainrot.l
add_executable(brainrot_lexer lex.yy.c symtab.c symtab.h tokens.h)
target_include_directories(brainrot_lexer PRIVATE ../../..)
