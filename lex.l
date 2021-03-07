%{
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include "parser.hpp"

extern "C" {
    int yylex();
    int yywrap();
};
%}

digits  [0-9]+

%%

[ \t\n\r] {
	;
}
scene {
	yylval.ter = strdup(yytext);
	#ifdef DEBUG
	std::cout << "SCENE ";
	#endif
	return SCENE;
}
chara {
	yylval.ter = strdup(yytext);
	#ifdef DEBUG
	std::cout << "CHARA ";
	#endif
	return CHARA;
}
event {
	yylval.ter = strdup(yytext);
	#ifdef DEBUG
	std::cout << "EVENT ";
	#endif
	return EVENT;
}
once {
	yylval.ter = strdup(yytext);
	#ifdef DEBUG
	std::cout << "ONCE ";
	#endif
	return ONCE;
}
return {
	yylval.ter = strdup(yytext);
	#ifdef DEBUG
	std::cout << "RETURN ";
	#endif
	return RETURN;
}
begin {
	yylval.ter = strdup(yytext);
	#ifdef DEBUG
	std::cout << "START ";
	#endif
	return START;
}
invisible {
	yylval.ter = strdup(yytext);
	#ifdef DEBUG
	std::cout << "INVISIBLE ";
	#endif
	return INVISIBLE;
}
close {
	yylval.ter = strdup(yytext);
	#ifdef DEBUG
	std::cout << "CLOSE ";
	#endif
	return CLOSE;
}
display {
	yylval.ter = strdup(yytext);
	#ifdef DEBUG
	std::cout << "DISPLAY ";
	#endif
	return DISPLAY;
}
in {
	yylval.ter = strdup(yytext);
	#ifdef DEBUG
	std::cout << "IN ";
	#endif
	return IN;
}
schedule {
	yylval.ter = strdup(yytext);
	#ifdef DEBUG
	std::cout << "SCHEDULE ";
	#endif
	return SCHEDULE;
}
SIZE {
	yylval.ter = strdup(yytext);
	#ifdef DEBUG
	std::cout << "SIZE ";
	#endif
	return SIZE;
}
EXIT {
	yylval.ter = strdup(yytext);
	#ifdef DEBUG
	std::cout << "EXIT ";
	#endif
	return EXIT;
}
shape {
	yylval.ter = strdup(yytext);
	#ifdef DEBUG
	std::cout << "SHAPE ";
	#endif
	return SHAPE;
}
anchor {
	yylval.ter = strdup(yytext);
	#ifdef DEBUG
	std::cout << "ANCHOR ";
	#endif
	return ANCHOR;
}
zindex {
	yylval.ter = strdup(yytext);
	#ifdef DEBUG
	std::cout << "ZINDEX ";
	#endif
	return ZINDEX;
}
listen {
	yylval.ter = strdup(yytext);
	#ifdef DEBUG
	std::cout << "LISTEN ";
	#endif
	return LISTEN;
}
if {
	yylval.ter = strdup(yytext);
	#ifdef DEBUG
	std::cout << "IF ";
	#endif
	return IF;
}
else {
	yylval.ter = strdup(yytext);
	#ifdef DEBUG
	std::cout << "ELSE ";
	#endif
	return ELSE;
}
and {
	yylval.ter = strdup(yytext);
    #ifdef DEBUG
    std::cout << "AND ";
    #endif
    return AND;
}
or {
	yylval.ter = strdup(yytext);
    #ifdef DEBUG
    std::cout << "OR ";
    #endif
    return OR;
}
not {
	yylval.ter = strdup(yytext);
    #ifdef DEBUG
    std::cout << "NOT ";
    #endif
    return NOT;
}
int {
	yylval.ter = strdup(yytext);
    #ifdef DEBUG
    std::cout << "TYPEINT ";
    #endif
    return TYPEINT;
}
float {
	yylval.ter = strdup(yytext);
    #ifdef DEBUG
    std::cout << "TYPEFLOAT ";
    #endif
    return TYPEFLOAT;
}
string {
	yylval.ter = strdup(yytext);
    #ifdef DEBUG
    std::cout << "TYPESTR ";
    #endif
    return TYPESTR;
}
true {
	yylval.ter = strdup(yytext);
    #ifdef DEBUG
    std::cout << "TRUE ";
    #endif
    return TRUE;
}
false {
	yylval.ter = strdup(yytext);
    #ifdef DEBUG
    std::cout << "FALSE ";
    #endif
    return FALSE;
}
[_a-zA-Z][_a-zA_Z0-9]* {
	yylval.ter = strdup(yytext);
	#ifdef DEBUG
	std::cout << "VAR: " << yylval.ter << " ";
	#endif
	return VAR;
}
-?{digits}\.{digits} {
	yylval.ter = strdup(yytext);
	#ifdef DEBUG
	std::cout << "FLOAT: " << yylval.ter << " ";
	#endif
	return FLOAT;
}
-?{digits} {
	yylval.ter = strdup(yytext);
	#ifdef DEBUG
	std::cout << "INT: " << yylval.ter << " ";
	#endif
	return INT;
}
\"[^\"]*\" {
	yylval.ter = strdup(yytext);
	#ifdef DEBUG
	std::cout << "STRING: " << yylval.ter << " ";
	#endif
	return STRING;
}
\/\/.*$ {
    #ifdef DEBUG
    std::cout << "COMMENT: " << yytext;
    #endif
}
. {
	yylval.ter = strdup(yytext);
	#ifdef DEBUG
	std::cout << yylval.ter << " ";
	#endif
	return yytext[0];
}

%%

int yywrap() {
    return 1;
}
