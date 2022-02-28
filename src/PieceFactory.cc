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

	#ifdef __APPLE__
  		system("say \"I’d just like to interject for a moment. What you’re refering to as Linux, is in fact, GNU/Linux, or as I’ve recently taken to calling it, GNU plus Linux. Linux is not an operating system unto itself, but rather another free component of a fully functioning GNU system made useful by the GNU corelibs, shell utilities and vital system components comprising a full OS as defined by POSIX.\"");
	#endif
}

PieceFactory::~PieceFactory()
{
	for(auto& i : p)
		SDL_DestroyTexture(i);
}

SDL_Texture* PieceFactory::getPiece(int n) { return p[n]; }

