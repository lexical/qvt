#include <qapplication.h>
#include "qvtedit.h"

int main ( int argc, char ** argv)
{
	QApplication a ( argc, argv ) ;

	QVTEdit w ;
	a.setMainWidget ( & w ) ;
	w.show () ;
	return a.exec () ;
}
