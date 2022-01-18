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
	for(int i = 0; i < ARRSIZE(p); i++)
	{
		SDL_DestroyTexture(p[i]);
		p[i] = nullptr;
	}
}

SDL_Texture* PieceFactory::getPiece(int n) { return p[n]; }

