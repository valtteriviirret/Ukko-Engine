#ifndef PIECEFACTORY_HH
#define PIECEFACTORY_HH

#include <SDL2/SDL.h>
#include <string>
#include "Texture.hh"
#include "Board.hh"
#include "Global.hh"
#include <cstdlib>

class PieceFactory
{
	public:
		PieceFactory();
		~PieceFactory();

		// get texture
		SDL_Texture* getPiece(int n);
	private:
		
		// the textures
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

