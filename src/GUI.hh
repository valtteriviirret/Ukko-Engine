#ifndef UKKOSHAKKI_GUI_HH
#define UKKOSHAKKI_GUI_HH

#include "SDL2/SDL.h"
#include "Renderer.hh"
#include "Square.hh"
#include "SquareManager.hh"

class GUI 
{
	public:
		GUI();
		~GUI();
        static SDL_Point mousePos(SDL_Event& e);
	private:
        static bool onMouseRollOver(SDL_Point& mousePos, SDL_Rect& square);
};


#endif //UKKOSHAKKI_GUI_HH
