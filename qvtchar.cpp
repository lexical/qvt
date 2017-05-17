#include "qvtchar.h"

QTextCodec * QVTChar::big5codec = QTextCodec :: codecForName ( "Big5" ) ;
//void QVTChar :: fromBig5 ( const char * c ) ;
std::bitset <11> QVTChar::QVT_BLACK_B   = 0 ;
std::bitset <11> QVTChar::QVT_RED_B     = 1 ;
std::bitset <11> QVTChar::QVT_GREEN_B   = 2 ;
std::bitset <11> QVTChar::QVT_BROWN_B   = 3 ;
std::bitset <11> QVTChar::QVT_BLUE_B    = 4 ;
std::bitset <11> QVTChar::QVT_MAGENTA_B = 5 ;
std::bitset <11> QVTChar::QVT_CYAN_B    = 6 ; // 110
std::bitset <11> QVTChar::QVT_WHITE_B   = 7 ; // 111

std::bitset <11> QVTChar::QVT_BLACK_F   = 0 ;  // 000 000
std::bitset <11> QVTChar::QVT_RED_F     = 8 ;  // 001 000
std::bitset <11> QVTChar::QVT_GREEN_F   = 16 ; // 010 000
std::bitset <11> QVTChar::QVT_BROWN_F   = 24 ; // 011 000
std::bitset <11> QVTChar::QVT_BLUE_F    = 32 ; // 100 000
std::bitset <11> QVTChar::QVT_MAGENTA_F = 40 ; // 101 000
std::bitset <11> QVTChar::QVT_CYAN_F    = 48 ; // 110 000
std::bitset <11> QVTChar::QVT_WHITE_F   = 56 ; // 111 000

std::bitset <11> QVTChar::QVT_SGR_RESET     = 0  ; // 000 : 000 000
std::bitset <11> QVTChar::QVT_SGR_BOLD      = 64 ; // 001
std::bitset <11> QVTChar::QVT_SGR_DIM       = 128; // 010
std::bitset <11> QVTChar::QVT_SGR_UNDERLINE = 192; // 011
std::bitset <11> QVTChar::QVT_SGR_BLINK     = 256; // 100
std::bitset <11> QVTChar::QVT_SGR_REVERSE   = 320; // 101
std::bitset <11> QVTChar::QVT_SGR_HIDDEN    = 384; // 110
std::bitset <11> QVTChar::QVT_SGR_REVERVED  = 448; // 111

std::bitset <11> QVTChar::QVT_URL_RESET = 0  ; // 0 : 000 000 000
std::bitset <11> QVTChar::QVT_URL_SET   = 512; // 1

std::bitset <11> QVTChar::QVT_FWDISABLE = 0    ; // 0 : 0 000 000 000
std::bitset <11> QVTChar::QVT_FULLWIDTH = 1024 ; // 1

QVTChar :: QVTChar ()
{
	//big5codec = QTextCodec :: codecForName ( "Big5" ) ;
	reset () ;
	ch = 0 ;
}

QVTChar :: QVTChar ( char c )
{
	reset () ;
	ch = c ;
}

QVTChar :: ~QVTChar ()
{
}

void QVTChar :: fromBig5 ( const char * c )
{
	// string from YYText(), null-terminalted
	ch = big5codec -> toUnicode ( c ).at ( 0 ) ; // 0 if out-of-bound
}

