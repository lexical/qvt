#include "qvtptyevent.h"

QVTPtyEvent :: QVTPtyEvent ( int len, char * m )
: QCustomEvent( QEvent :: User + 1 ), length ( len ), msg ( m )
{
}

QVTPtyEvent :: ~QVTPtyEvent ()
{
	delete msg ;
}
