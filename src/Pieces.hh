#ifndef PIECES_HH
#define PIECES_HH

#include "Piece.hh"
#include "SquareManager.hh"
#include "Settings.hh"
#include "Global.hh"

namespace Pieces
{
	// initializing pieces in their correct positions
	void init();

	// getting individual piece
	Piece& get(int n);

	Piece* getModify(int n);

	Piece* getReal(Piece* piece);

	Piece* getReal(Square* square);

	Piece* getXY(int x, int y);

	// set piece
	void set(Piece p, int x, int y);

	void setSquare(Piece* p, Square s);

	void emptyPiece(int x, int y); 

	void emptySquare(int x, int y);

	void makeEmptySquare(Square* square);

	void makeEmptyPiece(Piece* piece);
}

#endif

