#include "GameManager.hh"

namespace GameManager
{
	void update()
	{
		Global::playerCanCastleK = true;
		Global::playerCanCastleQ = true;
		Global::playerInCheck = false;

		for(int i = 0; i < 16; i++)
		{
			std::vector v = LegalMove::get(Pieces::get(i));

			for(int j = 0; j < (int)v.size(); j++)
			{
				// see checks
				if(v.at(j).piece.type == 5)
				{
					Global::playerInCheck = true;
					Global::playerCanCastleQ = false;
					Global::playerCanCastleK = false;
				}

				// possibility to castle
				if(!Global::playerKingMoved)
				{
					if(!Global::playerKsideRookMoved)
					{
						if((v.at(j).x == 5 && v.at(j).y == 7) || (v.at(j).x == 6 && v.at(j).y == 7))
							Global::playerCanCastleK = false;
					}
					else
						Global::playerCanCastleK = false;
					
					if(!Global::playerQsideRookMoved)
					{
						if((v.at(j).x == 1 && v.at(j).y == 7) || (v.at(j).x == 2 && v.at(j).y == 7))
							Global::playerCanCastleQ = false;
					}
					else
						Global::playerCanCastleQ = false;
				}
				else
				{
					Global::playerCanCastleQ = false;
					Global::playerCanCastleK = false;
				}
			}
		}

		Global::engineCanCastleK = true;
		Global::engineCanCastleQ = true;
		Global::engineInCheck = false;

		for(int i = 16; i < 32; i++)
		{
			std::vector v = LegalMove::get(Pieces::get(i));
			for(int j = 0; j < (int)v.size(); j++)
			{
				// see checks
				if(v.at(j).piece.type == 5)
				{
					Global::engineInCheck = true;
					Global::engineCanCastleK = false;
					Global::engineCanCastleQ = false;
				}

				// possibility to castle
				if(!Global::engineKingMoved)
				{
					if(!Global::engineKsideRookMoved)
					{
						if((v.at(j).x == 5 && v.at(j).y == 0) || (v.at(j).x == 6 && v.at(j).y == 7))
							Global::engineCanCastleK = false;
					}
					else
						Global::engineCanCastleK = false;

					if(!Global::engineQsideRookMoved)
					{
						if((v.at(j).x == 1  && v.at(j).y == 0) || (v.at(j).x == 2 && v.at(j).y == 0))
							Global::playerCanCastleQ = false;
					}
					else
						Global::engineCanCastleQ = false;

				}
				else
				{
					Global::engineCanCastleK = false;
					Global::engineCanCastleQ = false;
				}

			}
		}
	}

}
