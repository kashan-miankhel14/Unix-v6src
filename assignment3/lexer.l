%{
#include <stdio.h>
#include <string.h>

/* Counter variables for each category */
int controlkeyword = 0;
int datatypekeyword = 0;
int digitcount = 0;
int operatorcount = 0;
int globalvar = 0;
int localvar = 0;
int punctuatorcount = 0;
int functionname = 0;
int othersymbol = 0;
int totalcount = 0;

/* Symbol table structures */
#define MAX_SYMBOLS 1000

struct SymbolEntry {
    char name[64];
    char category[32];
};

struct SymbolEntry symbolTable[MAX_SYMBOLS];
int symbolCount = 0;

/* Function to add symbol to table */
void addSymbol(const char* name, const char* category) {
    /* Check if already exists */
    for (int i = 0; i < symbolCount; i++) {
        if (strcmp(symbolTable[i].name, name) == 0 && 
            strcmp(symbolTable[i].category, category) == 0) {
            return;  /* Already exists */
        }
    }
    if (symbolCount < MAX_SYMBOLS) {
        strcpy(symbolTable[symbolCount].name, name);
        strcpy(symbolTable[symbolCount].category, category);
        symbolCount++;
    }
}

/* Function to print symbol table */
void printSymbolTable() {
    printf("\n========== SYMBOL TABLE ==========\n");
    printf("%-20s | %-15s\n", "Name", "Category");
    printf("-----------------------------------\n");
    for (int i = 0; i < symbolCount; i++) {
        printf("%-20s | %-15s\n", symbolTable[i].name, symbolTable[i].category);
    }
    printf("===================================\n");
}

/* Function to print frequency table */
void printFrequencyTable() {
    totalcount = controlkeyword + datatypekeyword + digitcount + operatorcount + 
                 globalvar + localvar + punctuatorcount + functionname + othersymbol;
    
    if (totalcount == 0) totalcount = 1;  /* Avoid division by zero */
    
    printf("\n========== FREQUENCY TABLE ==========\n");
    printf("%-20s | %-10s | %-10s | %-10s\n", "Category", "Keywords", "Count", "Frequency");
    printf("------------------------------------------------------------\n");
    
    printf("%-20s | %-10s | %-10d | %-10.4f\n", "control keywords", 
           "if,else,for...", controlkeyword, (float)controlkeyword/totalcount);
    printf("%-20s | %-10s | %-10d | %-10.4f\n", "datatype keywords", 
           "int,char...", datatypekeyword, (float)datatypekeyword/totalcount);
    printf("%-20s | %-10s | %-10d | %-10.4f\n", "digits", 
           "0-9...", digitcount, (float)digitcount/totalcount);
    printf("%-20s | %-10s | %-10d | %-10.4f\n", "operators", 
           "+,-,*,/...", operatorcount, (float)operatorcount/totalcount);
    printf("%-20s | %-10s | %-10d | %-10.4f\n", "global variables", 
           "vars...", globalvar, (float)globalvar/totalcount);
    printf("%-20s | %-10s | %-10d | %-10.4f\n", "local variables", 
           "vars...", localvar, (float)localvar/totalcount);
    printf("%-20s | %-10s | %-10d | %-10.4f\n", "punctuators", 
           ";,(){}...", punctuatorcount, (float)punctuatorcount/totalcount);
    printf("%-20s | %-10s | %-10d | %-10.4f\n", "function names", 
           "main,foo...", functionname, (float)functionname/totalcount);
    printf("%-20s | %-10s | %-10d | %-10.4f\n", "other symbols", 
           "...", othersymbol, (float)othersymbol/totalcount);
    printf("------------------------------------------------------------\n");
    printf("%-20s | %-10s | %-10d | %-10.4f\n", "TOTAL", "", totalcount, 1.0);
    printf("=====================================\n");
}

%}

/* Options */
%option noyywrap

/* Definitions */
DIGIT       [0-9]
NUMBER      {DIGIT}+|{DIGIT}+\.{DIGIT}+
LETTER      [a-zA-Z_]
IDENTIFIER  {LETTER}({LETTER}|{DIGIT})*
WHITESPACE  [ \t\n\r]+
STRING      \"[^\"]*\"

%%

 /* Control Keywords */
"if"|"else"|"while"|"for"|"do"|"switch"|"case"|"break"|"continue"|"goto"|"return" {
    printf("CONTROL KEYWORD: %s\n", yytext);
    controlkeyword++;
    totalcount++;
    addSymbol(yytext, "control");
}

 /* Data Type Keywords */
"int"|"char"|"float"|"double"|"long"|"short"|"unsigned"|"void"|"struct"|"union"|"enum"|"register"|"static"|"auto"|"extern"|"const" {
    printf("DATATYPE KEYWORD: %s\n", yytext);
    datatypekeyword++;
    totalcount++;
    addSymbol(yytext, "datatype");
}

 /* Numbers/Digits */
{NUMBER} {
    printf("NUMBER: %s\n", yytext);
    digitcount++;
    totalcount++;
    addSymbol(yytext, "number");
}

 /* Operators */
"+"|"-"|"*"|"/"|"%"|"="|"=="|"!="|"<"|">"|"<="|">="|"&&"|"||"|"!"|"&"|"|"|"^"|"~"|"<<"|">>"|"++"|"--"|"+="|"-="|"*="|"/="|"%=" {
    printf("OPERATOR: %s\n", yytext);
    operatorcount++;
    totalcount++;
    addSymbol(yytext, "operator");
}

 /* Function Names - heuristic: identifier followed by ( */
{IDENTIFIER}[ ]*"(" {
    char funcname[64];
    sscanf(yytext, "%[^( ]", funcname);
    printf("FUNCTION NAME: %s\n", funcname);
    functionname++;
    totalcount++;
    addSymbol(funcname, "function");
}

 /* Identifiers (variables) - heuristic based on context */
{IDENTIFIER} {
    printf("IDENTIFIER: %s\n", yytext);
    /* Heuristic: typically local variables are shorter, globals might be specific patterns */
    /* For this analysis, we'll categorize based on common patterns */
    if (yytext[0] == '_' || (yytext[0] >= 'a' && yytext[0] <= 'z' && strlen(yytext) <= 3)) {
        localvar++;
        addSymbol(yytext, "local");
    } else {
        globalvar++;
        addSymbol(yytext, "global");
    }
    totalcount++;
}

 /* Punctuators */
";"|","|"("|")"|"{"|"}"|"["|"]"|"#"|"\""|"'"|"."|":" {
    printf("PUNCTUATOR: %s\n", yytext);
    punctuatorcount++;
    totalcount++;
    addSymbol(yytext, "punctuator");
}

 /* Preprocessor directives */
"#".* {
    printf("PREPROCESSOR: %s\n", yytext);
    /* Count individual tokens in preprocessor */
    punctuatorcount++;  /* For # */
    totalcount++;
}

 /* Comments - ignore but count lines */
"/*"([^*]|\*+[^*/])*\*+"/" {
    printf("COMMENT: %s\n", yytext);
    /* Comments are not counted in categories */
}

 /* Single line comments */
"//".* {
    printf("COMMENT: %s\n", yytext);
}

 /* String literals */
{STRING} {
    printf("STRING: %s\n", yytext);
    othersymbol++;
    totalcount++;
    addSymbol(yytext, "string");
}

 /* Whitespace - ignore */
{WHITESPACE} { }

 /* Single character tokens */
. {
    printf("OTHER: %s\n", yytext);
    othersymbol++;
    totalcount++;
}

%%

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        printf("Example: %s chmod.c\n", argv[0]);
        return 0;
    }

    FILE *fd = fopen(argv[1], "r");
    if (!fd) {
        printf("Error Opening File: %s\n", argv[1]);
        return 0;
    }

    printf("=== Lexical Analysis of %s ===\n\n", argv[1]);
    
    yyin = fd;
    yylex();
    
    fclose(fd);
    
    /* Print results */
    printSymbolTable();
    printFrequencyTable();
    
    return 0;
}
