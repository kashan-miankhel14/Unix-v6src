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
#line 1 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(const char *s);
int yylex();

extern FILE *yyin;

/* AST Node Structure */
struct ASTNode {
    char *type;
    char *value;
    struct ASTNode *left;
    struct ASTNode *right;
    struct ASTNode *next;  /* For statement lists */
};

/* Function to create a new AST node */
struct ASTNode* createNode(char* type, char* value, struct ASTNode* left, struct ASTNode* right) {
    struct ASTNode* node = (struct ASTNode*)malloc(sizeof(struct ASTNode));
    node->type = strdup(type);
    node->value = value ? strdup(value) : NULL;
    node->left = left;
    node->right = right;
    node->next = NULL;
    return node;
}

/* Counter for indentation */
int indent = 0;

/* Function to print AST with indentation */
void printAST(struct ASTNode* node, int level) {
    if (node == NULL) return;
    
    for (int i = 0; i < level; i++) printf("  ");
    
    if (node->value) {
        printf("[%s: %s]\n", node->type, node->value);
    } else {
        printf("[%s]\n", node->type);
    }
    
    if (node->left) printAST(node->left, level + 1);
    if (node->right) printAST(node->right, level + 1);
    if (node->next) printAST(node->next, level);
}

/* Global AST root */
struct ASTNode* astRoot = NULL;

/* Function to generate dot file for graph visualization */
void generateDotFile(struct ASTNode* root, const char* filename) {
    FILE* fp = fopen(filename, "w");
    if (!fp) return;
    
    fprintf(fp, "digraph AST {\n");
    fprintf(fp, "  node [shape=box, style=filled, fillcolor=lightblue];\n");
    
    /* Helper function to write nodes and edges */
    int nodeCount = 0;
    
    void writeNode(struct ASTNode* node, int* count) {
        if (!node) return;
        
        int myId = (*count)++;
        char label[256];
        if (node->value) {
            snprintf(label, sizeof(label), "%s\\n%s", node->type, node->value);
        } else {
            snprintf(label, sizeof(label), "%s", node->type);
        }
        
        fprintf(fp, "  n%d [label=\"%s\"];\n", myId, label);
        
        if (node->left) {
            int leftId = *count;
            writeNode(node->left, count);
            fprintf(fp, "  n%d -> n%d;\n", myId, leftId);
        }
        if (node->right) {
            int rightId = *count;
            writeNode(node->right, count);
            fprintf(fp, "  n%d -> n%d;\n", myId, rightId);
        }
        if (node->next) {
            int nextId = *count;
            writeNode(node->next, count);
            fprintf(fp, "  n%d -> n%d [style=dashed, color=red];\n", myId, nextId);
        }
    }
    
    writeNode(root, &nodeCount);
    fprintf(fp, "}\n");
    fclose(fp);
    printf("AST dot file generated: %s\n", filename);
}


#line 173 "parser.tab.c"

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

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IF = 3,                         /* IF  */
  YYSYMBOL_ELSE = 4,                       /* ELSE  */
  YYSYMBOL_WHILE = 5,                      /* WHILE  */
  YYSYMBOL_FOR = 6,                        /* FOR  */
  YYSYMBOL_DO = 7,                         /* DO  */
  YYSYMBOL_RETURN = 8,                     /* RETURN  */
  YYSYMBOL_BREAK = 9,                      /* BREAK  */
  YYSYMBOL_CONTINUE = 10,                  /* CONTINUE  */
  YYSYMBOL_GOTO = 11,                      /* GOTO  */
  YYSYMBOL_SWITCH = 12,                    /* SWITCH  */
  YYSYMBOL_CASE = 13,                      /* CASE  */
  YYSYMBOL_TYPE = 14,                      /* TYPE  */
  YYSYMBOL_STRUCT = 15,                    /* STRUCT  */
  YYSYMBOL_UNION = 16,                     /* UNION  */
  YYSYMBOL_ENUM = 17,                      /* ENUM  */
  YYSYMBOL_STATIC = 18,                    /* STATIC  */
  YYSYMBOL_REGISTER = 19,                  /* REGISTER  */
  YYSYMBOL_EXTERN = 20,                    /* EXTERN  */
  YYSYMBOL_CONST = 21,                     /* CONST  */
  YYSYMBOL_EQ = 22,                        /* EQ  */
  YYSYMBOL_NE = 23,                        /* NE  */
  YYSYMBOL_LE = 24,                        /* LE  */
  YYSYMBOL_GE = 25,                        /* GE  */
  YYSYMBOL_AND = 26,                       /* AND  */
  YYSYMBOL_OR = 27,                        /* OR  */
  YYSYMBOL_INC = 28,                       /* INC  */
  YYSYMBOL_DEC = 29,                       /* DEC  */
  YYSYMBOL_PLUSEQ = 30,                    /* PLUSEQ  */
  YYSYMBOL_MINUSEQ = 31,                   /* MINUSEQ  */
  YYSYMBOL_SHL = 32,                       /* SHL  */
  YYSYMBOL_SHR = 33,                       /* SHR  */
  YYSYMBOL_ARROW = 34,                     /* ARROW  */
  YYSYMBOL_NUMBER = 35,                    /* NUMBER  */
  YYSYMBOL_IDENTIFIER = 36,                /* IDENTIFIER  */
  YYSYMBOL_STRING = 37,                    /* STRING  */
  YYSYMBOL_CHAR = 38,                      /* CHAR  */
  YYSYMBOL_39_then_ = 39,                  /* "then"  */
  YYSYMBOL_40_ = 40,                       /* '='  */
  YYSYMBOL_41_ = 41,                       /* '<'  */
  YYSYMBOL_42_ = 42,                       /* '>'  */
  YYSYMBOL_43_ = 43,                       /* '+'  */
  YYSYMBOL_44_ = 44,                       /* '-'  */
  YYSYMBOL_45_ = 45,                       /* '*'  */
  YYSYMBOL_46_ = 46,                       /* '/'  */
  YYSYMBOL_47_ = 47,                       /* '%'  */
  YYSYMBOL_48_ = 48,                       /* '&'  */
  YYSYMBOL_49_ = 49,                       /* '!'  */
  YYSYMBOL_50_ = 50,                       /* '~'  */
  YYSYMBOL_51_ = 51,                       /* '#'  */
  YYSYMBOL_52_ = 52,                       /* ';'  */
  YYSYMBOL_53_ = 53,                       /* '('  */
  YYSYMBOL_54_ = 54,                       /* ')'  */
  YYSYMBOL_55_ = 55,                       /* ','  */
  YYSYMBOL_56_ = 56,                       /* '{'  */
  YYSYMBOL_57_ = 57,                       /* '}'  */
  YYSYMBOL_58_ = 58,                       /* ':'  */
  YYSYMBOL_YYACCEPT = 59,                  /* $accept  */
  YYSYMBOL_program = 60,                   /* program  */
  YYSYMBOL_declaration = 61,               /* declaration  */
  YYSYMBOL_preproc_decl = 62,              /* preproc_decl  */
  YYSYMBOL_var_decl = 63,                  /* var_decl  */
  YYSYMBOL_type_specifier = 64,            /* type_specifier  */
  YYSYMBOL_pointer = 65,                   /* pointer  */
  YYSYMBOL_func_decl = 66,                 /* func_decl  */
  YYSYMBOL_param_list = 67,                /* param_list  */
  YYSYMBOL_compound_statement = 68,        /* compound_statement  */
  YYSYMBOL_statement_list = 69,            /* statement_list  */
  YYSYMBOL_statement = 70,                 /* statement  */
  YYSYMBOL_if_statement = 71,              /* if_statement  */
  YYSYMBOL_while_statement = 72,           /* while_statement  */
  YYSYMBOL_for_statement = 73,             /* for_statement  */
  YYSYMBOL_return_statement = 74,          /* return_statement  */
  YYSYMBOL_expr = 75,                      /* expr  */
  YYSYMBOL_arg_list = 76                   /* arg_list  */
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
typedef yytype_uint8 yy_state_t;

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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

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
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   782

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  59
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  18
/* YYNRULES -- Number of rules.  */
#define YYNRULES  76
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  161

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   294


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
       2,     2,     2,    49,     2,    51,     2,    47,    48,     2,
      53,    54,    45,    43,    55,    44,     2,    46,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    58,    52,
      41,    40,    42,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    56,     2,    57,    50,     2,     2,     2,
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
      35,    36,    37,    38,    39
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   140,   140,   143,   150,   165,   167,   169,   174,   179,
     187,   192,   197,   205,   209,   213,   220,   222,   227,   232,
     241,   242,   246,   261,   266,   274,   276,   290,   292,   294,
     296,   298,   300,   302,   307,   309,   314,   322,   327,   335,
     340,   348,   355,   365,   370,   378,   382,   388,   392,   396,
     400,   405,   410,   415,   420,   425,   430,   435,   440,   445,
     450,   455,   460,   465,   470,   475,   480,   485,   490,   495,
     500,   505,   510,   515,   524,   525,   527
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "IF", "ELSE", "WHILE",
  "FOR", "DO", "RETURN", "BREAK", "CONTINUE", "GOTO", "SWITCH", "CASE",
  "TYPE", "STRUCT", "UNION", "ENUM", "STATIC", "REGISTER", "EXTERN",
  "CONST", "EQ", "NE", "LE", "GE", "AND", "OR", "INC", "DEC", "PLUSEQ",
  "MINUSEQ", "SHL", "SHR", "ARROW", "NUMBER", "IDENTIFIER", "STRING",
  "CHAR", "\"then\"", "'='", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'",
  "'%'", "'&'", "'!'", "'~'", "'#'", "';'", "'('", "')'", "','", "'{'",
  "'}'", "':'", "$accept", "program", "declaration", "preproc_decl",
  "var_decl", "type_specifier", "pointer", "func_decl", "param_list",
  "compound_statement", "statement_list", "statement", "if_statement",
  "while_statement", "for_statement", "return_statement", "expr",
  "arg_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-131)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -131,   133,  -131,   -22,   -18,   -15,   241,   685,     5,   -34,
      29,   729,   729,  -131,   -28,  -131,  -131,   729,   729,   729,
       9,  -131,   729,   169,  -131,  -131,  -131,    14,  -131,  -131,
    -131,  -131,  -131,  -131,  -131,    69,   729,   729,   707,     6,
     -16,  -131,    48,     1,  -131,   474,    15,    13,  -131,     6,
      42,  -131,  -131,    -9,   241,    -7,    -7,    -7,   -31,   276,
    -131,   205,  -131,   -36,   729,   729,   729,   729,   729,   729,
    -131,  -131,   729,   729,   729,   729,   729,   729,   729,   729,
     729,   729,  -131,   309,   342,   729,   505,   729,    26,  -131,
    -131,    29,  -131,  -131,    28,    46,    -8,   629,     2,  -131,
    -131,    49,  -131,  -131,  -131,   729,  -131,   267,   267,    59,
      59,   665,   639,   629,   629,   629,    59,    59,    79,    79,
      -7,    -7,    -7,   241,   241,   536,   729,   729,     4,  -131,
    -131,    30,    29,  -131,   729,    47,   567,    80,  -131,   729,
     598,   375,    30,  -131,    83,   629,  -131,  -131,   241,   408,
     729,    68,  -131,  -131,  -131,   241,   441,  -131,  -131,   241,
    -131
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    46,    45,    47,    48,     0,     0,     0,
       0,    34,     0,     0,     3,     7,     5,     0,     6,    27,
       4,    28,    29,    30,    31,     0,     0,     0,     0,    13,
      45,    32,     0,    45,    43,     0,     0,     0,    16,    14,
       0,    68,    70,    20,     0,    73,    72,    64,     0,     0,
      24,     0,    25,     0,     0,     0,     0,     0,     0,     0,
      69,    71,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    33,     0,     0,     0,     0,    74,     0,    44,
      35,    20,    17,    15,     0,     0,     0,    75,     0,    36,
       9,     0,    49,    23,    26,     0,    10,    60,    61,    58,
      59,    62,    63,    66,    67,    65,    56,    57,    51,    52,
      53,    54,    55,     0,     0,     0,     0,     0,     0,    12,
      21,     0,     0,    50,     0,     0,     0,    37,    39,     0,
       0,     0,     0,    19,     0,    76,     8,    11,     0,     0,
       0,     0,    18,    22,    38,     0,     0,    40,    42,     0,
      41
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -131,  -131,  -131,  -131,   126,    -1,   -25,  -131,    37,  -130,
    -131,    -6,  -131,  -131,  -131,  -131,    -4,  -131
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,    24,    25,    41,    27,    49,    28,    96,    29,
      61,    30,    31,    32,    33,    34,    35,    98
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      42,   143,    47,    45,   105,    39,   100,    51,    52,    50,
     101,    48,   152,    55,    56,    57,   106,    62,    59,    11,
      12,    70,    71,    92,    93,    53,    13,    43,    15,    16,
      54,    36,    83,    84,    86,    37,    17,    87,    38,    18,
      19,    46,    54,    39,    22,    58,   131,   132,    99,    97,
      63,    48,    95,    88,    87,   104,   133,   134,   142,   132,
     107,   108,   109,   110,   111,   112,    91,    90,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,    94,   127,
     129,   125,   130,    97,   148,   135,    23,    70,    71,   146,
      95,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,   136,    77,    78,    79,    80,    81,    70,    71,    74,
      75,    76,    77,    78,    79,    80,    81,   137,   138,   153,
     157,    82,   140,   141,    79,    80,    81,    26,   128,     0,
     145,   144,     0,     2,     0,   149,     3,     0,     4,     5,
       6,     7,   154,     0,     8,     0,   156,     9,     0,   158,
       0,    10,     0,   160,     0,     0,     0,     0,     0,     0,
       0,    11,    12,     0,     0,     0,     0,     0,    13,    14,
      15,    16,     3,     0,     4,     5,     6,     7,    17,     0,
       8,    18,    19,    39,    20,    21,    22,    10,     0,    23,
       0,     0,     0,     0,     0,     0,     0,    11,    12,     0,
       0,     0,     0,     0,    13,    40,    15,    16,     3,     0,
       4,     5,     6,     7,    17,     0,     8,    18,    19,    39,
       0,    21,    22,    10,     0,    23,    60,     0,     0,     0,
       0,     0,     0,    11,    12,     0,     0,     0,     0,     0,
      13,    40,    15,    16,     3,     0,     4,     5,     6,     7,
      17,     0,     8,    18,    19,    39,     0,    21,    22,    10,
       0,    23,   103,     0,     0,     0,     0,     0,     0,    11,
      12,     0,     0,     0,     0,     0,    13,    40,    15,    16,
       0,     0,     0,     0,     0,     0,    17,     0,     0,    18,
      19,    66,    67,    21,    22,    70,    71,    23,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    75,    76,
      77,    78,    79,    80,    81,     0,    74,    75,    76,    77,
      78,    79,    80,    81,     0,     0,     0,     0,     0,     0,
     102,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,     0,     0,     0,     0,     0,     0,     0,     0,    74,
      75,    76,    77,    78,    79,    80,    81,     0,     0,     0,
       0,     0,     0,   123,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,     0,     0,     0,     0,     0,     0,
       0,     0,    74,    75,    76,    77,    78,    79,    80,    81,
       0,     0,     0,     0,     0,     0,   124,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,     0,     0,     0,
       0,     0,     0,     0,     0,    74,    75,    76,    77,    78,
      79,    80,    81,     0,     0,     0,     0,     0,     0,   151,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
       0,     0,     0,     0,     0,     0,     0,     0,    74,    75,
      76,    77,    78,    79,    80,    81,     0,     0,     0,     0,
       0,     0,   155,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,     0,     0,     0,     0,     0,     0,     0,
       0,    74,    75,    76,    77,    78,    79,    80,    81,     0,
       0,     0,     0,     0,     0,   159,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,     0,     0,     0,     0,
       0,     0,     0,     0,    74,    75,    76,    77,    78,    79,
      80,    81,     0,     0,     0,     0,    89,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,     0,     0,     0,
       0,     0,     0,     0,     0,    74,    75,    76,    77,    78,
      79,    80,    81,     0,     0,     0,     0,   126,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,     0,     0,
       0,     0,     0,     0,     0,     0,    74,    75,    76,    77,
      78,    79,    80,    81,     0,     0,     0,     0,   139,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,     0,
       0,     0,     0,     0,     0,     0,     0,    74,    75,    76,
      77,    78,    79,    80,    81,     0,     0,     0,     0,   147,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
       0,     0,     0,     0,     0,     0,     0,     0,    74,    75,
      76,    77,    78,    79,    80,    81,     0,     0,     0,     0,
     150,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    64,    65,    66,    67,    68,     0,    70,    71,    74,
      75,    76,    77,    78,    79,    80,    81,     0,     0,     0,
      75,    76,    77,    78,    79,    80,    81,    64,    65,    66,
      67,     0,     0,    70,    71,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    75,    76,    77,    78,
      79,    80,    81,    11,    12,     0,     0,     0,     0,     0,
      13,    43,    15,    16,     0,     0,     0,     0,     0,     0,
      17,     0,     0,    18,    19,    11,    12,    44,    22,     0,
       0,     0,    13,    43,    15,    16,     0,     0,     0,     0,
       0,     0,    17,     0,     0,    18,    19,    11,    12,    85,
      22,     0,     0,     0,    13,    43,    15,    16,     0,     0,
       0,     0,     0,     0,    17,     0,     0,    18,    19,     0,
       0,     0,    22
};

static const yytype_int16 yycheck[] =
{
       6,   131,    36,     7,    40,    14,    37,    11,    12,    10,
      41,    45,   142,    17,    18,    19,    52,    23,    22,    28,
      29,    28,    29,    48,    49,    53,    35,    36,    37,    38,
      58,    53,    36,    37,    38,    53,    45,    53,    53,    48,
      49,    36,    58,    14,    53,    36,    54,    55,    54,    53,
      36,    45,    53,     5,    53,    61,    54,    55,    54,    55,
      64,    65,    66,    67,    68,    69,    53,    52,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    36,    53,
      52,    85,    36,    87,     4,    36,    56,    28,    29,    42,
      91,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,   105,    43,    44,    45,    46,    47,    28,    29,    40,
      41,    42,    43,    44,    45,    46,    47,   123,   124,    36,
      52,    52,   126,   127,    45,    46,    47,     1,    91,    -1,
     134,   132,    -1,     0,    -1,   139,     3,    -1,     5,     6,
       7,     8,   148,    -1,    11,    -1,   150,    14,    -1,   155,
      -1,    18,    -1,   159,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    28,    29,    -1,    -1,    -1,    -1,    -1,    35,    36,
      37,    38,     3,    -1,     5,     6,     7,     8,    45,    -1,
      11,    48,    49,    14,    51,    52,    53,    18,    -1,    56,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    29,    -1,
      -1,    -1,    -1,    -1,    35,    36,    37,    38,     3,    -1,
       5,     6,     7,     8,    45,    -1,    11,    48,    49,    14,
      -1,    52,    53,    18,    -1,    56,    57,    -1,    -1,    -1,
      -1,    -1,    -1,    28,    29,    -1,    -1,    -1,    -1,    -1,
      35,    36,    37,    38,     3,    -1,     5,     6,     7,     8,
      45,    -1,    11,    48,    49,    14,    -1,    52,    53,    18,
      -1,    56,    57,    -1,    -1,    -1,    -1,    -1,    -1,    28,
      29,    -1,    -1,    -1,    -1,    -1,    35,    36,    37,    38,
      -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,    48,
      49,    24,    25,    52,    53,    28,    29,    56,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    41,    42,
      43,    44,    45,    46,    47,    -1,    40,    41,    42,    43,
      44,    45,    46,    47,    -1,    -1,    -1,    -1,    -1,    -1,
      54,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,
      41,    42,    43,    44,    45,    46,    47,    -1,    -1,    -1,
      -1,    -1,    -1,    54,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    40,    41,    42,    43,    44,    45,    46,    47,
      -1,    -1,    -1,    -1,    -1,    -1,    54,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    40,    41,    42,    43,    44,
      45,    46,    47,    -1,    -1,    -1,    -1,    -1,    -1,    54,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    41,
      42,    43,    44,    45,    46,    47,    -1,    -1,    -1,    -1,
      -1,    -1,    54,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    40,    41,    42,    43,    44,    45,    46,    47,    -1,
      -1,    -1,    -1,    -1,    -1,    54,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    40,    41,    42,    43,    44,    45,
      46,    47,    -1,    -1,    -1,    -1,    52,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    40,    41,    42,    43,    44,
      45,    46,    47,    -1,    -1,    -1,    -1,    52,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    40,    41,    42,    43,
      44,    45,    46,    47,    -1,    -1,    -1,    -1,    52,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    41,    42,
      43,    44,    45,    46,    47,    -1,    -1,    -1,    -1,    52,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    41,
      42,    43,    44,    45,    46,    47,    -1,    -1,    -1,    -1,
      52,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    22,    23,    24,    25,    26,    -1,    28,    29,    40,
      41,    42,    43,    44,    45,    46,    47,    -1,    -1,    -1,
      41,    42,    43,    44,    45,    46,    47,    22,    23,    24,
      25,    -1,    -1,    28,    29,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    41,    42,    43,    44,
      45,    46,    47,    28,    29,    -1,    -1,    -1,    -1,    -1,
      35,    36,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,
      45,    -1,    -1,    48,    49,    28,    29,    52,    53,    -1,
      -1,    -1,    35,    36,    37,    38,    -1,    -1,    -1,    -1,
      -1,    -1,    45,    -1,    -1,    48,    49,    28,    29,    52,
      53,    -1,    -1,    -1,    35,    36,    37,    38,    -1,    -1,
      -1,    -1,    -1,    -1,    45,    -1,    -1,    48,    49,    -1,
      -1,    -1,    53
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    60,     0,     3,     5,     6,     7,     8,    11,    14,
      18,    28,    29,    35,    36,    37,    38,    45,    48,    49,
      51,    52,    53,    56,    61,    62,    63,    64,    66,    68,
      70,    71,    72,    73,    74,    75,    53,    53,    53,    14,
      36,    63,    70,    36,    52,    75,    36,    36,    45,    65,
      64,    75,    75,    53,    58,    75,    75,    75,    36,    75,
      57,    69,    70,    36,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    40,    41,    42,    43,    44,    45,
      46,    47,    52,    75,    75,    52,    75,    53,     5,    52,
      52,    53,    65,    65,    36,    64,    67,    75,    76,    70,
      37,    41,    54,    57,    70,    40,    52,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    54,    54,    75,    52,    53,    67,    52,
      36,    54,    55,    54,    55,    36,    75,    70,    70,    52,
      75,    75,    54,    68,    64,    75,    42,    52,     4,    75,
      52,    54,    68,    36,    70,    54,    75,    52,    70,    54,
      70
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    59,    60,    60,    60,    61,    61,    61,    62,    62,
      63,    63,    63,    64,    64,    64,    65,    65,    66,    66,
      67,    67,    67,    68,    68,    69,    69,    70,    70,    70,
      70,    70,    70,    70,    70,    70,    70,    71,    71,    72,
      72,    73,    73,    74,    74,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    76,    76,    76
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     2,     1,     1,     1,     5,     3,
       3,     5,     4,     1,     2,     3,     1,     2,     6,     5,
       0,     2,     4,     3,     2,     1,     2,     1,     1,     1,
       1,     1,     1,     2,     1,     3,     3,     5,     7,     5,
       7,     9,     8,     2,     3,     1,     1,     1,     1,     3,
       4,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     3,     3,     3,     2,     2,
       2,     2,     2,     2,     0,     1,     3
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

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
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
  case 2: /* program: %empty  */
#line 140 "parser.y"
    { 
        astRoot = NULL; 
    }
#line 1465 "parser.tab.c"
    break;

  case 3: /* program: program declaration  */
#line 144 "parser.y"
    { 
        if (astRoot == NULL) {
            astRoot = (yyvsp[0].node);
        }
        printf("AST: Declaration added to program\n");
    }
#line 1476 "parser.tab.c"
    break;

  case 4: /* program: program statement  */
#line 151 "parser.y"
    { 
        if (astRoot == NULL) {
            astRoot = createNode("Program", NULL, (yyvsp[0].node), NULL);
        } else {
            /* Chain statements */
            struct ASTNode* temp = astRoot;
            while (temp->next) temp = temp->next;
            temp->next = (yyvsp[0].node);
        }
        printf("AST: Statement added to program\n");
    }
#line 1492 "parser.tab.c"
    break;

  case 5: /* declaration: var_decl  */
#line 166 "parser.y"
    { (yyval.node) = (yyvsp[0].node); }
#line 1498 "parser.tab.c"
    break;

  case 6: /* declaration: func_decl  */
#line 168 "parser.y"
    { (yyval.node) = (yyvsp[0].node); }
#line 1504 "parser.tab.c"
    break;

  case 7: /* declaration: preproc_decl  */
#line 170 "parser.y"
    { (yyval.node) = (yyvsp[0].node); }
#line 1510 "parser.tab.c"
    break;

  case 8: /* preproc_decl: '#' IDENTIFIER '<' IDENTIFIER '>'  */
#line 175 "parser.y"
    {
        (yyval.node) = createNode("Include", (yyvsp[-1].str), NULL, NULL);
        printf("AST: Include - %s\n", (yyvsp[-1].str));
    }
#line 1519 "parser.tab.c"
    break;

  case 9: /* preproc_decl: '#' IDENTIFIER STRING  */
#line 180 "parser.y"
    {
        (yyval.node) = createNode("Include", (yyvsp[0].str), NULL, NULL);
        printf("AST: Include - %s\n", (yyvsp[0].str));
    }
#line 1528 "parser.tab.c"
    break;

  case 10: /* var_decl: type_specifier IDENTIFIER ';'  */
#line 188 "parser.y"
    {
        (yyval.node) = createNode("VarDecl", (yyvsp[-1].str), (yyvsp[-2].node), NULL);
        printf("AST: Variable Declaration - %s\n", (yyvsp[-1].str));
    }
#line 1537 "parser.tab.c"
    break;

  case 11: /* var_decl: type_specifier IDENTIFIER '=' expr ';'  */
#line 193 "parser.y"
    {
        (yyval.node) = createNode("VarDeclInit", (yyvsp[-3].str), (yyvsp[-4].node), (yyvsp[-1].node));
        printf("AST: Variable Declaration with Init - %s\n", (yyvsp[-3].str));
    }
#line 1546 "parser.tab.c"
    break;

  case 12: /* var_decl: STATIC type_specifier IDENTIFIER ';'  */
#line 198 "parser.y"
    {
        (yyval.node) = createNode("StaticVarDecl", (yyvsp[-1].str), (yyvsp[-2].node), NULL);
        printf("AST: Static Variable Declaration - %s\n", (yyvsp[-1].str));
    }
#line 1555 "parser.tab.c"
    break;

  case 13: /* type_specifier: TYPE  */
#line 206 "parser.y"
    {
        (yyval.node) = createNode("Type", "primitive", NULL, NULL);
    }
#line 1563 "parser.tab.c"
    break;

  case 14: /* type_specifier: TYPE pointer  */
#line 210 "parser.y"
    {
        (yyval.node) = createNode("PointerType", "pointer", createNode("Type", "primitive", NULL, NULL), NULL);
    }
#line 1571 "parser.tab.c"
    break;

  case 15: /* type_specifier: TYPE pointer pointer  */
#line 214 "parser.y"
    {
        (yyval.node) = createNode("PointerPointerType", "double_pointer", createNode("Type", "primitive", NULL, NULL), NULL);
    }
#line 1579 "parser.tab.c"
    break;

  case 16: /* pointer: '*'  */
#line 221 "parser.y"
    { (yyval.node) = createNode("Pointer", "*", NULL, NULL); }
#line 1585 "parser.tab.c"
    break;

  case 17: /* pointer: '*' pointer  */
#line 223 "parser.y"
    { (yyval.node) = createNode("Pointer", "*", (yyvsp[0].node), NULL); }
#line 1591 "parser.tab.c"
    break;

  case 18: /* func_decl: TYPE IDENTIFIER '(' param_list ')' compound_statement  */
#line 228 "parser.y"
    {
        (yyval.node) = createNode("Function", (yyvsp[-4].str), (yyvsp[-2].node), (yyvsp[0].node));
        printf("AST: Function Declaration - %s\n", (yyvsp[-4].str));
    }
#line 1600 "parser.tab.c"
    break;

  case 19: /* func_decl: IDENTIFIER '(' param_list ')' compound_statement  */
#line 233 "parser.y"
    {
        (yyval.node) = createNode("Function", (yyvsp[-4].str), (yyvsp[-2].node), (yyvsp[0].node));
        printf("AST: Function Declaration (implicit int) - %s\n", (yyvsp[-4].str));
    }
#line 1609 "parser.tab.c"
    break;

  case 20: /* param_list: %empty  */
#line 241 "parser.y"
    { (yyval.node) = NULL; }
#line 1615 "parser.tab.c"
    break;

  case 21: /* param_list: type_specifier IDENTIFIER  */
#line 243 "parser.y"
    {
        (yyval.node) = createNode("Param", (yyvsp[0].str), (yyvsp[-1].node), NULL);
    }
#line 1623 "parser.tab.c"
    break;

  case 22: /* param_list: param_list ',' type_specifier IDENTIFIER  */
#line 247 "parser.y"
    {
        struct ASTNode* newParam = createNode("Param", (yyvsp[0].str), (yyvsp[-1].node), NULL);
        (yyval.node) = (yyvsp[-3].node);
        if ((yyval.node)) {
            struct ASTNode* temp = (yyval.node);
            while (temp->next) temp = temp->next;
            temp->next = newParam;
        } else {
            (yyval.node) = newParam;
        }
    }
#line 1639 "parser.tab.c"
    break;

  case 23: /* compound_statement: '{' statement_list '}'  */
#line 262 "parser.y"
    {
        (yyval.node) = createNode("CompoundStmt", NULL, (yyvsp[-1].node), NULL);
        printf("AST: Compound Statement\n");
    }
#line 1648 "parser.tab.c"
    break;

  case 24: /* compound_statement: '{' '}'  */
#line 267 "parser.y"
    {
        (yyval.node) = createNode("EmptyCompoundStmt", NULL, NULL, NULL);
        printf("AST: Empty Compound Statement\n");
    }
#line 1657 "parser.tab.c"
    break;

  case 25: /* statement_list: statement  */
#line 275 "parser.y"
    { (yyval.node) = (yyvsp[0].node); }
#line 1663 "parser.tab.c"
    break;

  case 26: /* statement_list: statement_list statement  */
#line 277 "parser.y"
    {
        (yyval.node) = (yyvsp[-1].node);
        if ((yyval.node)) {
            struct ASTNode* temp = (yyval.node);
            while (temp->next) temp = temp->next;
            temp->next = (yyvsp[0].node);
        } else {
            (yyval.node) = (yyvsp[0].node);
        }
    }
#line 1678 "parser.tab.c"
    break;

  case 27: /* statement: compound_statement  */
#line 291 "parser.y"
    { (yyval.node) = (yyvsp[0].node); }
#line 1684 "parser.tab.c"
    break;

  case 28: /* statement: if_statement  */
#line 293 "parser.y"
    { (yyval.node) = (yyvsp[0].node); }
#line 1690 "parser.tab.c"
    break;

  case 29: /* statement: while_statement  */
#line 295 "parser.y"
    { (yyval.node) = (yyvsp[0].node); }
#line 1696 "parser.tab.c"
    break;

  case 30: /* statement: for_statement  */
#line 297 "parser.y"
    { (yyval.node) = (yyvsp[0].node); }
#line 1702 "parser.tab.c"
    break;

  case 31: /* statement: return_statement  */
#line 299 "parser.y"
    { (yyval.node) = (yyvsp[0].node); }
#line 1708 "parser.tab.c"
    break;

  case 32: /* statement: var_decl  */
#line 301 "parser.y"
    { (yyval.node) = (yyvsp[0].node); }
#line 1714 "parser.tab.c"
    break;

  case 33: /* statement: expr ';'  */
#line 303 "parser.y"
    { 
        (yyval.node) = createNode("ExprStmt", NULL, (yyvsp[-1].node), NULL);
        printf("AST: Expression Statement\n");
    }
#line 1723 "parser.tab.c"
    break;

  case 34: /* statement: ';'  */
#line 308 "parser.y"
    { (yyval.node) = createNode("EmptyStmt", NULL, NULL, NULL); }
#line 1729 "parser.tab.c"
    break;

  case 35: /* statement: GOTO IDENTIFIER ';'  */
#line 310 "parser.y"
    {
        (yyval.node) = createNode("Goto", (yyvsp[-1].str), NULL, NULL);
        printf("AST: Goto - %s\n", (yyvsp[-1].str));
    }
#line 1738 "parser.tab.c"
    break;

  case 36: /* statement: IDENTIFIER ':' statement  */
#line 315 "parser.y"
    {
        (yyval.node) = createNode("Label", (yyvsp[-2].str), (yyvsp[0].node), NULL);
        printf("AST: Label - %s\n", (yyvsp[-2].str));
    }
#line 1747 "parser.tab.c"
    break;

  case 37: /* if_statement: IF '(' expr ')' statement  */
#line 323 "parser.y"
    {
        (yyval.node) = createNode("If", NULL, (yyvsp[-2].node), (yyvsp[0].node));
        printf("AST: IF Statement (no else)\n");
    }
#line 1756 "parser.tab.c"
    break;

  case 38: /* if_statement: IF '(' expr ')' statement ELSE statement  */
#line 328 "parser.y"
    {
        (yyval.node) = createNode("If-Else", NULL, (yyvsp[-4].node), createNode("Then-Else", NULL, (yyvsp[-2].node), (yyvsp[0].node)));
        printf("AST: IF-ELSE Statement\n");
    }
#line 1765 "parser.tab.c"
    break;

  case 39: /* while_statement: WHILE '(' expr ')' statement  */
#line 336 "parser.y"
    {
        (yyval.node) = createNode("While", NULL, (yyvsp[-2].node), (yyvsp[0].node));
        printf("AST: WHILE Statement\n");
    }
#line 1774 "parser.tab.c"
    break;

  case 40: /* while_statement: DO statement WHILE '(' expr ')' ';'  */
#line 341 "parser.y"
    {
        (yyval.node) = createNode("Do-While", NULL, (yyvsp[-2].node), (yyvsp[-5].node));
        printf("AST: DO-WHILE Statement\n");
    }
#line 1783 "parser.tab.c"
    break;

  case 41: /* for_statement: FOR '(' expr ';' expr ';' expr ')' statement  */
#line 349 "parser.y"
    {
        (yyval.node) = createNode("For", NULL, 
            createNode("ForInit", NULL, (yyvsp[-6].node), 
                createNode("ForCond-Inc", NULL, (yyvsp[-4].node), (yyvsp[-2].node))), (yyvsp[0].node));
        printf("AST: FOR Statement\n");
    }
#line 1794 "parser.tab.c"
    break;

  case 42: /* for_statement: FOR '(' ';' expr ';' expr ')' statement  */
#line 356 "parser.y"
    {
        (yyval.node) = createNode("For", NULL, 
            createNode("ForNoInit", NULL, NULL, 
                createNode("ForCond-Inc", NULL, (yyvsp[-4].node), (yyvsp[-2].node))), (yyvsp[0].node));
        printf("AST: FOR Statement (no init)\n");
    }
#line 1805 "parser.tab.c"
    break;

  case 43: /* return_statement: RETURN ';'  */
#line 366 "parser.y"
    {
        (yyval.node) = createNode("Return", NULL, NULL, NULL);
        printf("AST: RETURN Statement\n");
    }
#line 1814 "parser.tab.c"
    break;

  case 44: /* return_statement: RETURN expr ';'  */
#line 371 "parser.y"
    {
        (yyval.node) = createNode("Return", NULL, (yyvsp[-1].node), NULL);
        printf("AST: RETURN Statement with value\n");
    }
#line 1823 "parser.tab.c"
    break;

  case 45: /* expr: IDENTIFIER  */
#line 379 "parser.y"
    {
        (yyval.node) = createNode("Identifier", (yyvsp[0].str), NULL, NULL);
    }
#line 1831 "parser.tab.c"
    break;

  case 46: /* expr: NUMBER  */
#line 383 "parser.y"
    {
        char buf[32];
        snprintf(buf, sizeof(buf), "%d", (yyvsp[0].num));
        (yyval.node) = createNode("Number", buf, NULL, NULL);
    }
#line 1841 "parser.tab.c"
    break;

  case 47: /* expr: STRING  */
#line 389 "parser.y"
    {
        (yyval.node) = createNode("String", (yyvsp[0].str), NULL, NULL);
    }
#line 1849 "parser.tab.c"
    break;

  case 48: /* expr: CHAR  */
#line 393 "parser.y"
    {
        (yyval.node) = createNode("Char", "char", NULL, NULL);
    }
#line 1857 "parser.tab.c"
    break;

  case 49: /* expr: '(' expr ')'  */
#line 397 "parser.y"
    {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 1865 "parser.tab.c"
    break;

  case 50: /* expr: IDENTIFIER '(' arg_list ')'  */
#line 401 "parser.y"
    {
        (yyval.node) = createNode("FunctionCall", (yyvsp[-3].str), (yyvsp[-1].node), NULL);
        printf("AST: Function Call - %s\n", (yyvsp[-3].str));
    }
#line 1874 "parser.tab.c"
    break;

  case 51: /* expr: expr '+' expr  */
#line 406 "parser.y"
    {
        (yyval.node) = createNode("Add", "+", (yyvsp[-2].node), (yyvsp[0].node));
        printf("AST: Binary Op - Add\n");
    }
#line 1883 "parser.tab.c"
    break;

  case 52: /* expr: expr '-' expr  */
#line 411 "parser.y"
    {
        (yyval.node) = createNode("Sub", "-", (yyvsp[-2].node), (yyvsp[0].node));
        printf("AST: Binary Op - Sub\n");
    }
#line 1892 "parser.tab.c"
    break;

  case 53: /* expr: expr '*' expr  */
#line 416 "parser.y"
    {
        (yyval.node) = createNode("Mul", "*", (yyvsp[-2].node), (yyvsp[0].node));
        printf("AST: Binary Op - Mul\n");
    }
#line 1901 "parser.tab.c"
    break;

  case 54: /* expr: expr '/' expr  */
#line 421 "parser.y"
    {
        (yyval.node) = createNode("Div", "/", (yyvsp[-2].node), (yyvsp[0].node));
        printf("AST: Binary Op - Div\n");
    }
#line 1910 "parser.tab.c"
    break;

  case 55: /* expr: expr '%' expr  */
#line 426 "parser.y"
    {
        (yyval.node) = createNode("Mod", "%", (yyvsp[-2].node), (yyvsp[0].node));
        printf("AST: Binary Op - Mod\n");
    }
#line 1919 "parser.tab.c"
    break;

  case 56: /* expr: expr '<' expr  */
#line 431 "parser.y"
    {
        (yyval.node) = createNode("LT", "<", (yyvsp[-2].node), (yyvsp[0].node));
        printf("AST: Comparison - LT\n");
    }
#line 1928 "parser.tab.c"
    break;

  case 57: /* expr: expr '>' expr  */
#line 436 "parser.y"
    {
        (yyval.node) = createNode("GT", ">", (yyvsp[-2].node), (yyvsp[0].node));
        printf("AST: Comparison - GT\n");
    }
#line 1937 "parser.tab.c"
    break;

  case 58: /* expr: expr LE expr  */
#line 441 "parser.y"
    {
        (yyval.node) = createNode("LE", "<=", (yyvsp[-2].node), (yyvsp[0].node));
        printf("AST: Comparison - LE\n");
    }
#line 1946 "parser.tab.c"
    break;

  case 59: /* expr: expr GE expr  */
#line 446 "parser.y"
    {
        (yyval.node) = createNode("GE", ">=", (yyvsp[-2].node), (yyvsp[0].node));
        printf("AST: Comparison - GE\n");
    }
#line 1955 "parser.tab.c"
    break;

  case 60: /* expr: expr EQ expr  */
#line 451 "parser.y"
    {
        (yyval.node) = createNode("EQ", "==", (yyvsp[-2].node), (yyvsp[0].node));
        printf("AST: Comparison - EQ\n");
    }
#line 1964 "parser.tab.c"
    break;

  case 61: /* expr: expr NE expr  */
#line 456 "parser.y"
    {
        (yyval.node) = createNode("NE", "!=", (yyvsp[-2].node), (yyvsp[0].node));
        printf("AST: Comparison - NE\n");
    }
#line 1973 "parser.tab.c"
    break;

  case 62: /* expr: expr AND expr  */
#line 461 "parser.y"
    {
        (yyval.node) = createNode("LogicalAnd", "&&", (yyvsp[-2].node), (yyvsp[0].node));
        printf("AST: Logical AND\n");
    }
#line 1982 "parser.tab.c"
    break;

  case 63: /* expr: expr OR expr  */
#line 466 "parser.y"
    {
        (yyval.node) = createNode("LogicalOr", "||", (yyvsp[-2].node), (yyvsp[0].node));
        printf("AST: Logical OR\n");
    }
#line 1991 "parser.tab.c"
    break;

  case 64: /* expr: '!' expr  */
#line 471 "parser.y"
    {
        (yyval.node) = createNode("LogicalNot", "!", (yyvsp[0].node), NULL);
        printf("AST: Logical NOT\n");
    }
#line 2000 "parser.tab.c"
    break;

  case 65: /* expr: expr '=' expr  */
#line 476 "parser.y"
    {
        (yyval.node) = createNode("Assign", "=", (yyvsp[-2].node), (yyvsp[0].node));
        printf("AST: Assignment\n");
    }
#line 2009 "parser.tab.c"
    break;

  case 66: /* expr: expr PLUSEQ expr  */
#line 481 "parser.y"
    {
        (yyval.node) = createNode("AddAssign", "+=", (yyvsp[-2].node), (yyvsp[0].node));
        printf("AST: Add Assignment\n");
    }
#line 2018 "parser.tab.c"
    break;

  case 67: /* expr: expr MINUSEQ expr  */
#line 486 "parser.y"
    {
        (yyval.node) = createNode("SubAssign", "-=", (yyvsp[-2].node), (yyvsp[0].node));
        printf("AST: Sub Assignment\n");
    }
#line 2027 "parser.tab.c"
    break;

  case 68: /* expr: INC expr  */
#line 491 "parser.y"
    {
        (yyval.node) = createNode("PreInc", "++", (yyvsp[0].node), NULL);
        printf("AST: Pre-Increment\n");
    }
#line 2036 "parser.tab.c"
    break;

  case 69: /* expr: expr INC  */
#line 496 "parser.y"
    {
        (yyval.node) = createNode("PostInc", "++", (yyvsp[-1].node), NULL);
        printf("AST: Post-Increment\n");
    }
#line 2045 "parser.tab.c"
    break;

  case 70: /* expr: DEC expr  */
#line 501 "parser.y"
    {
        (yyval.node) = createNode("PreDec", "--", (yyvsp[0].node), NULL);
        printf("AST: Pre-Decrement\n");
    }
#line 2054 "parser.tab.c"
    break;

  case 71: /* expr: expr DEC  */
#line 506 "parser.y"
    {
        (yyval.node) = createNode("PostDec", "--", (yyvsp[-1].node), NULL);
        printf("AST: Post-Decrement\n");
    }
#line 2063 "parser.tab.c"
    break;

  case 72: /* expr: '&' expr  */
#line 511 "parser.y"
    {
        (yyval.node) = createNode("AddressOf", "&", (yyvsp[0].node), NULL);
        printf("AST: Address Of\n");
    }
#line 2072 "parser.tab.c"
    break;

  case 73: /* expr: '*' expr  */
#line 516 "parser.y"
    {
        (yyval.node) = createNode("Deref", "*", (yyvsp[0].node), NULL);
        printf("AST: Dereference\n");
    }
#line 2081 "parser.tab.c"
    break;

  case 74: /* arg_list: %empty  */
#line 524 "parser.y"
    { (yyval.node) = NULL; }
#line 2087 "parser.tab.c"
    break;

  case 75: /* arg_list: expr  */
#line 526 "parser.y"
    { (yyval.node) = (yyvsp[0].node); }
#line 2093 "parser.tab.c"
    break;

  case 76: /* arg_list: arg_list ',' expr  */
#line 528 "parser.y"
    {
        (yyval.node) = (yyvsp[-2].node);
        if ((yyval.node)) {
            struct ASTNode* temp = (yyval.node);
            while (temp->next) temp = temp->next;
            temp->next = (yyvsp[0].node);
        } else {
            (yyval.node) = (yyvsp[0].node);
        }
    }
#line 2108 "parser.tab.c"
    break;


#line 2112 "parser.tab.c"

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
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
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

  return yyresult;
}

#line 540 "parser.y"


void yyerror(const char *s) {
    fprintf(stderr, "Syntactic Error: %s\n", s);
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        FILE *fp = fopen(argv[1], "r");
        if (fp) {
            yyin = fp;
        } else {
            fprintf(stderr, "Error opening file: %s\n", argv[1]);
            return -1;
        }
    } else {
        printf("Usage: %s <source_file>\n", argv[0]);
        printf("Example: %s chmod.c\n", argv[0]);
        return 1;
    }
    
    printf("=== Starting Syntactic Analysis ===\n\n");
    
    yyparse();
    
    printf("\n=== AST Structure ===\n");
    if (astRoot) {
        printAST(astRoot, 0);
        generateDotFile(astRoot, "ast.dot");
    } else {
        printf("No AST generated (parse may have failed).\n");
    }
    
    return 0;
}
