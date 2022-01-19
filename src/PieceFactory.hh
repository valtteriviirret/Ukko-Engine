#ifndef PIECEFACTORY_HH
#define PIECEFACTORY_HH

#include <SDL2/SDL.h>
#include <string>
#include "Texture.hh"
#include "Board.hh"

#define ARRSIZE(arr) (int)(sizeof(arr)/sizeof(arr[0]))

class PieceFactory
{
	public:
		PieceFactory();
		~PieceFactory();
		SDL_Texture* getPiece(int n);
	private:
		bool _dotdot{};
		SDL_Texture* p[12]{};

		std::string c[12] = 
		{
			"Assets/bb.png",
			"Assets/bh.png",
			"Assets/bk.png",
			"Assets/bp.png",
			"Assets/bq.png",
			"Assets/br.png",
			"Assets/wb.png",
			"Assets/wh.png",
			"Assets/wk.png",
			"Assets/wp.png",
			"Assets/wq.png",
			"Assets/wr.png"
		};
};

#endif

