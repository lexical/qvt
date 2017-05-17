#ifndef QVTCHAR_H
#define QVTCHAR_H

#include <bitset>
#include <qstring.h>
#include <qtextcodec.h> 

class QVTChar : public std::bitset <11>
{
public :
	QVTChar () ;
	QVTChar ( char c ) ;
	~QVTChar () ;

	// void operator= ( const QChar & c ) ;

	void fromBig5 ( const char * c ) ;

	static std::bitset <11> QVT_BLACK_B    ;
	static std::bitset <11> QVT_RED_B      ;
	static std::bitset <11> QVT_GREEN_B    ;
	static std::bitset <11> QVT_BROWN_B    ;
	static std::bitset <11> QVT_BLUE_B     ;
	static std::bitset <11> QVT_MAGENTA_B  ;
	static std::bitset <11> QVT_CYAN_B     ; // 110
	static std::bitset <11> QVT_WHITE_B    ; // 111
	
	static std::bitset <11> QVT_BLACK_F ; // 000 000
	static std::bitset <11> QVT_RED_F ; // 001 000
	static std::bitset <11> QVT_GREEN_F ; // 010 000
	static std::bitset <11> QVT_BROWN_F ; // 011 000
	static std::bitset <11> QVT_BLUE_F ; // 100 000
	static std::bitset <11> QVT_MAGENTA_F ; // 101 000
	static std::bitset <11> QVT_CYAN_F ; // 110 000
	static std::bitset <11> QVT_WHITE_F ; // 111 000
	
	static std::bitset <11> QVT_SGR_RESET ; // 000 : 000 000
	static std::bitset <11> QVT_SGR_BOLD ; // 001
	static std::bitset <11> QVT_SGR_DIM ; // 010
	static std::bitset <11> QVT_SGR_UNDERLINE ; // 011
	static std::bitset <11> QVT_SGR_BLINK ; // 100
	static std::bitset <11> QVT_SGR_REVERSE ; // 101
	static std::bitset <11> QVT_SGR_HIDDEN ; // 110
	static std::bitset <11> QVT_SGR_REVERVED ; // 111
	
	static std::bitset <11> QVT_URL_RESET ; // 0 : 000 000 000
	static std::bitset <11> QVT_URL_SET ; // 1

	static std::bitset <11> QVT_FWDISABLE ; // 00 : 00 000 000 000
	static std::bitset <11> QVT_FULLWIDTH ; // 01

	/*enum { QVT_BLACK_B = 0, QVT_RED_B, QVT_GREEN_B, QVT_BROWN_B, QVT_BLUE_B, QVT_MAGENTA_B, QVT_CYAN_B, QVT_WHITE_B, 
			
			QVT_BLACK_F, QVT_RED_F, QVT_GREEN_F, QVT_BROWN_F, QVT_BLUE_F, QVT_MAGENTA_F, QVT_CYAN_F, QVT_WHITE_F, 
			
			QVT_SGR_RESET, QVT_SGR_BOLD, QVT_SGR_DIM, QVT_SGR_UNDERLINE, QVT_SGR_REVERSE, QVT_SGR_BLINK, QVT_SGR_HIDDEN, QVT_SGR_RESERVED, 
			
			QVT_URL_RESET, QVT_URL_SET, 
			
			QVT_FW_RESET, QVT_FW_SET } ;
*/
	QChar ch ;

private :
	static QTextCodec * big5codec ;
} ;

#endif
