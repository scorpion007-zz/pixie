%option never-interactive
%option noyywrap
%%
\#\!parameters										return SCRL_PARAMETERS;
\#\!variables										return SCRL_VARIABLES;
output												return SCRL_OUTPUT;
uniform												return SCRL_UNIFORM;
varying												return SCRL_VARYING;
float												return SCRL_FLOAT;
boolean												return SCRL_BOOLEAN;
color												return SCRL_COLOR;
vector												return SCRL_VECTOR;
normal												return SCRL_NORMAL;
point												return SCRL_POINT;
matrix												return SCRL_MATRIX;
string												return SCRL_STRING;

surface												return SCRL_SURFACE;
displacement										return SCRL_DISPLACEMENT;
imager												return SCRL_IMAGER;
light												return SCRL_LIGHTSOURCE;
volume												return SCRL_VOLUME;
generic												return SCRL_GENERIC;

DSO													return SCRL_DSO;

\#\!Init\:											return SCRL_INIT;
\#\!Code\:											return SCRL_CODE;

\.													return SCRL_DOT;
\:													return SCRL_COLON;
\=													return SCRL_EQUAL;
\(													return SCRL_OPEN_PARANTHESIS;
\)													return SCRL_CLOSE_PARANTHESIS;
\[													return SCRL_OPEN_SQR_PARANTHESIS;
\]													return SCRL_CLOSE_SQR_PARANTHESIS;
\,													return SCRL_COMMA;

\#\!version[ ]+[0-9]+\.[0-9]+\.[0-9]+\n				{	int	r,b,a;	sscanf(yytext+9,"%d.%d.%d",&r,&b,&a);	if ((r != VERSION_RELEASE) || (b != VERSION_BETA)) sdrerror("Version mismatch");	}
\"[^\"]*\"											{   strcpy(yylval.string,&yytext[1]);	yylval.string[strlen(yylval.string)-1] = '\0'; osProcessEscapes(yylval.string); return SCRL_TEXT_VALUE;}
[a-zA-Z\_][a-zA-Z0-9\_]*							{	strcpy(yylval.string,yytext); return SCRL_IDENTIFIER_VALUE; }
\#\![a-zA-Z][a-zA-Z0-9\_]*							{	strcpy(yylval.string,yytext); return SCRL_LABEL_VALUE; }

[+-]?([0-9]+|([0-9]*(\.[0-9]+)?)([eE][+-]?[0-9]+)?)	{	sscanf(yytext,"%f",&yylval.real); return SCRL_FLOAT_VALUE; }
[+-]?([0-9]+|([0-9]+(\.[0-9]*)?)([eE][+-]?[0-9]+)?) {	sscanf(yytext,"%f",&yylval.real); return SCRL_FLOAT_VALUE; }
[\t ]												;

\n													{	extern int slLineno; slLineno++; return SCRL_NL;	}
%%

