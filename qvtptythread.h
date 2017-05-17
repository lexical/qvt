#ifndef QVTPTYTHREAD_H
#define QVTPTYTHREAD_H

#include <qthread.h>
#include <qapplication.h>
#include "qvtptyevent.h"
#include <pty.h>
#include <unistd.h>
#include <sys/select.h>

class QVTPtyThread : public QThread
{
public :
	QVTPtyThread ( QObject * p ) ;
	virtual void run () ;

	int md ;

private :
	QObject * parent ;
} ;
#endif
