#include "Move.hh"

namespace Move
{
	void execute(Piece& source, Square target)
	{
		// create new "piece"
		Piece piece;
		piece.type = NONE;

		// castling
		if(source.type == KING)
		{
			// king side castle
			if(source.x - 2 == target.x)
			{
				// move king to correct place
				source.x -= 2;

				// move rook to correct place
				if(source.user == PLAYER)
				{
					Pieces::get(24).x = source.x + 1;
					piece.x = 0;
					piece.y = 7;

					// update rook empty place
					Sqr::getSquare(piece.x, piece.y).piece = piece;
					// update new rook
					Sqr::getSquare(Pieces::get(24).x, Pieces::get(24).y).piece = Pieces::get(24);
					Sqr::getSquare(source.x, source.y).piece = source;
				}
				else
				{
					// king side castle
				}
				
			}
			if(source.x + 2 == target.x)
			{
				std::cout << "king side castle";
				// queenside castle
			}
		}
		else
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

			// get square of source
			Square srcSquare = Sqr::getSquare(source.x, source.y);

			piece.x = srcSquare.x;
			piece.y = srcSquare.y;

			// change source values (updating graphics)
			source.x = target.x;
			source.y = target.y;

			// updating squares
			Sqr::getSquare(srcSquare.x, srcSquare.y).piece = piece;
			Sqr::getSquare(target.x, target.y).piece = source;
		}
	}
}
