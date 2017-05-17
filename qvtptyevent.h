#ifndef QVTPTYEVENT_H
#define QVTPTYEVENT_H

#include <qevent.h>
#include "lex/qvttoken.h"

class QVTPtyEvent : public QCustomEvent
{
public :
	QVTPtyEvent ( int len, char *  m ) ;
	~QVTPtyEvent () ;

	int length ;
	char * msg ;
} ;
#endif
