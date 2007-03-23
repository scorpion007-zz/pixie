%option never-interactive
%option noyywrap 
%%
void							return DSO_VOID;
float							return DSO_FLOAT;
vector							return DSO_VECTOR;
normal							return DSO_NORMAL;
point							return DSO_POINT;
color							return DSO_COLOR;
matrix							return DSO_MATRIX;
string							return DSO_STRING;
output							;
\(								return DSO_OPEN;
\)								return DSO_CLOSE;
[a-zA-Z0-9\_]+					{	yylval.string	=	strdup(yytext);	return DSO_TEXT;	}
\,								return DSO_COMMA;
[\n\t ]							;

%%

