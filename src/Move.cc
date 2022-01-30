#include "Move.hh"
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

	void castlingFunc(Piece& source, Piece& rook, bool player, bool queenSide)
	{
		int y;

		// make king's square empty
		if(player)
		{
			emptyPiece(4, 7);
			y = 7;
		}
		else
		{
			emptyPiece(4, 0);
			y = 0;
		}
		
		// make rook's square empty and move pieces
		if(queenSide)
		{
			emptyPiece(0, y);
			source.x -= 2;
			rook.x += 3;
		}
		else
		{
			emptyPiece(7, y);
			source.x += 2;
			rook.x -= 2;
		}

		// update board
		Sqr::getSquare(rook.x, rook.y).piece = rook;
		Sqr::getSquare(source.x, source.y).piece = source;
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
				Global::playerKingMoved = true;

				// queen side castle
				if(source.x - 2 == target.x)
					castlingFunc(source, Pieces::get(24), true, true);

				// king side castle
				if(source.x + 2 == target.x)
					castlingFunc(source, Pieces::get(25), true, false);
				
			}

			// (if source.user == ENGINE)
			else
			{
				Global::engineKingMoved = true;

				if(source.x - 2 == target.x)
					castlingFunc(source, Pieces::get(8), false, true);
				if(source.x + 2 == target.x)
					castlingFunc(source, Pieces::get(9), false, false);

			}
		}

		// if rook is moved
		if(source.type == ROOK)
		{
			if(source.user == PLAYER)
			{
				if(source.x == 0)
					Global::playerQsideRookMoved = true;
				if(source.x == 7)
					Global::playerKsideRookMoved = true;
			}

			else
			{
				if(source.x == 0)
					Global::engineQsideRookMoved = true;
				if(source.x == 7)
					Global::engineKsideRookMoved = true;

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

