%{
#include "parser.tab.h"
#include <stdio.h>
#include <string.h>
%}

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
"if"      { return IF; }
"else"    { return ELSE; }
"while"   { return WHILE; }
"for"     { return FOR; }
"do"      { return DO; }
"return"  { return RETURN; }
"break"   { return BREAK; }
"continue" { return CONTINUE; }
"goto"    { return GOTO; }
"switch"  { return SWITCH; }
"case"    { return CASE; }

 /* Data Type Keywords */
"int"|"char"|"float"|"double"|"long"|"short"|"unsigned"|"void" {
    return TYPE;
}
"struct"  { return STRUCT; }
"union"   { return UNION; }
"enum"    { return ENUM; }
"static"  { return STATIC; }
"register" { return REGISTER; }
"extern"  { return EXTERN; }
"const"   { return CONST; }

 /* Identifiers */
{IDENTIFIER} {
    yylval.str = strdup(yytext);
    return IDENTIFIER;
}

 /* Numbers */
{NUMBER} {
    yylval.num = atoi(yytext);
    return NUMBER;
}

 /* String literals */
{STRING} {
    yylval.str = strdup(yytext);
    return STRING;
}

 /* Character literals - simplified */
"'"([^'\n]|"\\'")*"'" {
    yylval.str = strdup(yytext);
    return CHAR;
}

 /* Operators */
"=="      { return EQ; }
"!="      { return NE; }
"<="      { return LE; }
">="      { return GE; }
"&&"      { return AND; }
"||"      { return OR; }
"++"      { return INC; }
"--"      { return DEC; }
"+="      { return PLUSEQ; }
"-="      { return MINUSEQ; }
"<<"      { return SHL; }
">>"      { return SHR; }
"->"      { return ARROW; }

 /* Pointer handling - multiple stars */
"*"+[ ]*  { 
    /* Count consecutive stars for pointer levels */
    return '*';
}

 /* Single character operators and punctuators */
"+"       { return '+'; }
"-"       { return '-'; }
"/"       { return '/'; }
"%"       { return '%'; }
"<"       { return '<'; }
">"       { return '>'; }
"="       { return '='; }
"&"       { return '&'; }
"|"       { return '|'; }
"^"       { return '^'; }
"!"       { return '!'; }
"~"       { return '~'; }

 /* Punctuators */
"("       { return '('; }
")"       { return ')'; }
"{"       { return '{'; }
"}"       { return '}'; }
"["       { return '['; }
"]"       { return ']'; }
";"       { return ';'; }
","       { return ','; }
":"       { return ':'; }
"."       { return '.'; }

 /* Preprocessor - simplified handling */
"#".*     { /* Ignore preprocessor directives */ }

 /* Comments */
"/*"([^*]|\*+[^*/])*\*+"/" { /* Ignore block comments */ }
"//".*    { /* Ignore line comments */ }

 /* Whitespace */
{WHITESPACE} { }

 /* Any other character */
.         { return yytext[0]; }

%%
