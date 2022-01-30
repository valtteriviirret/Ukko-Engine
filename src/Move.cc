#include "Move.hh"

namespace Move
{
	// algebraic notation of the move
	std::string name;

	// parts of the notation
	std::string nameSource;
	std::string nameX;
	std::string nameY;

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

	void readName() { std::cout << name << "\n"; }
	std::string getName() { return name; }

	void execute(Piece& source, Square target)
	{
		name = "";

		switch(source.type)
		{
			case PAWN: break;
			case NONE: break;
			case ROOK: nameSource = "R"; break;
			case KING: nameSource = "K"; break;
			case QUEEN: nameSource = "Q"; break;
			case KNIGHT: nameSource = "N"; break;
			case BISHOP: nameSource = "B"; break;
		}

		switch(target.x)
		{
			case 0: nameX = "a"; break;	
			case 1: nameX = "b"; break;
			case 2: nameX = "c"; break;
			case 3: nameX = "d"; break;
			case 4: nameX = "e"; break;
			case 5: nameX = "f"; break;
			case 6: nameX = "g"; break;
			case 7: nameX = "h"; break;
		}

		switch(target.y)
		{
			case 0: nameY = "8"; break;
			case 1: nameY = "7"; break;
			case 2: nameY = "6"; break;
			case 3: nameY = "5"; break;
			case 4: nameY = "4"; break;
			case 5: nameY = "3"; break;
			case 6: nameY = "2"; break;
			case 7: nameY = "1"; break;
		}

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
	
		// if rook is moved, has to do with castling
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
		
		// pawn promotion
		if(source.type == PAWN)
		{
			if(source.user == PLAYER)
			{
				// last row
				if(target.y == 0)
				{
					int choice;
					std::cout 	<< "PLAYER PAWN GETS PROMOTED IN " << nameX << nameY << "\n"
								<< "CHOOSE PIECE:\n1:QUEEN\n2:ROOK\n3:BISHOP\n4:KNIGHT\n";
					std::cin >> choice;

					switch(choice)
					{
						case 2: source.type = ROOK; break;
						case 1: source.type = QUEEN; break;
						case 3: source.type = BISHOP; break;
						case 4: source.type = KNIGHT; break;
					}
				}
			}
			// source.user == ENGINE
			else
			{
				if(target.y == 7)
				{
					source.type = QUEEN;
				}
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

		// make the notation
		name = nameSource + nameX + nameY;

		// read info of the move in console
		readName();
	}
}

