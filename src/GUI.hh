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
    	void MouseEvent(SDL_Event& e);
	private:
        static bool onMouseRollOver(SDL_Rect& square);
    	static SDL_Point mousePos;
};


#endif //UKKOSHAKKI_GUI_HH
