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

	Piece* realSource = nullptr;
	Piece* realTarget = nullptr;

	/*
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
	*/

	void readName() { std::cout << name << "\n"; }
	std::string getName() { return name; }

	void execute(Square* source, Square* target, bool real)
	{
		// get real piece
		if(real)
		{
			realSource = Pieces::getReal(source);

			name = "";
			nameSource = "";
			promotion = "";

			switch(source->piece.type)
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
		}

		/*
		// castling
		if(source->piece.type == KING)
		{
			if(source->piece.user == PLAYER)
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
		*/
	
		// if rook is moved, has to do with castling
		if(real)
		{
			if(source->piece.type == ROOK)
			{
				if(source->piece.user == PLAYER)
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
		}

	
		if(real)
		{
			// pawn promotion
			if(source->piece.type == PAWN)
			{
				if(source->piece.user == PLAYER)
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

							switch(choice)
							{
								case 'Q':
									source->piece.type = QUEEN;
									target->piece.type = QUEEN;
									promotion = 'Q';
									choiceMade = true;
									break;
								case 'R':
									source->piece.type = ROOK;
									target->piece.type = ROOK;
									promotion = 'R';
									choiceMade = true;
									break;
								case 'B':
									source->piece.type = BISHOP;
									target->piece.type = BISHOP;
									promotion = 'B';
									choiceMade = true;
									break;
								case 'N':
									source->piece.type = KNIGHT;
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
							source->piece.type = QUEEN;
						
						target->piece.type = QUEEN;
						promotion = 'Q';
					}
				}
			}
		}

		if(real)
		{
			if(source->piece.type == PAWN)
			{
				if(Global::en_passant)
				{
					if(target->x == Global::en_passant->x && target->y == Global::en_passant->y)
					{
						if(source->piece.user == PLAYER)
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
			if(source->piece.type == PAWN)
			{
				if(source->piece.user == PLAYER)
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
		}


		// REGULAR MOVE
		
		// capturing piece
		if(real)
		{
			if(target->piece.type != NONE)
			{
				realTarget = Pieces::getReal(target);
		
				if(real)
					Pieces::makeEmpty(realTarget);

				Pieces::makeEmpty(target);
			}
		}

		Piece source2 = source->piece;
		Piece target2 = target->piece;

		// get target positions
		int targetX = target->x;
		int targetY = target->y;

		source->piece.type = target2.type;
		source->piece.user = target2.user;
		source->piece.color = target2.color;

		target->piece.type = source2.type;
		target->piece.user = source2.user;
		target->piece.color = source2.color;

		// source and target change value
		//source->piece = target2;
		//target->piece = source2;

		if(real)
		{
			// move the piece
			realSource->x = targetX;
			realSource->y = targetY;

			// make the notation
			name = name + nameSource + " to " + nameX + nameY + promotion;

			// read info of the move in console
			readName();

			// change turn
			if(source2.user == PLAYER)
				Global::playerTurn = false;
			else
				Global::playerTurn = true;
		}
	}
}


