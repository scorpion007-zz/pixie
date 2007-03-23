%option never-interactive
%option noyywrap
%%
\(													return IF_OPEN;
\)													return IF_CLOSE;
\+													return IF_PLUS;
\-													return IF_MINUS;
\*													return IF_MUL;
\/													return IF_DIV;
\*\*												return IF_MULMUL;
\&													return IF_AND;
\^													return IF_POW;
\|													return IF_OR;
\=\=												return IF_EQUAL;
\!\=												return IF_NEQUAL;
\<\=												return IF_LESSE;
\>\=												return IF_GREATERE;
\<													return IF_LESS;
\>													return IF_GREATER;
\&\&												return IF_ANDAND;
\|\|												return IF_OROR;
\~													return IF_NOT;
\$													return IF_DOLLAR;
\=\~												return IF_MATCH;
\,													return IF_COMMA;

defined												return IF_DEFINED;
concat												return IF_CONCAT;

\'[^\'\"]*\'										{   yylval.string = rstrdup(yytext+1,CRenderer::globalMemory);	yylval.string[strlen(yylval.string)-1] = '\0'; osProcessEscapes(yylval.string); return IF_TEXT_VALUE;}
[a-zA-Z\_][a-zA-Z0-9:\_]*							{	yylval.string = rstrdup(yytext,CRenderer::globalMemory);	return IF_IDENTIFIER_VALUE; }
[+-]?([0-9]+|([0-9]*(\.[0-9]+)?)([eE][+-]?[0-9]+)?)	{	sscanf(yytext,"%f",&yylval.real); return IF_FLOAT_VALUE; }
[+-]?([0-9]+|([0-9]+(\.[0-9]*)?)([eE][+-]?[0-9]+)?)	{	sscanf(yytext,"%f",&yylval.real); return IF_FLOAT_VALUE; }
[\t ]												;
\n													;
%%






