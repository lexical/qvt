#include "qvtptythread.h"
#include <sys/ioctl.h>
#include <qstring.h>

QVTPtyThread :: QVTPtyThread ( QObject * p )
: parent ( p )
{
}

void QVTPtyThread :: run ()
{
	//int md ; // master descriptor
	int pid ;

	winsize wsize ;
	wsize.ws_row = 24 ;
	wsize.ws_col = 80 ;

	if ( ( pid = forkpty ( & md, NULL, NULL, NULL ) ) == 0 )
	{
		//ioctl ( md, TIOCGWINSZ, (char *) & wsize ) ;
		// child process
		execl ( "/bin/bash", "bash", ( char * ) 0 ) ;
	}
	else
	{
		ioctl ( md, TIOCSWINSZ, (char *) & wsize ) ;
		// parent process
		fd_set readset ;

		char * c ;
		QVTPtyEvent * e ;

		int n ;
		while (1)
		{
			FD_ZERO ( & readset ) ;
			FD_SET ( md, & readset ) ;
			select ( md + 1, & readset, NULL, NULL, NULL ) ;

			c = new char [ 1024 ] ;
			n = read ( md , ( void * ) c, 1023 /*SSIZE_MAX*/ ) ;

			if( n >= 0 )
			{
				c [ n ] = 0 ;

				e = new QVTPtyEvent ( n, c ) ;
				QApplication :: postEvent ( parent, e ) ;
			}
			else
			{
				QApplication :: exit();
				break;
			}
		}
	}
}
