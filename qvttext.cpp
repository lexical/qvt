#include "qvttext.h"

QVTText :: QVTText ( int n, int height_i, int width_i )
: std :: deque <QVTString> (n), curx (0), cury (0), height (height_i), width (width_i)
{
}

QVTText :: ~QVTText ()
{
}

QVTChar & QVTText :: get ( int _y, int _x )
{
	return at ( y ( _y - 1 ) ).idx ( _x - 1 ) ;
}

QVTString * QVTText :: get ( int _y )
{
	return & at ( y ( _y - 1 ) ) ;
}

void QVTText :: insert ( const QVTChar & c )
{
	at ( y ( cury ) ).idx ( curx ) = c ;
	++ curx ;
}

void QVTText :: insertw ( const QVTChar & c )
{
	at ( y ( cury ) ).idx ( curx ) = c ;
	curx += 2 ;
}

void QVTText :: scroll ()
{
	pop_back () ;

	QVTString s ;
	push_front ( s ) ;
}

void QVTText::to ( int _y, int _x )
{
	curx = _x - 1 ;
	cury = _y - 1 ;
}

void QVTText :: lf ()
{
	// modify latter from screen margin to history length
	if ( cury == height - 1 ) // margin
		scroll () ;
	else
		++ cury ;
}

void QVTText :: cr ()
{
	curx = 0 ;
}

void QVTText :: ht ()
{
	curx = ( curx / 8 + 1 ) * 8 ;
}

void QVTText :: clear () // Clear entire line
{
}

void QVTText :: el0 () // Clear line from cursor right
{
	QVTString & s = at ( y ( cury ) ) ;
	int sz = s.size () ;
	for ( int i = curx ; i < sz ; ++ i )
		s.pop_back () ;
}

void QVTText :: el1 () // Clear line from cursor left
{
}

void QVTText :: ed0 () // Clear screen from cursor down
{
	for ( int i = 0 ; i <= y ( cury ) ; ++ i )
		at ( i ).clear () ;
}

void QVTText :: ed1 () // Clear screen from cursor up
{
}

// private member function

int QVTText :: y ( int row )
{
	return height - row - 1 ;
}
