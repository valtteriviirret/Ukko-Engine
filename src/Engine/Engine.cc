#include "Engine.hh"

namespace Engine
{
	void PlayMove()
	{
		if(Sqr::getSquare(0, 1).piece == ROOK)
			std::cout << "Engine sees squares";
		else
			std::cout << "Engine is still stupid";

		std::cout << (Sqr::getSquare(0, 1).piece);
		std::cout << (Sqr::getSquare(0, 1).piece);
	}
}
