#include <qvtstring.h>

QVTString :: QVTString ()
{
}

QVTString :: ~QVTString ()
{
}

QVTChar & QVTString :: idx ( int i )
{
	int s = size () ;

	if ( i < s )
		return at ( i ) ;
	else
	{
		QVTChar c ;
		for ( int k = 0 ; k <= i - s ; ++ k )
			push_back ( c ) ;

		return at ( i ) ;
	}
}

/*
void QVTString :: insert ( int idx, const QVTChar & c )
{
	QVTChar tc ( 'E' ) ;
	int s = size () ;

	if ( idx >= s )
		for ( int t = 0 ; t < idx - s ; ++ t )
			push_back ( tc ) ;

	iterator i = begin () + idx ;
	std :: vector <QVTChar> :: insert ( i, c ) ;
}*/
