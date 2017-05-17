#ifndef QVTEDIT_H
#define QVTEDIT_H

#include <unistd.h>
#include <sstream>
#include <iostream>
#include <qwidget.h>
#include <qpainter.h>
#include <qfont.h>
#include "qvttext.h"
#include "qvtptyevent.h"
#include "qvtptythread.h"
#include "lex/lex.h"

#include <stdio.h>

class QVTEdit : public QWidget
{
public :
	QVTEdit ( QWidget * parent = 0, const char * name = 0, WFlags f = 0 ) ;
	~QVTEdit () ;

protected :
	virtual void paintEvent ( QPaintEvent * ) ;
	virtual void customEvent ( QCustomEvent * e ) ;
	virtual void keyPressEvent ( QKeyEvent * e ) ;

	QVTText * textBuf ;
	QVTPtyThread pty ;

	VTFlexLexer vtlex ;
	NFlexLexer nlex ;

	QFont deffont;

private :
	int charHeight, charWidth ;
	QVTChar defChar ; // default char & attributes
	std :: vector <int> param ;

	int str2int ( const char * c ) ;
} ;
#endif
