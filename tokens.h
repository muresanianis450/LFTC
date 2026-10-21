/* tokens.h - internal codes of the Brainrot tokens (grammar v1.1) */
#ifndef TOKENS_H
#define TOKENS_H

enum TokenCode {
    T_IDENTIFIER = 0, T_CONSTANT = 1,
    /* keywords */
    T_PEIGENGOO = 2, T_GOJO_SATORU, T_SIXSEVEN, T_TRALALERO_TRALALA,
    T_CAPPUCCINO_ASSASSINO, T_HIPOCACTUS, T_BOMBOMBINI_GUSINI, T_TRIPPI_TROPPI,
    T_BOMBARDIRO_CROCODILO, T_TUNG_TUNG_TUNG_SAHUR, T_CHEESE_RATTATINO,
    T_SHPIONIRO_GOLUBIRO, T_CHIMPANZINI_BANANINI,        /* 2 .. 14 */
    /* comparison operators */
    T_EQ = 15, T_NE, T_GT, T_LT, T_GE, T_LE,             /* 15 .. 20 */
    /* separators / symbols */
    T_ASSIGN = 21, T_PLUS, T_MINUS, T_ARROW, T_LPAREN, T_RPAREN,
    T_LBRACKET, T_RBRACKET, T_LBRACE, T_RBRACE, T_COMMA, T_COLON, T_DOT /* 21 .. 33 */
};

static const char *TOKEN_NAME[] = {
    "identifier", "constant",
    "Peigengoo", "Gojo_Satoru", "SIXSEVEN", "Tralalero_Tralala",
    "Cappuccino_Assassino", "Hipocactus", "Bombombini_Gusini", "Trippi_Troppi",
    "Bombardiro_Crocodilo", "Tung_Tung_Tung_Sahur", "Cheese_Rattatino",
    "Shpioniro_Golubiro", "Chimpanzini_Bananini",
    "==", "!=", ">", "<", ">=", "<=",
    "=", "+", "-", "->", "(", ")", "[", "]", "{", "}", ",", ":", "."
};
#define TOKEN_COUNT 34
#endif
