#include "PieceFactory.hh"

PieceFactory::PieceFactory(bool dotdot) : _dotdot(dotdot)
{
	if(!_dotdot)
		for(int i = 0; i < ARRSIZE(p); i++)
			p[i] = Texture::load(c[i]);
	else
		for(int i = 0; i < ARRSIZE(p); i++)
			p[i] = Texture::load("../" + c[i]);
}


PieceFactory::~PieceFactory()
{
	for(int i = 0; i < (int)sizeof(p); i++)
	{
		SDL_DestroyTexture(p[i]);
		p[i] = nullptr;
	}
}

SDL_Texture* PieceFactory::getPiece(int n) { return p[n]; }
