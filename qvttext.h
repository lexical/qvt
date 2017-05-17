#ifndef QVTTEXT_H
#define QVTTEXT_H

#include <deque>
#include "qvtstring.h"

class QVTText : public std :: deque <QVTString>
{
public :
	QVTText ( int n, int height_i, int width_i ) ;
	~QVTText () ;

	QVTChar charAttribute ;

	QVTChar & get ( int _y, int _x ) ;
	QVTString * get ( int _y ) ;

	void scroll () ;
	// int replace () ;
	void insert ( const QVTChar & c ) ;
	void insertw ( const QVTChar & c ) ;

	void to ( int _y, int _x ) ;
	void lf () ;
	void cr () ; 
	void ht () ;

	void clear () ;
	void el0 () ;
	void el1 () ;
	void ed0 () ;
	void ed1 () ;


private :
	int curx, cury, height, width ;
	int y ( int row ) ;

} ;
#endif
