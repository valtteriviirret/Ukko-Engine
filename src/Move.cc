#include "Move.hh"
#include "SquareManager.hh"

namespace Move
{
	// create new empty piece
	void emptyPiece(Piece& source, int x, int y)
	{
		Piece piece;
		piece.x = x;
		piece.y = y;
		piece.type = NONE;
		source.user == PLAYER ? piece.user = ENGINE : piece.user = PLAYER;
		Sqr::getSquare(piece.x, piece.y).piece = piece;
	}

	void execute(Piece& source, Square target)
	{
		// castling
		if(source.type == KING)
		{
			// queen side castle
			if(source.x - 2 == target.x)
			{
				// move king to correct place
				source.x -= 2;

				// move rook to correct place
				if(source.user == PLAYER)
				{
					// empty space for old rook
					emptyPiece(source, 0, 7);
					
					// empty piece for old king
					emptyPiece(source, 4, 7);

					// update rook's position
					Pieces::get(24).x = source.x + 1;

					// update rook
					Sqr::getSquare(Pieces::get(24).x, Pieces::get(24).y).piece = Pieces::get(24);

					// update king
					Sqr::getSquare(source.x, source.y).piece = source;

				}
				
			}
			if(source.x + 2 == target.x)
			{
				std::cout << "king side castle";
				// queenside castle
			}
		}

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

		// REGULAR MOVE

		// create empty piece for source's place
		Square srcSquare = Sqr::getSquare(source.x, source.y);
		emptyPiece(source, srcSquare.x, srcSquare.y);

		// change source values (updating graphics)
		source.x = target.x;
		source.y = target.y;

		// update move's piece
		Sqr::getSquare(target.x, target.y).piece = source;
	}

}

