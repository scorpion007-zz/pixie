%{
   #include <stdlib.h>

   int boolwrap() { return 1; }

   /* ----------------------------------------------------- */
   /* The following code is used to parse in-memory data    */
   /*   -> init_lexical_parser: must be called before the   */
   /*      grammatical analyzer.                            */
   /*   -> close_lexical_parser: must be called after the   */
   /*      end of the grammatical analyzer.                 */
   /* ----------------------------------------------------- */

   static YY_BUFFER_STATE buf_state;
   void init_lexical_parser(char *src) { buf_state = yy_scan_string(src); }
   void close_lexical_parser() { yy_delete_buffer(buf_state); }

   /* ----------------------------------------------------- */
   /* Allocatd memory for words                             */
   /* ----------------------------------------------------- */

   char *found_mot;
%}
%option never-interactive
%option noyywrap
%%
global												return	VAR_GLOBAL;
constant											return	VAR_CONSTANT;
uniform												return	VAR_UNIFORM;
varying												return	VAR_VARYING;
facevarying											return	VAR_FACEVARYING;
vertex												return	VAR_VERTEX;
float												return	VAR_FLOAT;
integer												return	VAR_INTEGER;
int													return	VAR_INTEGER;
vector												return	VAR_VECTOR;
color												return	VAR_COLOR;
normal												return	VAR_NORMAL;
point												return	VAR_POINT;
matrix												return	VAR_MATRIX;
htpoint												return	VAR_HTPOINT;
hpoint												return	VAR_HTPOINT;
double												return	VAR_DOUBLE;
string												return	VAR_STRING;
\[													return	VAR_OPEN;
\]													return	VAR_CLOSE;
[a-zA-Z\_][a-zA-Z0-9\_]*							{	assert(strlen(yytext) < (VARIABLE_NAME_LENGTH-1));	strcpy(currentVariable->name,yytext); return VAR_IDENTIFIER; }
([0-9]+|([0-9]*(\.[0-9]+)?)([eE][+-]?[0-9]+)?)		{	sscanf(yytext,"%f",&yylval.real); return VAR_FLOAT; }
[\t ]												;
%%

