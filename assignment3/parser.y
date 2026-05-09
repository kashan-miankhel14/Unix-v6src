%{
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

%}

/* Union for semantic values */
%union {
    int num;
    char *str;
    struct ASTNode *node;
}

/* Token declarations */
%token IF ELSE WHILE FOR DO RETURN BREAK CONTINUE GOTO SWITCH CASE
%token TYPE STRUCT UNION ENUM STATIC REGISTER EXTERN CONST
%token EQ NE LE GE AND OR INC DEC PLUSEQ MINUSEQ SHL SHR ARROW
%token <num> NUMBER
%token <str> IDENTIFIER STRING CHAR

/* Type declarations for non-terminals */
%type <node> program statement statement_list expr 
%type <node> var_decl func_decl param_list param arg_list
%type <node> if_statement while_statement for_statement return_statement
%type <node> compound_statement declaration type_specifier preproc_decl pointer

/* Precedence and associativity */
%nonassoc "then"
%nonassoc ELSE
%right '=' PLUSEQ MINUSEQ
%left OR
%left AND
%left EQ NE
%left LE GE '<' '>'
%left '+' '-'
%left '*' '/' '%'
%right '&' '!' '~'
%left INC DEC

%%

program:
    /* empty */ 
    { 
        astRoot = NULL; 
    }
|   program declaration
    { 
        if (astRoot == NULL) {
            astRoot = $2;
        }
        printf("AST: Declaration added to program\n");
    }
|   program statement
    { 
        if (astRoot == NULL) {
            astRoot = createNode("Program", NULL, $2, NULL);
        } else {
            /* Chain statements */
            struct ASTNode* temp = astRoot;
            while (temp->next) temp = temp->next;
            temp->next = $2;
        }
        printf("AST: Statement added to program\n");
    }
;

declaration:
    var_decl
    { $$ = $1; }
|   func_decl
    { $$ = $1; }
|   preproc_decl
    { $$ = $1; }
;

preproc_decl:
    '#' IDENTIFIER '<' IDENTIFIER '>'
    {
        $$ = createNode("Include", $4, NULL, NULL);
        printf("AST: Include - %s\n", $4);
    }
|   '#' IDENTIFIER STRING
    {
        $$ = createNode("Include", $3, NULL, NULL);
        printf("AST: Include - %s\n", $3);
    }
;

var_decl:
    type_specifier IDENTIFIER ';'
    {
        $$ = createNode("VarDecl", $2, $1, NULL);
        printf("AST: Variable Declaration - %s\n", $2);
    }
|   type_specifier IDENTIFIER '=' expr ';'
    {
        $$ = createNode("VarDeclInit", $2, $1, $4);
        printf("AST: Variable Declaration with Init - %s\n", $2);
    }
|   STATIC type_specifier IDENTIFIER ';'
    {
        $$ = createNode("StaticVarDecl", $3, $2, NULL);
        printf("AST: Static Variable Declaration - %s\n", $3);
    }
;

type_specifier:
    TYPE
    {
        $$ = createNode("Type", "primitive", NULL, NULL);
    }
|   TYPE pointer
    {
        $$ = createNode("PointerType", "pointer", createNode("Type", "primitive", NULL, NULL), NULL);
    }
|   TYPE pointer pointer
    {
        $$ = createNode("PointerPointerType", "double_pointer", createNode("Type", "primitive", NULL, NULL), NULL);
    }
;

pointer:
    '*'
    { $$ = createNode("Pointer", "*", NULL, NULL); }
|   '*' pointer
    { $$ = createNode("Pointer", "*", $2, NULL); }
;

func_decl:
    TYPE IDENTIFIER '(' param_list ')' compound_statement
    {
        $$ = createNode("Function", $2, $4, $6);
        printf("AST: Function Declaration - %s\n", $2);
    }
|   IDENTIFIER '(' param_list ')' compound_statement
    {
        $$ = createNode("Function", $1, $3, $5);
        printf("AST: Function Declaration (implicit int) - %s\n", $1);
    }
;

param_list:
    /* empty */
    { $$ = NULL; }
|   type_specifier IDENTIFIER
    {
        $$ = createNode("Param", $2, $1, NULL);
    }
|   param_list ',' type_specifier IDENTIFIER
    {
        struct ASTNode* newParam = createNode("Param", $4, $3, NULL);
        $$ = $1;
        if ($$) {
            struct ASTNode* temp = $$;
            while (temp->next) temp = temp->next;
            temp->next = newParam;
        } else {
            $$ = newParam;
        }
    }
;

compound_statement:
    '{' statement_list '}'
    {
        $$ = createNode("CompoundStmt", NULL, $2, NULL);
        printf("AST: Compound Statement\n");
    }
|   '{' '}'
    {
        $$ = createNode("EmptyCompoundStmt", NULL, NULL, NULL);
        printf("AST: Empty Compound Statement\n");
    }
;

statement_list:
    statement
    { $$ = $1; }
|   statement_list statement
    {
        $$ = $1;
        if ($$) {
            struct ASTNode* temp = $$;
            while (temp->next) temp = temp->next;
            temp->next = $2;
        } else {
            $$ = $2;
        }
    }
;

statement:
    compound_statement
    { $$ = $1; }
|   if_statement
    { $$ = $1; }
|   while_statement
    { $$ = $1; }
|   for_statement
    { $$ = $1; }
|   return_statement
    { $$ = $1; }
|   var_decl
    { $$ = $1; }
|   expr ';'
    { 
        $$ = createNode("ExprStmt", NULL, $1, NULL);
        printf("AST: Expression Statement\n");
    }
|   ';'
    { $$ = createNode("EmptyStmt", NULL, NULL, NULL); }
|   GOTO IDENTIFIER ';'
    {
        $$ = createNode("Goto", $2, NULL, NULL);
        printf("AST: Goto - %s\n", $2);
    }
|   IDENTIFIER ':' statement
    {
        $$ = createNode("Label", $1, $3, NULL);
        printf("AST: Label - %s\n", $1);
    }
;

if_statement:
    IF '(' expr ')' statement %prec "then"
    {
        $$ = createNode("If", NULL, $3, $5);
        printf("AST: IF Statement (no else)\n");
    }
|   IF '(' expr ')' statement ELSE statement
    {
        $$ = createNode("If-Else", NULL, $3, createNode("Then-Else", NULL, $5, $7));
        printf("AST: IF-ELSE Statement\n");
    }
;

while_statement:
    WHILE '(' expr ')' statement
    {
        $$ = createNode("While", NULL, $3, $5);
        printf("AST: WHILE Statement\n");
    }
|   DO statement WHILE '(' expr ')' ';'
    {
        $$ = createNode("Do-While", NULL, $5, $2);
        printf("AST: DO-WHILE Statement\n");
    }
;

for_statement:
    FOR '(' expr ';' expr ';' expr ')' statement
    {
        $$ = createNode("For", NULL, 
            createNode("ForInit", NULL, $3, 
                createNode("ForCond-Inc", NULL, $5, $7)), $9);
        printf("AST: FOR Statement\n");
    }
|   FOR '(' ';' expr ';' expr ')' statement
    {
        $$ = createNode("For", NULL, 
            createNode("ForNoInit", NULL, NULL, 
                createNode("ForCond-Inc", NULL, $4, $6)), $8);
        printf("AST: FOR Statement (no init)\n");
    }
;

return_statement:
    RETURN ';'
    {
        $$ = createNode("Return", NULL, NULL, NULL);
        printf("AST: RETURN Statement\n");
    }
|   RETURN expr ';'
    {
        $$ = createNode("Return", NULL, $2, NULL);
        printf("AST: RETURN Statement with value\n");
    }
;

expr:
    IDENTIFIER
    {
        $$ = createNode("Identifier", $1, NULL, NULL);
    }
|   NUMBER
    {
        char buf[32];
        snprintf(buf, sizeof(buf), "%d", $1);
        $$ = createNode("Number", buf, NULL, NULL);
    }
|   STRING
    {
        $$ = createNode("String", $1, NULL, NULL);
    }
|   CHAR
    {
        $$ = createNode("Char", "char", NULL, NULL);
    }
|   '(' expr ')'
    {
        $$ = $2;
    }
|   IDENTIFIER '(' arg_list ')'
    {
        $$ = createNode("FunctionCall", $1, $3, NULL);
        printf("AST: Function Call - %s\n", $1);
    }
|   expr '+' expr
    {
        $$ = createNode("Add", "+", $1, $3);
        printf("AST: Binary Op - Add\n");
    }
|   expr '-' expr
    {
        $$ = createNode("Sub", "-", $1, $3);
        printf("AST: Binary Op - Sub\n");
    }
|   expr '*' expr
    {
        $$ = createNode("Mul", "*", $1, $3);
        printf("AST: Binary Op - Mul\n");
    }
|   expr '/' expr
    {
        $$ = createNode("Div", "/", $1, $3);
        printf("AST: Binary Op - Div\n");
    }
|   expr '%' expr
    {
        $$ = createNode("Mod", "%", $1, $3);
        printf("AST: Binary Op - Mod\n");
    }
|   expr '<' expr
    {
        $$ = createNode("LT", "<", $1, $3);
        printf("AST: Comparison - LT\n");
    }
|   expr '>' expr
    {
        $$ = createNode("GT", ">", $1, $3);
        printf("AST: Comparison - GT\n");
    }
|   expr LE expr
    {
        $$ = createNode("LE", "<=", $1, $3);
        printf("AST: Comparison - LE\n");
    }
|   expr GE expr
    {
        $$ = createNode("GE", ">=", $1, $3);
        printf("AST: Comparison - GE\n");
    }
|   expr EQ expr
    {
        $$ = createNode("EQ", "==", $1, $3);
        printf("AST: Comparison - EQ\n");
    }
|   expr NE expr
    {
        $$ = createNode("NE", "!=", $1, $3);
        printf("AST: Comparison - NE\n");
    }
|   expr AND expr
    {
        $$ = createNode("LogicalAnd", "&&", $1, $3);
        printf("AST: Logical AND\n");
    }
|   expr OR expr
    {
        $$ = createNode("LogicalOr", "||", $1, $3);
        printf("AST: Logical OR\n");
    }
|   '!' expr
    {
        $$ = createNode("LogicalNot", "!", $2, NULL);
        printf("AST: Logical NOT\n");
    }
|   expr '=' expr
    {
        $$ = createNode("Assign", "=", $1, $3);
        printf("AST: Assignment\n");
    }
|   expr PLUSEQ expr
    {
        $$ = createNode("AddAssign", "+=", $1, $3);
        printf("AST: Add Assignment\n");
    }
|   expr MINUSEQ expr
    {
        $$ = createNode("SubAssign", "-=", $1, $3);
        printf("AST: Sub Assignment\n");
    }
|   INC expr
    {
        $$ = createNode("PreInc", "++", $2, NULL);
        printf("AST: Pre-Increment\n");
    }
|   expr INC
    {
        $$ = createNode("PostInc", "++", $1, NULL);
        printf("AST: Post-Increment\n");
    }
|   DEC expr
    {
        $$ = createNode("PreDec", "--", $2, NULL);
        printf("AST: Pre-Decrement\n");
    }
|   expr DEC
    {
        $$ = createNode("PostDec", "--", $1, NULL);
        printf("AST: Post-Decrement\n");
    }
|   '&' expr
    {
        $$ = createNode("AddressOf", "&", $2, NULL);
        printf("AST: Address Of\n");
    }
|   '*' expr
    {
        $$ = createNode("Deref", "*", $2, NULL);
        printf("AST: Dereference\n");
    }
;

arg_list:
    /* empty */
    { $$ = NULL; }
|   expr
    { $$ = $1; }
|   arg_list ',' expr
    {
        $$ = $1;
        if ($$) {
            struct ASTNode* temp = $$;
            while (temp->next) temp = temp->next;
            temp->next = $3;
        } else {
            $$ = $3;
        }
    }
;

%%

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
