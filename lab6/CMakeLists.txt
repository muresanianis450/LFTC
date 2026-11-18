cmake_minimum_required(VERSION 3.15)
project(Lab6 C)
set(CMAKE_C_STANDARD 11)

# brainrot.tab.c / brainrot.tab.h were generated from brainrot.y with: bison -d -v brainrot.y
# lex.yy.c was generated from brainrot.l with:                        flex brainrot.l
# (run these two again after changing the .y or the .l, or just use make)
add_executable(brainrot_parser brainrot.tab.c lex.yy.c symtab.c symtab.h tokens.h token_map.h)
target_include_directories(brainrot_parser PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
