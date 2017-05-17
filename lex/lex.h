#ifndef LEX_H
#define LEX_H

	#include "qvttoken.h"

	#undef yyFlexLexer
	#define yyFlexLexer VTFlexLexer
	#include <FlexLexer.h>

	#undef yyFlexLexer
	#define yyFlexLexer NFlexLexer
	#include <FlexLexer.h>

#endif
