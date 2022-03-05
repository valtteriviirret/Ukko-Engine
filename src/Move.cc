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

	Piece* realTarget = nullptr;
	Piece* realSource = nullptr;
	User ogUser;

	void castlingFunc(Piece* rook, bool player, bool queenSide, bool real)
	{
		if(real)
		{
			int y;
			nameSource = "";

			// make the king square empty
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
				realSource->x -= 2;
				rook->x += 3;
				name = "0-0-0";
			}
			else
			{
				Pieces::emptySquare(7, y);
				realSource->x += 2;
				rook->x -= 2;
				name = "0-0";
			}

			// update board
			Sqr::squareHelper(rook->x, rook->y)->piece = *rook;
			Sqr::squareHelper(realSource->x, realSource->y)->piece = *realSource;
		}
		else
		{
			// SquareCopy::getSquares();
		}
	}


	void readName() { std::cout << name << "\n"; }
	std::string getName() { return name; }

	void execute(Square* source, Square* target, bool real)
	{
		if(real)
		{
			// get the user of the function
			ogUser = source->piece.user;

			// get real pieces
			realSource = Pieces::getXY(source->x, source->y);
			realTarget = Pieces::getXY(target->x, target->y);
		}

		// stuff for notation
		if(real)
		{
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

		// castling
		if(real)
		{
			if(source->piece.type == KING)
			{
				if(source->piece.user == PLAYER)
				{
					Global::playerKingMoved = true;

					// queen side castle
					if(source->piece.x - 2 == target->piece.x)
						return castlingFunc(Pieces::getModify(24), true, true, real);

					// king side castle
					if(source->piece.x + 2 == target->piece.x)
						return castlingFunc(Pieces::getModify(25), true, false, real);
					
				}

				// (if source.user == ENGINE)
				else
				{
					Global::engineKingMoved = true;

					if(source->x - 2 == target->x)
						return castlingFunc(Pieces::getModify(8), false, true, real);

					if(source->x + 2 == target->x)
						return castlingFunc(Pieces::getModify(9), false, false, real);
				}
			}
		}


	
		// if rook is moved, has to do with castling
		if(real)
		{
			if(source->piece.type == ROOK)
			{
				if(source->piece.user == PLAYER)
				{
					if(source->x == 0)
						Global::playerQsideRookMoved = true;
					if(source->x == 7)
						Global::playerKsideRookMoved = true;
				}

				else
				{
					if(source->x == 0)
						Global::engineQsideRookMoved = true;
					if(source->x == 7)
						Global::engineKsideRookMoved = true;
				}
			}
		}

	
		// pawn promotion for player
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
									realSource->type = QUEEN;
									promotion = 'Q';
									choiceMade = true;
									break;
								case 'R':
									source->piece.type = ROOK;
									realSource->type = ROOK;
									promotion = 'R';
									choiceMade = true;
									break;
								case 'B':
									source->piece.type = BISHOP;
									realSource->type = BISHOP;
									promotion = 'B';
									choiceMade = true;
									break;
								case 'N':
									source->piece.type = KNIGHT;
									realSource->type = KNIGHT;
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
			}
		}

		// pawn promotion for engine
		if(source->piece.user == ENGINE)
		{
			if(target->y == 7)
			{
				if(real)
				{
					realSource->type = QUEEN;
					promotion = 'Q';
				}
				source->piece.type = QUEEN;
			}
		}

		// en passant only works with real moves
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
		// TODO I think this does not work
		if(target->piece.type != NONE)
		{
			if(real)
				Pieces::makeEmptyPiece(realTarget);
			
			Pieces::makeEmptySquare(target);
		}

		if(real)
		{
			// making movement with real pieces
			realSource->x = target->x;
			realSource->y = target->y;
			realTarget->x = source->x;
			realTarget->y = source->y;
		}

		// source and target change values
		target->piece.color = source->piece.color;
		target->piece.type = source->piece.type;
		target->piece.user = source->piece.user;

		source->piece.color = UNDEFINED;
		source->piece.type = NONE;
		source->piece.user = GHOST;

		if(real)
		{
			// make the notation
			name = name + nameSource + " to " + nameX + nameY + promotion;

			// read info of the move in console
			readName();

			// change turn
			Global::playerTurn = ogUser != PLAYER;
		}
	}
}


