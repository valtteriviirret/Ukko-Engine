#include "Move.hh"

namespace Move
{
	void execute(Piece& source, Square target)
	{
		// if moving to enemy's square
		if(target.piece.type != 6 && target.piece.type != 5)
		{
			for(int i = 0; i < 32; i++)
			{
				if(Pieces::get(i).x == target.x && Pieces::get(i).y == target.y)
				{
					Pieces::get(i).alive = false;
				}
			}
		}

		// get square of source and destination
		Square srcSquare = Sqr::getSquare(source.x, source.y);

		// creating new empty piece for source's place
		Piece piece;
		piece.x = srcSquare.x;
		piece.y = srcSquare.y;
		piece.type = NONE;

		// change source values (updating graphics)
		source.x = target.x;
		source.y = target.y;

		// updating squares
		Sqr::getSquare(srcSquare.x, srcSquare.y).piece = piece;
		Sqr::getSquare(target.x, target.y).piece = source;
	}
}
