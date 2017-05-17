%{
#undef YY_MAIN
#include "qvttoken.h"

using namespace QVTToken ;

%}
%%

[0-9]+	{ return NUMBER ; }
.|\n	{ return UKN ; }

%%

int yywrap () { return 1 ; }
