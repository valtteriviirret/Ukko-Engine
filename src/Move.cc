#include "Move.hh"
#include "Pieces.hh"
#include "SquareManager.hh"

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

	// make castling in function later
	void castlingFunc()
	{

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
			if(source.user == PLAYER)
			{
				playerKingMoved = true;

				// queen side castle
				if(source.x - 2 == target.x)
				{
					// empty space for old rook
					emptyPiece(0, 7);
					
					// empty piece for old king
					emptyPiece(4, 7);

					// move king to correct place
					source.x -= 2;

					// move rook to correct place
					Pieces::get(24).x += 3;

					// update rook, if problems occurs they gotta be here
					Sqr::getSquare(Pieces::get(24).x, Pieces::get(24).y).piece = Pieces::get(24);

					// update king
					Sqr::getSquare(source.x, source.y).piece = source;

				}

				// king side castle
				if(source.x + 2 == target.x)
				{
					// empty space for old rook
					emptyPiece(7, 7);

					// empty space for old king
					emptyPiece(4, 7);

					// move king to correct place
					source.x += 2;

					// move rook to correct place
					Pieces::get(25).x -= 2;
					
					// update rook
					Sqr::getSquare(Pieces::get(25).x, Pieces::get(25).y).piece = Pieces::get(25);

					// update king
					Sqr::getSquare(source.x, source.y).piece = source;

				}

				
			}

			// (if source.user == ENGINE)
			else
			{

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

		// if moving to enemy's square, if problems were to occur in the future its prolly here
		//
		// also this if must change later
		if(target.piece.type != 6 && target.piece.type != 5)
		{
			for(int i = 0; i < 32; i++)
			{
				if(Pieces::get(i).x == target.x && Pieces::get(i).y == target.y)
				{
					// destroy the old piece
					Piece newPiece;
					newPiece.type = NONE;
					Pieces::get(i) = newPiece;
				}
			}
		}
		
		// REGULAR MOVE

		// create empty piece for source's place
		Square srcSquare = Sqr::getSquare(source.x, source.y);
		emptyPiece(srcSquare.x, srcSquare.y);

		// change source values to target
		source.x = target.x;
		source.y = target.y;

		// update moved pieces place
		Sqr::getSquare(source.x, source.y).piece = source;
	}

}

