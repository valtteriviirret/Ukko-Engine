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

	// make the square empty
	void emptySquare(int x, int y)
	{
		Sqr::squareHelper(x, y)->piece = ghost(x, y);
	}

	// make the piece empty
	void emptyPiece(int x, int y)
	{
		for(int i = 0; i < 32; i++)
			if(Pieces::get(i).x == x && Pieces::get(i).y == y)
				Pieces::get(i) = ghost(x, y);
	}

	void castlingFunc(Piece* source, Piece& rook, bool player, bool queenSide)
	{
		int y;
		nameSource = "";

		// make king's square empty
		if(player)
		{
			emptySquare(4, 7);
			y = 7;
		}
		else
		{
			emptySquare(4, 0);
			y = 0;
		}
		
		// make rook's square empty and move pieces
		if(queenSide)
		{
			emptySquare(0, y);
			source->x -= 2;
			rook.x += 3;
			name = "0-0-0";
		}
		else
		{
			emptySquare(7, y);
			source->x += 2;
			rook.x -= 2;
			name = "0-0";
		}

		// update board
		Sqr::squareHelper(rook.x, rook.y)->piece = rook;
		Sqr::squareHelper(source->x, source->y)->piece = *source;
	}

	void readName() { std::cout << name << "\n"; }
	std::string getName() { return name; }

	void execute(Piece* source, Square target)
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

		switch(target.x)
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

		switch(target.y)
		{
			case 0: nameY = '1'; break;
			case 1: nameY = '2'; break;
			case 2: nameY = '3'; break;
			case 3: nameY = '4'; break;
			case 4: nameY = '5'; break;
			case 5: nameY = '6'; break;
			case 6: nameY = '7'; break;
			case 7: nameY = '8'; break;
		}

		// castling
		if(source->type == KING)
		{
			if(source->user == PLAYER)
			{
				Global::playerKingMoved = true;

				// queen side castle
				if(source->x - 2 == target.x)
					castlingFunc(source, Pieces::get(24), true, true);

				// king side castle
				if(source->x + 2 == target.x)
					castlingFunc(source, Pieces::get(25), true, false);
				
			}

			// (if source.user == ENGINE)
			else
			{
				Global::engineKingMoved = true;

				if(source->x - 2 == target.x)
					castlingFunc(source, Pieces::get(8), false, true);

				if(source->x + 2 == target.x)
					castlingFunc(source, Pieces::get(9), false, false);

			}
			
		}
	
		// if rook is moved, has to do with castling
		if(source->type == ROOK)
		{
			if(source->user == PLAYER)
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

		
		// pawn promotion
		if(source->type == PAWN)
		{
			if(source->user == PLAYER)
			{
				// last row
				if(target.y == 0)
				{
					std::cout << "PLAYER PAWN GETS PROMOTED IN " << nameX << nameY << "\n";
					std::cout << "CHOOSE PIECE:\n";
					showPieces

					bool choiceMade = false;
					char choice;

					while(!choiceMade)
					{
						std::cin >> choice;

						Piece* orig = source;

						switch(choice)
						{
							case 'Q':
								source->type = QUEEN;
								promotion = 'Q';
								choiceMade = true;
								break;
							case 'R':
								source->type = ROOK;
								promotion = 'R';
								choiceMade = true;
								break;
							case 'B':
								source->type = BISHOP;
								promotion = 'B';
								choiceMade = true;
								break;
							case 'N':
								source->type = KNIGHT;
								promotion = 'N';
								choiceMade = true;
								break;
							default:
								std::cout << "INCORRECT OPTION\nCHOOSE AGAIN!\n";
								showPieces
								break;
						}

						source->color = orig->color;
						source->alive = true;
						source->user = orig->user;
					}
				}
			}
			// source.user == ENGINE
			else
			{
				// engine always picks queen, at least for now
				if(target.y == 7)
				{
					Piece* orig = source;
					source->type = QUEEN;
					source->color = orig->color;
					source->alive = true;
					source->user = orig->user;
					promotion = 'Q';
				}
			}
		}

		// en passant move
		if(source->type == PAWN)
		{
			if(Global::en_passant)
			{
				if(target.x == Global::en_passant->x && target.y == Global::en_passant->y)
				{
					if(source->user == PLAYER)
					{
						emptyPiece(target.x, (target.y + 1));
						emptySquare(target.x, (target.y + 1));
					}
				
					else
					{
						emptyPiece(target.x, (target.y - 1));
						emptySquare(target.x, (target.y - 1));
					}
				}
			}
		}

		// make en passant squares
		if(source->type == PAWN)
		{
			if(source->user == PLAYER)
			{
				if(source->y == 6 && target.y == 4)
					Global::en_passant = Sqr::squareHelper(source->x, 5);
				else
					Global::en_passant = nullptr;
			}
			else
			{
				if(source->y == 1 && target.y == 3)
					Global::en_passant = Sqr::squareHelper(source->x, 2);
				else
					Global::en_passant = nullptr;
			}
		}
		else
			Global::en_passant = nullptr;


		// REGULAR MOVE
			
		// if piece is captured
		//
		//
		// make source square empty
		emptySquare(source->x, source->y);

		if(target.piece.type != 6)
		{
			// destroy old piece
			emptyPiece(target.x, target.y);
		}



		// change source values to target
		source->x = target.x;
		source->y = target.y;

		// update square
		Sqr::squareHelper(target.x, target.y)->piece = *source;




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


