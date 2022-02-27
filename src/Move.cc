#include "Move.hh"

namespace Move
{
	// algebraic notation of the move
	std::string name;

	// parts of the notation
	std::string nameSource;
	char nameX;
	char nameY;
	std::string promotion;

	void castlingFunc(Piece* source, Piece& rook, bool player, bool queenSide, bool real)
	{
		int y;
		nameSource = "";

		// make king's square empty
		if(player)
		{
			Pieces::emptySquare(4, 7);
			y = 7;
		}
		else
		{
			Pieces::emptySquare(4, 0);
			y = 0;
		}
		
		// make rook's square empty and move pieces
		if(queenSide)
		{
			Pieces::emptySquare(0, y);
			if(real)
			{
				source->x -= 2;
				rook.x += 3;
			}
			name = "0-0-0";
		}
		else
		{
			Pieces::emptyPiece(7, y);
			if(real)
			{
				source->x += 2;
				rook.x -= 2;
			}
			name = "0-0";
		}

		// update board
		Sqr::squareHelper(rook.x, rook.y)->piece = rook;
		Sqr::squareHelper(source->x, source->y)->piece = *source;
	}

	void readName() { std::cout << name << "\n"; }
	std::string getName() { return name; }

	void execute(Piece* source, Square* target, bool real)
	{
		name = "";
		nameSource = "";
		promotion = "";

		switch(source->type)
		{
			case NONE: break;
			case PAWN: nameSource = "Pawn"; break;
			case ROOK: nameSource = "Rook"; break;
			case KING: nameSource = "King"; break;
			case QUEEN: nameSource = "Queen"; break;
			case KNIGHT: nameSource = "Knight"; break;
			case BISHOP: nameSource = "Bishop"; break;
		}

		switch(target->x)
		{
			case 0: nameX = 'A'; break;
			case 1: nameX = 'B'; break;
			case 2: nameX = 'C'; break;
			case 3: nameX = 'D'; break;
			case 4: nameX = 'E'; break;
			case 5: nameX = 'F'; break;
			case 6: nameX = 'G'; break;
			case 7: nameX = 'H'; break;
		}

		switch(target->y)
		{
			case 0: nameY = '8'; break;
			case 1: nameY = '7'; break;
			case 2: nameY = '6'; break;
			case 3: nameY = '5'; break;
			case 4: nameY = '4'; break;
			case 5: nameY = '3'; break;
			case 6: nameY = '2'; break;
			case 7: nameY = '1'; break;
		}

		// castling
		if(source->type == KING)
		{
			if(source->user == PLAYER)
			{
				Global::playerKingMoved = true;

				// queen side castle
				if(source->x - 2 == target->x)
					castlingFunc(source, Pieces::get(24), true, true, real);

				// king side castle
				if(source->x + 2 == target->x)
					castlingFunc(source, Pieces::get(25), true, false, real);
				
			}

			// (if source.user == ENGINE)
			else
			{
				Global::engineKingMoved = true;

				if(source->x - 2 == target->x)
					castlingFunc(source, Pieces::get(8), false, true, real);

				if(source->x + 2 == target->x)
					castlingFunc(source, Pieces::get(9), false, false, real);
			}
		}
	
		// if rook is moved, has to do with castling
		if(source->type == ROOK)
		{
			if(source->user == PLAYER)
			{
				if(source->x == 0)
					if(real)
						Global::playerQsideRookMoved = true;
				if(source->x == 7)
					if(real)
						Global::playerKsideRookMoved = true;
			}

			else
			{
				if(source->x == 0)
					if(real)
						Global::engineQsideRookMoved = true;
				if(source->x == 7)
					if(real)
						Global::engineKsideRookMoved = true;
			}
		}

		
		// pawn promotion
		if(source->type == PAWN)
		{
			if(source->user == PLAYER)
			{
				// last row
				if(target->y == 0)
				{
					std::cout << "PLAYER PAWN GETS PROMOTED IN " << nameX << nameY << "\n";
					std::cout << "CHOOSE PIECE:\n";
					showPieces

					bool choiceMade = false;
					char choice;

					while(!choiceMade)
					{
						std::cin >> choice;

						//Piece* sqrOrig = &Sqr::squareHelper(target->x, target->y)->piece;

						switch(choice)
						{
							case 'Q':
								source->type = QUEEN;
								target->piece.type = QUEEN;
								promotion = 'Q';
								choiceMade = true;
								break;
							case 'R':
								source->type = ROOK;
								target->piece.type = ROOK;
								promotion = 'R';
								choiceMade = true;
								break;
							case 'B':
								source->type = BISHOP;
								target->piece.type = BISHOP;
								promotion = 'B';
								choiceMade = true;
								break;
							case 'N':
								source->type = KNIGHT;
								target->piece.type = KNIGHT;
								promotion = 'N';
								choiceMade = true;
								break;
							default:
								std::cout << "INCORRECT OPTION\nCHOOSE AGAIN!\n";
								showPieces
								break;
						}
					}
				}
			}
			// source.user == ENGINE
			else
			{
				// engine always picks queen, at least for now
				if(target->y == 7)
				{
					if(real)
						source->type = QUEEN;
					
					//Piece* sqrOrig = &Sqr::squareHelper(target->x, target->y)->piece;
					target->piece.type = QUEEN;
					promotion = 'Q';
				}
			}
		}

		// TODO THIS
		// en passant move
		if(source->type == PAWN)
		{
			if(Global::en_passant)
			{
				if(target->x == Global::en_passant->x && target->y == Global::en_passant->y)
				{
					if(source->user == PLAYER)
					{
						if(real)
							Pieces::emptySquare(target->x, (target->y + 1));
						Pieces::emptySquare(target->x, (target->y + 1));
					}
				
					else
					{
						if(real)
							Pieces::emptySquare(target->x, (target->y - 1));
						Pieces::emptySquare(target->x, (target->y - 1));
					}
				}
			}
		}

		// make en passant squares
		//
		//TODO fix this
		if(source->type == PAWN)
		{
			if(source->user == PLAYER)
			{
				if(source->y == 6 && target->y == 4)
					Global::en_passant = Sqr::squareHelper(source->x, 5);
				else
					Global::en_passant = nullptr;
			}
			else
			{
				if(source->y == 1 && target->y == 3)
					Global::en_passant = Sqr::squareHelper(source->x, 2);
				else
					Global::en_passant = nullptr;
			}
		}
		else
			Global::en_passant = nullptr;


		// REGULAR MOVE
		
		// capturing piece
		if(target->piece.type != 6)
		{
			if(real)
				Pieces::emptyPiece(target->x, target->y);

			if(real)
				Pieces::emptySquare(target->x, target->y);
			else
				Pieces::makeEmpty(target);
		}

		// make the source square empty
		if(real)
			Pieces::emptySquare(source->x, source->y);
		//else
			//TODO

		// move the piece
		if(real)
		{
			source->x = target->x;
			source->y = target->y;
		}

		// update square
		Sqr::squareHelper(source->x, source->y)->piece = *source;
	
		if(real)
		{
			// make the notation
			name = name + nameSource + " to " + nameX + nameY + promotion;

			// read info of the move in console
			readName();

			// change turn
			if(source->user == PLAYER)
				Global::playerTurn = false;
			else
				Global::playerTurn = true;
		}
	}
}


