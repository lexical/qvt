#include <qfontmetrics.h>
#include "qvtedit.h"
#include <string>
#include <qpalette.h>

QVTEdit :: QVTEdit ( QWidget * parent, const char * name, WFlags f )
: QWidget ( parent, name, f ), pty ( this )
{
	textBuf = new QVTText ( 24, 24, 80 ) ; // buffer, height, width

	deffont.setFamily( "monospace" ) ;
	QFontMetrics fm( deffont ) ;

	charHeight = fm.height() ;
	charWidth = fm.charWidth( "ZZZ", 1 ) ;

	resize( charWidth * 80, charHeight * 24 ) ;

	QPalette p( palette() ) ;
	p.setColor( QPalette :: Normal, QColorGroup :: Background, Qt :: black ) ;
	setPalette( p ) ;

	pty.start () ;
}

QVTEdit :: ~QVTEdit ()
{
	delete textBuf ;
	pty.terminate () ;
	pty.wait () ;
}

void QVTEdit :: customEvent( QCustomEvent * e )
{
	QVTPtyEvent * pe = static_cast <QVTPtyEvent *> ( e ) ;
	//qDebug("START");qDebug (pe->msg);qDebug("END");
/*
	int l = strlen ( pe->msg ) ;
	for ( int i = 0 ; i < l ; ++i )
		qDebug ( "%c-%i", pe->msg [i], pe->msg [i] ) ;
*/

	std :: stringstream ss ;
	std :: stringstream ns ;
	ss << pe -> msg ;
	//qDebug("START");qDebug(ss.str().c_str());qDebug("END");

	int tok_id, ntok_id ;

	vtlex.switch_streams ( & ss, & std :: cout ) ;
	// switch_stream will cause EOF to occur
	// token that is broken into two pieces while transmitting
	// wound't be recognize

	// Solution :
	// 1) can class-while (global) stringstream solve this?
	// 2) use <<EOF>> in lex

	QVTChar ch;
	ch |= QVTChar :: QVT_RED_B;
	ch |= QVTChar :: QVT_WHITE_F;

	while ( tok_id = vtlex.yylex () )
	{
		if( tok_id != QVTToken::SGR and tok_id != QVTToken::DEFAULT and tok_id != QVTToken::LF and tok_id != QVTToken::CR )
			qDebug ( "*** " + QString :: number ( tok_id ) +" "+ ((char*)vtlex.YYText () + 1) ) ;

		if ( tok_id >= QVTToken :: SET and tok_id <= QVTToken :: UKN )
		{
			param.clear () ;
			ns.clear () ;
			ns << vtlex.YYText () ;
			nlex.switch_streams ( & ns, & std :: cout ) ;
			while ( ntok_id = nlex.yylex () )
				if ( ntok_id == QVTToken :: NUMBER )
					param.push_back ( str2int ( nlex.YYText () ) ) ;

			// set defChar according to param
			// or re-act according to the seq.
			if ( tok_id == QVTToken::SGR )
			{
				for( std::vector<int>:: iterator i = param.begin(); i != param.end(); ++ i )
				{
					//qDebug ( "*** " + QString :: number ( tok_id ) +" "+ ((char*)vtlex.YYText () + 1) ) ;

					switch( * i )
					{
					case 0:
						ch.reset();
						ch |= QVTChar :: QVT_WHITE_F;
						ch |= QVTChar :: QVT_BLACK_B;
						break;

					case 1:
						ch |= QVTChar :: QVT_SGR_BOLD;

					case 30: // cyan
						ch &= ~ QVTChar :: QVT_WHITE_F;
						ch |= QVTChar :: QVT_BLACK_F;
						break;

					case 31: // cyan
						ch &= ~ QVTChar :: QVT_WHITE_F;
						ch |= QVTChar :: QVT_RED_F;
						break;

					case 32: // cyan
						ch &= ~ QVTChar :: QVT_WHITE_F;
						ch |= QVTChar :: QVT_GREEN_F;
						break;

					case 33: // cyan
						ch &= ~ QVTChar :: QVT_WHITE_F;
						ch |= QVTChar :: QVT_BROWN_F;
						break;

					case 34: // cyan
						ch &= ~ QVTChar :: QVT_WHITE_F;
						ch |= QVTChar :: QVT_BLUE_F;
						break;

					case 35: // cyan
						ch &= ~ QVTChar :: QVT_WHITE_F;
						ch |= QVTChar :: QVT_MAGENTA_F;
						break;

					case 36: // cyan
						ch &= ~ QVTChar :: QVT_WHITE_F;
						ch |= QVTChar :: QVT_CYAN_F;
						break;

					case 37: // white
						ch |= QVTChar :: QVT_WHITE_F;
						break;

					default:
						qDebug( "->" + QString::number( * i ) );
					};	
				}
			}
			else if ( tok_id == QVTToken::CUP || tok_id == QVTToken::HVP )
			{
				if ( param.size() )
					textBuf -> to ( param[0], param[1] ) ;
				else
					textBuf -> to ( 1, 1 ) ;
				//qDebug (QString::number(param[0]), QString::number(param[1]));
			}
			else if ( tok_id == QVTToken::ED )
			{
				if ( ! param.size() )
					textBuf -> ed0 () ;
				else if ( param[0] == 1 )
					textBuf -> ed1 () ;
				else if ( param[0] == 2 )
					textBuf -> clear () ;
			}
			else if ( tok_id == QVTToken::EL )
			{
				if ( ! param.size() )
					textBuf -> el0 () ;
				else if ( param[0] == 1 )
					textBuf -> el1 () ;
				else if ( param[0] == 2 )
					textBuf -> clear () ;
			}
		}
		else if ( tok_id >= QVTToken :: NUL and tok_id <= QVTToken :: SUB )
		{
			if ( tok_id == QVTToken :: LF ) // linefeed(10)
			{
				textBuf -> lf () ;
			}
			else if ( tok_id == QVTToken :: CR )
			{
				textBuf -> cr () ;
			}
			else if ( tok_id == QVTToken :: HT )
			{
				textBuf -> ht () ;
			}
		}
		else if ( tok_id == QVTToken :: URL ) // URL
		{

		}
		else if ( tok_id == QVTToken :: BIG_FIVE )
		{
			qDebug(QString::number(tok_id) + " big");
/*
			QVTChar k ;
			k |= QVTChar::QVT_FULLWIDTH ;
			//qDebug(k.to_string<char, std::char_traits<char>, std::allocator<char> >().c_str());
			k.fromBig5 ( & vtlex.YYText () [ 0 ] ) ;
			textBuf -> insertw ( k ) ;
*/
		}
		else if ( tok_id == QVTToken :: DEFAULT )
		{
			// modify textBuf
			//qDebug(QString::number(tok_id) + " big");
			//QVTChar k ( vtlex.YYText () [ 0 ] ) ;
			ch.fromBig5 ( & vtlex.YYText () [ 0 ] ) ;
			textBuf -> insert ( ch ) ;
			//qDebug(QString::number(tok_id));
			//qDebug( "%s-%i", vtlex.YYText (),vtlex.YYText ()[0]);
			//printf ( "%s(%i)", vtlex.YYText (), tok_id ) ;
		}
		else
		{
			//printf ( "%s*%i*", vtlex.YYText (), tok_id ) ;
			qDebug ( "*** " + QString :: number ( tok_id ) +" "+ ((char*)vtlex.YYText () + 1) ) ;
	    }
	}
	//buffer.flush() ;
	//buffer << ss.str() ;
	//qDebug(ss.str().c_str());

	// redraw
	// repaint () ;
	update () ;
}

void QVTEdit :: paintEvent ( QPaintEvent * )
{
	QPainter paint( this );
	//QBrush b ( Qt::gray ) ;
	//paint.fillRect ( 0, 0, 80 * charWidth, 24 * charHeight, b ) ;

/*
	paint.setPen( Qt :: darkGray );

	// draw the grid for debugging
	for ( int i = 0 ; i < 80 ; ++ i )
		paint.drawLine ( i * charWidth, 0, i * charWidth, charHeight * 24 ) ;

	for ( int i = 0 ; i < 24 ; ++ i )
		paint.drawLine ( 0, i * charHeight, charWidth * 80, i * charHeight ) ;
*/

	// default color
	// to be removed when QVTChar's default color is set
	// not yet implmented
	QColor fcolor = paletteForegroundColor () ;
	QColor bcolor = paletteBackgroundColor () ;

	QPen p ;
	int x = 0, y = 0, px, py ;

	QVTString * row ;
	QVTString :: iterator col ;

	// draw text in QVTText (textBuf)
	for ( int r = 1 ; r <= 24 ; ++ r )
	{
		row = textBuf -> get ( r ) ;
		for ( col = row -> begin () ; col != row -> end () ; ++ col )
		{
			if (  col !=  row->begin () && ( * ( col - 1 ) & QVTChar :: QVT_FULLWIDTH ).any () )
			{
				//qDebug("full");
				++ x ; continue ;
			}

			px = charWidth * x ;
			py = charHeight * ( y + 1 ) ;

//qDebug(col->to_string<char, std::char_traits<char>, std::allocator<char> >().c_str());

			// set foreground color
			if ( ( * col & QVTChar :: QVT_WHITE_F ) == QVTChar :: QVT_BLACK_F )
				fcolor = Qt :: black ;

			else if ( ( * col & QVTChar :: QVT_WHITE_F ) == QVTChar :: QVT_RED_F )
				fcolor = Qt :: red ;

			else if ( ( *col & QVTChar :: QVT_WHITE_F ) == QVTChar :: QVT_GREEN_F )
				fcolor = Qt :: green ;

			else if ( ( * col & QVTChar :: QVT_WHITE_F ) == QVTChar :: QVT_BROWN_F )
				fcolor = Qt :: yellow ;

			else if ( ( * col & QVTChar :: QVT_WHITE_F ) == QVTChar :: QVT_BLUE_F )
				fcolor = Qt :: blue ;

			else if ( ( * col & QVTChar :: QVT_WHITE_F ) == QVTChar :: QVT_MAGENTA_F )
				fcolor = Qt :: magenta ;

			else if ( ( * col & QVTChar :: QVT_WHITE_F ) == QVTChar :: QVT_CYAN_F )
				fcolor = Qt :: cyan ;

			else if ( ( * col & QVTChar :: QVT_WHITE_F ) == QVTChar :: QVT_WHITE_F )
				fcolor = Qt :: gray ;
			//else
			//	qDebug ( "fcolor not set" + QString::number(x)+" "+QString::number(y) ) ;

			// set background color
			if ( ( * col & QVTChar::QVT_WHITE_B ) == QVTChar :: QVT_BLACK_B )
				bcolor = Qt :: black ;

			else if ( ( * col & QVTChar::QVT_WHITE_B ) == QVTChar :: QVT_RED_B)
				bcolor = Qt :: red ;

			else if ( ( * col & QVTChar::QVT_WHITE_B ) == QVTChar :: QVT_GREEN_B )
				bcolor = Qt :: green ;

			else if ( ( * col & QVTChar::QVT_WHITE_B ) == QVTChar :: QVT_BROWN_B)
				bcolor = Qt :: yellow ;

			else if ( ( * col & QVTChar::QVT_WHITE_B ) == QVTChar :: QVT_BLUE_B )
				bcolor = Qt :: blue ;

			else if ( ( * col & QVTChar::QVT_WHITE_B ) == QVTChar :: QVT_MAGENTA_B )
				bcolor = Qt :: magenta ;

			else if ( ( * col & QVTChar::QVT_WHITE_B ) == QVTChar :: QVT_CYAN_B)
				bcolor = Qt :: cyan ;

			else if ( ( * col & QVTChar::QVT_WHITE_B ) == QVTChar :: QVT_WHITE_B )
				bcolor = Qt :: gray ;
			//else
			//	qDebug ( "bcolor not set" + QString::number(x)+" "+QString::number(y) ) ;

/*
			// draw background color
			p.setColor ( bcolor ) ;
			paint.setPen (p) ;
			paint.drawRect ( px, py - charHeight, charWidth, charHeight ) ;
*/

			p.setColor (fcolor ) ;

			paint.setPen (p) ;
			//paint.setBackgroundMode( Qt :: OpaqueMode ) ;
			paint.setBackgroundColor( bcolor ) ;

			// style (bold/underline ... etc)
			if ( ( * col & QVTChar :: QVT_SGR_REVERVED )  == QVTChar :: QVT_SGR_BOLD )
			{
				fcolor = fcolor.light () ;
			}

			if ( ( * col & QVTChar :: QVT_SGR_REVERVED ) == QVTChar :: QVT_SGR_DIM )
			{
				fcolor = fcolor.dark () ;
			}

			if ( ( * col & QVTChar :: QVT_SGR_REVERVED ) == QVTChar :: QVT_SGR_UNDERLINE )
			{
				paint.drawLine ( px, py - 1, px + charWidth - 1, py - 1 ) ;
				if ( ( * col & QVTChar :: QVT_FULLWIDTH ).any () )
					paint.drawLine ( px + charWidth, py - 1, px + charWidth * 2 - 1, py - 1 ) ;

			}

			if ( ( * col & QVTChar :: QVT_SGR_REVERVED ) == QVTChar :: QVT_SGR_REVERSE )
			{
			}

			if ( ( * col & QVTChar :: QVT_SGR_REVERVED ) == QVTChar :: QVT_SGR_BLINK )
			{
			}

			if ( ( * col & QVTChar :: QVT_URL_SET ).any () )
			{
			}
			paint.setFont ( deffont ) ;

			paint.drawText ( px + 1, py - 4, col -> ch ) ; //qDebug(QString(col->ch));
			++ x ;
		}
		x = 0 ;
		++ y ;
	}
}

void QVTEdit :: keyPressEvent ( QKeyEvent * e )
{
	if ( e -> state () == Qt::ShiftButton )
	{
	}
	else if ( e -> state () == Qt::ControlButton )
	{
	}
	else if ( e -> state () == Qt::AltButton )
	{
	}
	else
	{
		e -> accept () ;
		char * msg = const_cast <char *> ( e -> text ().ascii () ) ;
		write ( pty.md, static_cast <void *> ( msg ), e -> text ().length () ) ;
		// will msg be memory leaking here???
		// delete msg ;
	}
}

// private member function
int QVTEdit :: str2int ( const char * c )
{
	std :: stringstream ss ( c ) ;
	int n ;
	ss >> n ;
	return n ;
}
