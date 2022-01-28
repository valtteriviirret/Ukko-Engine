#include "Move.hh"

namespace Move
{
	// create new empty piece
	void emptyPiece(int x, int y)
	{
		Piece piece;
		piece.x = x;
		piece.y = y;
		piece.type = NONE;
		Sqr::getSquare(piece.x, piece.y).piece = piece;
	}

	void execute(Piece& source, Square target)
	{
		if(target.piece.type == 5)
		{
			std::cout << "Check!\n";
		}


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
					emptyPiece(0, 7);
					
					// empty piece for old king
					emptyPiece(4, 7);

					// update rook's position
					Pieces::get(24).x = source.x + 1;

					// update rook
					Sqr::getSquare(Pieces::get(24).x, Pieces::get(24).y).piece = Pieces::get(24);

					// update king
					Sqr::getSquare(source.x, source.y).piece = source;

				}
				// engine's queen side castle
				else
				{

				}
				
			}

			// king side castle, hmm why not work
			if(source.x + 2 == target.x)
			{
				std::cout << "king side castle";
				if(source.user == PLAYER)
				{
					std::cout << "this should print as well";
				}
				else
				{

				}
			}
		}

		// if rook is moved
		if(source.type == ROOK)
		{
			if(source.user == PLAYER)
			{
				if(source.x == 0)
					playerQsideRookMoved = true;
				if(source.x == 7)
					playerKsideRookMoved = true;
			}

			else
			{
				if(source.x == 0)
					engineQsideRookMoved = true;
				if(source.x == 7)
					engineKsideRookMoved = true;

			}
		}

		// if moving to enemy's square, something wrong here!
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
		emptyPiece(srcSquare.x, srcSquare.y);

		// change source values (updating graphics)
		source.x = target.x;
		source.y = target.y;

		// update move's piece
		Sqr::getSquare(target.x, target.y).piece = source;
	}

}

