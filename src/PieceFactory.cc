#include "PieceFactory.hh"

PieceFactory::PieceFactory() 
{
	for(int i = 0; i < ARRSIZE(p); i++)
	{
		if(Texture::load(c[i]))
			p[i] = Texture::load(c[i]);
		else
			p[i] = Texture::load("../" + c[i]);
	}
}

PieceFactory::~PieceFactory()
{
	for(auto & i : p)
	{
		SDL_DestroyTexture(i);
		i = nullptr;
	}
}

SDL_Texture* PieceFactory::getPiece(int n) { return p[n]; }

