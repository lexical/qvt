#ifndef QVTSTRING_H
#define QVTSTRING_H

#include "qvtchar.h"
#include <vector>

// maybe use std :: list is better
class QVTString : public std :: vector <QVTChar>
{
public :
	QVTString () ;
	~QVTString () ;

	QVTChar & idx ( int i ) ;

	//void insert ( int idx, const QVTChar & c ) ;

} ;
#endif
