#ifndef TOKEN_H
#define TOKEN_H

namespace QVTToken
{
enum QVTToken {
	// Control Characters
	NUL=1, ETX, EOT, ENQ, BEL, BS, HT, LF, VT, FF, CR, SO, SI, 
	DC_ONE, DC_THREE, CAN, SUB, ESC, 

	// Control Sequences
	// from SET to UKN 
	SET, RESET, RIS,

	DECKPAM, DECKPNM, // Keypad Character Selection

	SCS, // Select Character Sets, IGNORED

	SGR,

	DECSTBM, // Scrolling Region

	// Cursor Movement
	CUU, CUD, CUF, CUB,
	CUP, HVP, IND, RI, NEL, DECSC, DECRC,

	// Tab Stops
	HTS, TBC,

	// Line Attributes
	DECDHL_ONE, DECDHL_TWO, DECSWL, DECDWL, 

	// Erasing
	EL, ED,

	// Editing
	DCH, IL, DL,

	// Print, Media Copy
	MC,

	// Reports
	DSR, CPR, DA, DECID, 

	// Test & adjustments
	DECALN, DECTST, 

	// Keyboard LEDs
	DECLL,

	// unkown sequense & default return
	UKN, DEFAULT, 

	// VT52 Compatible Mode is NOT SUPPORTED

	// BIG5 T.Chinese Characters
	BIG_FIVE,

	// URL
	URL, 

	// Number (for number.lex)
	NUMBER
} ;
} ;
#endif
