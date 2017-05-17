%{
#undef YY_MAIN
#include "qvttoken.h"

using namespace QVTToken ;

%}

ESC	\x1b
D	\x5b
P	\x23

%%

\0	{ return NUL ; }
\3	{ return ETX ; }
\4	{ return EOT ; }
\5	{ return ENQ ; }
\7	{ return BEL ; }
\10	{ return BS ; }
\11	{ return HT ; }
\12	{ return LF ; }
\13	{ return VT ; }
\14	{ return FF ; }
\15	{ return CR ; }
\16	{ return SO ; }
\17	{ return SI ; }
\21	{ return DC_ONE ; }
\23	{ return DC_THREE ; }
\30	{ return CAN ; }
\32	{ return SUB ; }

{ESC}{D}[0-9\?;]*h	{ return SET ; /*Not Strict*/ }
{ESC}{D}[0-9\?;]*l	{ return RESET ; /*Not Strict*/ }
{ESC}c	{ return RIS ; }

{ESC}=	{ return DECKPAM ; }
{ESC}>	{ return DECKPNM ; }

{ESC}[\(\)][AB012]	{ return SCS ; }
{ESC}[NO]	{ return SCS ; }

{ESC}{D}[0-9;]*m	{ return SGR ; /*Not Strict*/ }

{ESC}{D}[0-9]+;[0-9]+r	{ return DECSTBM ; }

{ESC}{D}[0-9]+A	{ return CUU ; }
{ESC}{D}[0-9]+B	{ return CUD ; }
{ESC}{D}[0-9]+C	{ return CUF ; }
{ESC}{D}[0-9]+D	{ return CUB ; }
{ESC}{D}[0-9;]*H	{ return CUP ; /*Not Strict*/ }
{ESC}{D}[0-9;]*f	{ return HVP ; /*Not Strict*/ }
{ESC}D	{ return IND ; }
{ESC}M	{ return RI ; }
{ESC}E	{ return NEL ; }
{ESC}7	{ return DECSC ; }
{ESC}8	{ return DECRC ; }

{ESC}H	{ return HTS ; }
{ESC}{D}[03]?g	{ return TBC ; }

{ESC}{P}3	{ return DECDHL_ONE ; }
{ESC}{P}4	{ return DECDHL_TWO ; }
{ESC}{P}5	{ return DECSWL ; }
{ESC}{P}6	{ return DECDWL ; }

{ESC}{D}[012]?K	{ return EL ; }
{ESC}{D}[012]?J	{ return ED ; }

{ESC}{D}[0-9]*P	{ return DCH ; }
{ESC}{D}[0-9]*L	{ return IL ; }
{ESC}{D}[0-9]*M	{ return DL ; }

{ESC}{D}[0-9\?;]*i	{ return MC ; /*Not Strict. IGNORED*/ }

{ESC}{D}[0-9\?;]*n	{ return DSR ; /*Not Strict*/ }
{ESC}{D}[0-9]+;[0-9]+R	{ return CPR ; }
{ESC}{D}0?c	{ return DA ; }
{ESC}Z	{ return DECID ; }

{ESC}{P}8	{ return DECALN ; }
{ESC}{D}2;[0-9]+y	{ return DECTST ; }

{ESC}{D}[01]?q	{ return DECLL ; }

[\x81-\xFE][\x40-\xFE]	{ return BIG_FIVE ; }

(http|https):\/\/[A-Za-z0-9\.\/\?\\\-\+=#%&]*	{ return URL ; }

{ESC}({D}|{P})?[0-9;\?]*[A-Za-z]	{ return UKN ; }
{ESC}\x5D.*\x7	{ return UKN ; }

.	{ return DEFAULT ; /*[\x20-\x7E]*/ }

%%

int yywrap () { return 1 ; }
