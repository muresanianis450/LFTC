/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "brainrot.y"

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

#line 116 "brainrot.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "brainrot.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IDENTIFIER = 3,                 /* "identifier"  */
  YYSYMBOL_NUMBER = 4,                     /* "number"  */
  YYSYMBOL_STRING = 5,                     /* "string"  */
  YYSYMBOL_PEIGENGOO = 6,                  /* "Peigengoo"  */
  YYSYMBOL_GOJO_SATORU = 7,                /* "Gojo_Satoru"  */
  YYSYMBOL_SIXSEVEN = 8,                   /* "SIXSEVEN"  */
  YYSYMBOL_TRALALERO_TRALALA = 9,          /* "Tralalero_Tralala"  */
  YYSYMBOL_CAPPUCCINO_ASSASSINO = 10,      /* "Cappuccino_Assassino"  */
  YYSYMBOL_HIPOCACTUS = 11,                /* "Hipocactus"  */
  YYSYMBOL_BOMBOMBINI_GUSINI = 12,         /* "Bombombini_Gusini"  */
  YYSYMBOL_TRIPPI_TROPPI = 13,             /* "Trippi_Troppi"  */
  YYSYMBOL_BOMBARDIRO_CROCODILO = 14,      /* "Bombardiro_Crocodilo"  */
  YYSYMBOL_TUNG_TUNG_TUNG_SAHUR = 15,      /* "Tung_Tung_Tung_Sahur"  */
  YYSYMBOL_CHEESE_RATTATINO = 16,          /* "Cheese_Rattatino"  */
  YYSYMBOL_SHPIONIRO_GOLUBIRO = 17,        /* "Shpioniro_Golubiro"  */
  YYSYMBOL_CHIMPANZINI_BANANINI = 18,      /* "Chimpanzini_Bananini"  */
  YYSYMBOL_EQ = 19,                        /* "=="  */
  YYSYMBOL_NE = 20,                        /* "!="  */
  YYSYMBOL_GT = 21,                        /* ">"  */
  YYSYMBOL_LT = 22,                        /* "<"  */
  YYSYMBOL_GE = 23,                        /* ">="  */
  YYSYMBOL_LE = 24,                        /* "<="  */
  YYSYMBOL_ASSIGN = 25,                    /* "="  */
  YYSYMBOL_PLUS = 26,                      /* "+"  */
  YYSYMBOL_MINUS = 27,                     /* "-"  */
  YYSYMBOL_ARROW = 28,                     /* "->"  */
  YYSYMBOL_LPAREN = 29,                    /* "("  */
  YYSYMBOL_RPAREN = 30,                    /* ")"  */
  YYSYMBOL_LBRACKET = 31,                  /* "["  */
  YYSYMBOL_RBRACKET = 32,                  /* "]"  */
  YYSYMBOL_LBRACE = 33,                    /* "{"  */
  YYSYMBOL_RBRACE = 34,                    /* "}"  */
  YYSYMBOL_COMMA = 35,                     /* ","  */
  YYSYMBOL_COLON = 36,                     /* ":"  */
  YYSYMBOL_DOT = 37,                       /* "."  */
  YYSYMBOL_YYACCEPT = 38,                  /* $accept  */
  YYSYMBOL_program = 39,                   /* program  */
  YYSYMBOL_statements = 40,                /* statements  */
  YYSYMBOL_statement = 41,                 /* statement  */
  YYSYMBOL_const_decls = 42,               /* const_decls  */
  YYSYMBOL_const_decl = 43,                /* const_decl  */
  YYSYMBOL_const_value = 44,               /* const_value  */
  YYSYMBOL_assignment = 45,                /* assignment  */
  YYSYMBOL_input_statement = 46,           /* input_statement  */
  YYSYMBOL_print_statement = 47,           /* print_statement  */
  YYSYMBOL_print_arg = 48,                 /* print_arg  */
  YYSYMBOL_list_expression = 49,           /* list_expression  */
  YYSYMBOL_list_base = 50,                 /* list_base  */
  YYSYMBOL_list_ops = 51,                  /* list_ops  */
  YYSYMBOL_list_op = 52,                   /* list_op  */
  YYSYMBOL_list_creation = 53,             /* list_creation  */
  YYSYMBOL_record_list = 54,               /* record_list  */
  YYSYMBOL_record_list_content = 55,       /* record_list_content  */
  YYSYMBOL_more_records = 56,              /* more_records  */
  YYSYMBOL_record = 57,                    /* record  */
  YYSYMBOL_more_pairs = 58,                /* more_pairs  */
  YYSYMBOL_pair = 59,                      /* pair  */
  YYSYMBOL_filter_op = 60,                 /* filter_op  */
  YYSYMBOL_add_op = 61,                    /* add_op  */
  YYSYMBOL_remove_op = 62,                 /* remove_op  */
  YYSYMBOL_select_op = 63,                 /* select_op  */
  YYSYMBOL_identifier_list = 64,           /* identifier_list  */
  YYSYMBOL_more_identifiers = 65,          /* more_identifiers  */
  YYSYMBOL_condition = 66,                 /* condition  */
  YYSYMBOL_or_rest = 67,                   /* or_rest  */
  YYSYMBOL_and_cond = 68,                  /* and_cond  */
  YYSYMBOL_and_rest = 69,                  /* and_rest  */
  YYSYMBOL_simple_cond = 70,               /* simple_cond  */
  YYSYMBOL_field_ref = 71,                 /* field_ref  */
  YYSYMBOL_field_suffix = 72,              /* field_suffix  */
  YYSYMBOL_operator = 73,                  /* operator  */
  YYSYMBOL_value = 74,                     /* value  */
  YYSYMBOL_if_statement = 75,              /* if_statement  */
  YYSYMBOL_optional_else = 76,             /* optional_else  */
  YYSYMBOL_for_loop = 77,                  /* for_loop  */
  YYSYMBOL_statement_block = 78            /* statement_block  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   102

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  41
/* YYNRULES -- Number of rules.  */
#define YYNRULES  73
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  126

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   292


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    77,    77,    79,    80,    82,    83,    84,    85,    86,
      90,    91,    93,    95,    96,    97,    98,   102,   104,   106,
     108,   109,   113,   115,   116,   118,   119,   121,   122,   123,
     124,   127,   129,   131,   132,   134,   135,   137,   139,   140,
     142,   145,   147,   149,   151,   153,   155,   156,   161,   163,
     164,   166,   168,   169,   171,   172,   174,   176,   177,   179,
     179,   179,   180,   180,   180,   182,   183,   184,   185,   189,
     191,   192,   194,   196
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "\"identifier\"",
  "\"number\"", "\"string\"", "\"Peigengoo\"", "\"Gojo_Satoru\"",
  "\"SIXSEVEN\"", "\"Tralalero_Tralala\"", "\"Cappuccino_Assassino\"",
  "\"Hipocactus\"", "\"Bombombini_Gusini\"", "\"Trippi_Troppi\"",
  "\"Bombardiro_Crocodilo\"", "\"Tung_Tung_Tung_Sahur\"",
  "\"Cheese_Rattatino\"", "\"Shpioniro_Golubiro\"",
  "\"Chimpanzini_Bananini\"", "\"==\"", "\"!=\"", "\">\"", "\"<\"",
  "\">=\"", "\"<=\"", "\"=\"", "\"+\"", "\"-\"", "\"->\"", "\"(\"",
  "\")\"", "\"[\"", "\"]\"", "\"{\"", "\"}\"", "\",\"", "\":\"", "\".\"",
  "$accept", "program", "statements", "statement", "const_decls",
  "const_decl", "const_value", "assignment", "input_statement",
  "print_statement", "print_arg", "list_expression", "list_base",
  "list_ops", "list_op", "list_creation", "record_list",
  "record_list_content", "more_records", "record", "more_pairs", "pair",
  "filter_op", "add_op", "remove_op", "select_op", "identifier_list",
  "more_identifiers", "condition", "or_rest", "and_cond", "and_rest",
  "simple_cond", "field_ref", "field_suffix", "operator", "value",
  "if_statement", "optional_else", "for_loop", "statement_block", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-97)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -10,    13,    21,    19,   -10,     2,   -97,    14,     1,    20,
      46,    35,    19,   -97,   -97,   -97,   -97,   -97,   -97,    32,
      26,     4,     1,    19,    31,    37,    -9,    41,   -97,   -97,
      27,   -97,   -97,    -2,   -97,   -97,   -97,    19,   -97,   -97,
     -97,   -97,   -97,   -97,    52,   -97,    28,    19,    49,     1,
     -97,     1,   -97,   -97,   -97,   -97,   -97,   -97,   -97,    42,
      26,    29,     1,    58,    59,    34,   -97,    -2,   -97,   -97,
     -97,   -97,   -97,   -97,   -97,   -97,    19,    53,    31,    37,
     -97,   -97,   -97,   -97,   -97,    19,    33,    38,   -97,    40,
     -97,    64,   -97,   -97,   -97,   -97,   -97,    60,    66,    43,
      39,   -97,    42,    44,    47,   -97,    36,    45,   -97,    33,
     -97,   -97,    67,   -97,   -97,    42,    66,    50,    39,    44,
     -97,    45,   -97,   -97,   -97,   -97
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
      11,     0,     0,     0,    11,     0,     1,     0,     0,     0,
       0,     0,     4,     5,     6,     9,     7,     8,    10,     0,
       0,    58,     0,     0,    50,    53,     0,     0,    24,    21,
       0,    19,    20,    26,    23,    18,     2,     4,    16,    14,
      13,    15,    12,    17,     0,    56,     0,     4,    71,     0,
      48,     0,    51,    59,    60,    61,    62,    63,    64,     0,
       0,     0,     0,     0,     0,     0,    22,    26,    27,    28,
      29,    30,     3,    57,    55,    73,     0,     0,    50,    53,
      66,    65,    67,    68,    54,     0,    34,     0,    41,     0,
      43,     0,    25,    70,    69,    49,    52,     0,     0,     0,
      36,    31,     0,    47,     0,    72,     0,    39,    32,     0,
      33,    42,     0,    45,    44,     0,     0,     0,    36,    47,
      40,    39,    37,    35,    46,    38
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -97,   -97,   -30,    -3,    72,   -97,   -97,   -97,   -97,   -97,
     -97,   -18,   -97,    11,   -97,   -97,   -97,   -97,   -37,   -26,
     -36,   -29,   -97,   -97,   -97,   -97,   -97,   -33,   -19,    10,
      48,    12,    51,   -58,   -97,   -97,   -96,   -97,   -97,   -97,
     -67
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,    36,    37,     3,     4,    42,    13,    14,    15,
      31,    32,    33,    66,    67,    34,    87,    99,   110,   100,
     117,   107,    68,    69,    70,    71,   104,   113,    23,    50,
      24,    52,    25,    26,    45,    59,    84,    16,    77,    17,
      48
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      12,    83,    43,    46,    21,    62,   111,    72,     1,    93,
      53,    54,    55,    56,    57,    58,     5,    75,    97,   120,
      47,     6,     7,    27,    63,    64,    65,    19,     8,    28,
      22,     9,    30,    10,    11,    38,    39,    40,    35,    20,
      41,    44,    85,    88,    83,    21,    80,    81,    49,    28,
      82,    29,    30,    51,    60,    73,    61,    83,    74,    76,
      86,    89,    90,    91,    94,   102,    98,   103,   101,   106,
     119,   105,   115,    47,   109,   108,    18,   114,    92,   112,
     116,   123,    47,   118,   122,   125,   124,   121,    95,     0,
       0,    96,     0,     0,     0,     0,     0,    78,     0,     0,
       0,     0,    79
};

static const yytype_int8 yycheck[] =
{
       3,    59,    20,    22,     3,     7,   102,    37,    18,    76,
      19,    20,    21,    22,    23,    24,     3,    47,    85,   115,
      23,     0,     3,     3,    26,    27,    28,    25,     9,     3,
      29,    12,     6,    14,    15,     3,     4,     5,     3,    25,
       8,    37,    60,    62,   102,     3,     4,     5,    17,     3,
       8,     5,     6,    16,    13,     3,    29,   115,    30,    10,
      31,     3,     3,    29,    11,    25,    33,     3,    30,     3,
       3,    11,    36,    76,    35,    32,     4,    30,    67,    35,
      35,   118,    85,   109,    34,   121,   119,   116,    78,    -1,
      -1,    79,    -1,    -1,    -1,    -1,    -1,    49,    -1,    -1,
      -1,    -1,    51
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    18,    39,    42,    43,     3,     0,     3,     9,    12,
      14,    15,    41,    45,    46,    47,    75,    77,    42,    25,
      25,     3,    29,    66,    68,    70,    71,     3,     3,     5,
       6,    48,    49,    50,    53,     3,    40,    41,     3,     4,
       5,     8,    44,    49,    37,    72,    66,    41,    78,    17,
      67,    16,    69,    19,    20,    21,    22,    23,    24,    73,
      13,    29,     7,    26,    27,    28,    51,    52,    60,    61,
      62,    63,    40,     3,    30,    40,    10,    76,    68,    70,
       4,     5,     8,    71,    74,    49,    31,    54,    66,     3,
       3,    29,    51,    78,    11,    67,    69,    78,    33,    55,
      57,    30,    25,     3,    64,    11,     3,    59,    32,    35,
      56,    74,    35,    65,    30,    36,    35,    58,    57,     3,
      74,    59,    34,    56,    65,    58
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    38,    39,    40,    40,    41,    41,    41,    41,    41,
      42,    42,    43,    44,    44,    44,    44,    45,    46,    47,
      48,    48,    49,    50,    50,    51,    51,    52,    52,    52,
      52,    53,    54,    55,    55,    56,    56,    57,    58,    58,
      59,    60,    61,    62,    63,    64,    65,    65,    66,    67,
      67,    68,    69,    69,    70,    70,    71,    72,    72,    73,
      73,    73,    73,    73,    73,    74,    74,    74,    74,    75,
      76,    76,    77,    78
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     2,     0,     1,     1,     1,     1,     1,
       2,     0,     4,     1,     1,     1,     1,     3,     2,     2,
       1,     1,     2,     1,     1,     2,     0,     1,     1,     1,
       1,     4,     3,     2,     0,     3,     0,     4,     3,     0,
       3,     2,     4,     2,     4,     2,     3,     0,     2,     3,
       0,     2,     3,     0,     3,     3,     2,     2,     0,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     5,
       2,     0,     6,     2
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= END_OF_INPUT)
    {
      yychar = END_OF_INPUT;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: const_decls statement statements  */
#line 77 "brainrot.y"
                                                                    { PROD(1); }
#line 1542 "brainrot.tab.c"
    break;

  case 3: /* statements: statement statements  */
#line 79 "brainrot.y"
                                                                    { PROD(2); }
#line 1548 "brainrot.tab.c"
    break;

  case 4: /* statements: %empty  */
#line 80 "brainrot.y"
                                                                    { PROD(3); }
#line 1554 "brainrot.tab.c"
    break;

  case 5: /* statement: assignment  */
#line 82 "brainrot.y"
                                                                    { PROD(4); }
#line 1560 "brainrot.tab.c"
    break;

  case 6: /* statement: input_statement  */
#line 83 "brainrot.y"
                                                                    { PROD(5); }
#line 1566 "brainrot.tab.c"
    break;

  case 7: /* statement: if_statement  */
#line 84 "brainrot.y"
                                                                    { PROD(6); }
#line 1572 "brainrot.tab.c"
    break;

  case 8: /* statement: for_loop  */
#line 85 "brainrot.y"
                                                                    { PROD(7); }
#line 1578 "brainrot.tab.c"
    break;

  case 9: /* statement: print_statement  */
#line 86 "brainrot.y"
                                                                    { PROD(8); }
#line 1584 "brainrot.tab.c"
    break;

  case 10: /* const_decls: const_decl const_decls  */
#line 90 "brainrot.y"
                                                                    { PROD(9); }
#line 1590 "brainrot.tab.c"
    break;

  case 11: /* const_decls: %empty  */
#line 91 "brainrot.y"
                                                                    { PROD(10); }
#line 1596 "brainrot.tab.c"
    break;

  case 12: /* const_decl: "Chimpanzini_Bananini" "identifier" "=" const_value  */
#line 93 "brainrot.y"
                                                                     { PROD(11); }
#line 1602 "brainrot.tab.c"
    break;

  case 13: /* const_value: "string"  */
#line 95 "brainrot.y"
                                                                    { PROD(12); }
#line 1608 "brainrot.tab.c"
    break;

  case 14: /* const_value: "number"  */
#line 96 "brainrot.y"
                                                                    { PROD(13); }
#line 1614 "brainrot.tab.c"
    break;

  case 15: /* const_value: "SIXSEVEN"  */
#line 97 "brainrot.y"
                                                                    { PROD(14); }
#line 1620 "brainrot.tab.c"
    break;

  case 16: /* const_value: "identifier"  */
#line 98 "brainrot.y"
                                                                    { PROD(15); }
#line 1626 "brainrot.tab.c"
    break;

  case 17: /* assignment: "identifier" "=" list_expression  */
#line 102 "brainrot.y"
                                                                    { PROD(16); }
#line 1632 "brainrot.tab.c"
    break;

  case 18: /* input_statement: "Tung_Tung_Tung_Sahur" "identifier"  */
#line 104 "brainrot.y"
                                                                    { PROD(17); }
#line 1638 "brainrot.tab.c"
    break;

  case 19: /* print_statement: "Bombardiro_Crocodilo" print_arg  */
#line 106 "brainrot.y"
                                                                    { PROD(18); }
#line 1644 "brainrot.tab.c"
    break;

  case 20: /* print_arg: list_expression  */
#line 108 "brainrot.y"
                                                                    { PROD(19); }
#line 1650 "brainrot.tab.c"
    break;

  case 21: /* print_arg: "string"  */
#line 109 "brainrot.y"
                                                                    { PROD(20); }
#line 1656 "brainrot.tab.c"
    break;

  case 22: /* list_expression: list_base list_ops  */
#line 113 "brainrot.y"
                                                                    { PROD(21); }
#line 1662 "brainrot.tab.c"
    break;

  case 23: /* list_base: list_creation  */
#line 115 "brainrot.y"
                                                                    { PROD(22); }
#line 1668 "brainrot.tab.c"
    break;

  case 24: /* list_base: "identifier"  */
#line 116 "brainrot.y"
                                                                    { PROD(23); }
#line 1674 "brainrot.tab.c"
    break;

  case 25: /* list_ops: list_op list_ops  */
#line 118 "brainrot.y"
                                                                    { PROD(24); }
#line 1680 "brainrot.tab.c"
    break;

  case 26: /* list_ops: %empty  */
#line 119 "brainrot.y"
                                                                    { PROD(25); }
#line 1686 "brainrot.tab.c"
    break;

  case 27: /* list_op: filter_op  */
#line 121 "brainrot.y"
                                                                    { PROD(26); }
#line 1692 "brainrot.tab.c"
    break;

  case 28: /* list_op: add_op  */
#line 122 "brainrot.y"
                                                                    { PROD(27); }
#line 1698 "brainrot.tab.c"
    break;

  case 29: /* list_op: remove_op  */
#line 123 "brainrot.y"
                                                                    { PROD(28); }
#line 1704 "brainrot.tab.c"
    break;

  case 30: /* list_op: select_op  */
#line 124 "brainrot.y"
                                                                    { PROD(29); }
#line 1710 "brainrot.tab.c"
    break;

  case 31: /* list_creation: "Peigengoo" "(" record_list ")"  */
#line 127 "brainrot.y"
                                                                    { PROD(30); }
#line 1716 "brainrot.tab.c"
    break;

  case 32: /* record_list: "[" record_list_content "]"  */
#line 129 "brainrot.y"
                                                                    { PROD(31); }
#line 1722 "brainrot.tab.c"
    break;

  case 33: /* record_list_content: record more_records  */
#line 131 "brainrot.y"
                                                                    { PROD(32); }
#line 1728 "brainrot.tab.c"
    break;

  case 34: /* record_list_content: %empty  */
#line 132 "brainrot.y"
                                                                    { PROD(33); }
#line 1734 "brainrot.tab.c"
    break;

  case 35: /* more_records: "," record more_records  */
#line 134 "brainrot.y"
                                                                    { PROD(34); }
#line 1740 "brainrot.tab.c"
    break;

  case 36: /* more_records: %empty  */
#line 135 "brainrot.y"
                                                                    { PROD(35); }
#line 1746 "brainrot.tab.c"
    break;

  case 37: /* record: "{" pair more_pairs "}"  */
#line 137 "brainrot.y"
                                                                    { PROD(36); }
#line 1752 "brainrot.tab.c"
    break;

  case 38: /* more_pairs: "," pair more_pairs  */
#line 139 "brainrot.y"
                                                                    { PROD(37); }
#line 1758 "brainrot.tab.c"
    break;

  case 39: /* more_pairs: %empty  */
#line 140 "brainrot.y"
                                                                    { PROD(38); }
#line 1764 "brainrot.tab.c"
    break;

  case 40: /* pair: "identifier" ":" value  */
#line 142 "brainrot.y"
                                                                    { PROD(39); }
#line 1770 "brainrot.tab.c"
    break;

  case 41: /* filter_op: "Gojo_Satoru" condition  */
#line 145 "brainrot.y"
                                                                    { PROD(40); }
#line 1776 "brainrot.tab.c"
    break;

  case 42: /* add_op: "+" "identifier" "=" value  */
#line 147 "brainrot.y"
                                                                    { PROD(41); }
#line 1782 "brainrot.tab.c"
    break;

  case 43: /* remove_op: "-" "identifier"  */
#line 149 "brainrot.y"
                                                                    { PROD(42); }
#line 1788 "brainrot.tab.c"
    break;

  case 44: /* select_op: "->" "(" identifier_list ")"  */
#line 151 "brainrot.y"
                                                                    { PROD(43); }
#line 1794 "brainrot.tab.c"
    break;

  case 45: /* identifier_list: "identifier" more_identifiers  */
#line 153 "brainrot.y"
                                                                    { PROD(44); }
#line 1800 "brainrot.tab.c"
    break;

  case 46: /* more_identifiers: "," "identifier" more_identifiers  */
#line 155 "brainrot.y"
                                                                    { PROD(45); }
#line 1806 "brainrot.tab.c"
    break;

  case 47: /* more_identifiers: %empty  */
#line 156 "brainrot.y"
                                                                    { PROD(46); }
#line 1812 "brainrot.tab.c"
    break;

  case 48: /* condition: and_cond or_rest  */
#line 161 "brainrot.y"
                                                                    { PROD(47); }
#line 1818 "brainrot.tab.c"
    break;

  case 49: /* or_rest: "Shpioniro_Golubiro" and_cond or_rest  */
#line 163 "brainrot.y"
                                                                    { PROD(48); }
#line 1824 "brainrot.tab.c"
    break;

  case 50: /* or_rest: %empty  */
#line 164 "brainrot.y"
                                                                    { PROD(49); }
#line 1830 "brainrot.tab.c"
    break;

  case 51: /* and_cond: simple_cond and_rest  */
#line 166 "brainrot.y"
                                                                    { PROD(50); }
#line 1836 "brainrot.tab.c"
    break;

  case 52: /* and_rest: "Cheese_Rattatino" simple_cond and_rest  */
#line 168 "brainrot.y"
                                                                    { PROD(51); }
#line 1842 "brainrot.tab.c"
    break;

  case 53: /* and_rest: %empty  */
#line 169 "brainrot.y"
                                                                    { PROD(52); }
#line 1848 "brainrot.tab.c"
    break;

  case 54: /* simple_cond: field_ref operator value  */
#line 171 "brainrot.y"
                                                                    { PROD(53); }
#line 1854 "brainrot.tab.c"
    break;

  case 55: /* simple_cond: "(" condition ")"  */
#line 172 "brainrot.y"
                                                                    { PROD(54); }
#line 1860 "brainrot.tab.c"
    break;

  case 56: /* field_ref: "identifier" field_suffix  */
#line 174 "brainrot.y"
                                                                    { PROD(55); }
#line 1866 "brainrot.tab.c"
    break;

  case 57: /* field_suffix: "." "identifier"  */
#line 176 "brainrot.y"
                                                                    { PROD(56); }
#line 1872 "brainrot.tab.c"
    break;

  case 58: /* field_suffix: %empty  */
#line 177 "brainrot.y"
                                                                    { PROD(57); }
#line 1878 "brainrot.tab.c"
    break;

  case 59: /* operator: "=="  */
#line 179 "brainrot.y"
                        { PROD(58); }
#line 1884 "brainrot.tab.c"
    break;

  case 60: /* operator: "!="  */
#line 179 "brainrot.y"
                                             { PROD(59); }
#line 1890 "brainrot.tab.c"
    break;

  case 61: /* operator: ">"  */
#line 179 "brainrot.y"
                                                                 { PROD(60); }
#line 1896 "brainrot.tab.c"
    break;

  case 62: /* operator: "<"  */
#line 180 "brainrot.y"
                       { PROD(61); }
#line 1902 "brainrot.tab.c"
    break;

  case 63: /* operator: ">="  */
#line 180 "brainrot.y"
                                            { PROD(62); }
#line 1908 "brainrot.tab.c"
    break;

  case 64: /* operator: "<="  */
#line 180 "brainrot.y"
                                                                 { PROD(63); }
#line 1914 "brainrot.tab.c"
    break;

  case 65: /* value: "string"  */
#line 182 "brainrot.y"
                                                                    { PROD(64); }
#line 1920 "brainrot.tab.c"
    break;

  case 66: /* value: "number"  */
#line 183 "brainrot.y"
                                                                    { PROD(65); }
#line 1926 "brainrot.tab.c"
    break;

  case 67: /* value: "SIXSEVEN"  */
#line 184 "brainrot.y"
                                                                    { PROD(66); }
#line 1932 "brainrot.tab.c"
    break;

  case 68: /* value: field_ref  */
#line 185 "brainrot.y"
                                                                    { PROD(67); }
#line 1938 "brainrot.tab.c"
    break;

  case 69: /* if_statement: "Tralalero_Tralala" condition statement_block optional_else "Hipocactus"  */
#line 189 "brainrot.y"
                                                                                            { PROD(68); }
#line 1944 "brainrot.tab.c"
    break;

  case 70: /* optional_else: "Cappuccino_Assassino" statement_block  */
#line 191 "brainrot.y"
                                                                    { PROD(69); }
#line 1950 "brainrot.tab.c"
    break;

  case 71: /* optional_else: %empty  */
#line 192 "brainrot.y"
                                                                    { PROD(70); }
#line 1956 "brainrot.tab.c"
    break;

  case 72: /* for_loop: "Bombombini_Gusini" "identifier" "Trippi_Troppi" list_expression statement_block "Hipocactus"  */
#line 194 "brainrot.y"
                                                                                                               { PROD(71); }
#line 1962 "brainrot.tab.c"
    break;

  case 73: /* statement_block: statement statements  */
#line 196 "brainrot.y"
                                                                    { PROD(72); }
#line 1968 "brainrot.tab.c"
    break;


#line 1972 "brainrot.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= END_OF_INPUT)
        {
          /* Return failure if at end of input.  */
          if (yychar == END_OF_INPUT)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 199 "brainrot.y"


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
