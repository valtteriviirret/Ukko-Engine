#ifndef UKKOSHAKKI_GUI_HH
#define UKKOSHAKKI_GUI_HH

#include "SDL2/SDL.h"

class GUI 
{
	public:
        static SDL_Point mousePos(SDL_Event& e);
        static bool onMouseRollOver(SDL_Point& mousePos, SDL_Rect& square);
};


#endif //UKKOSHAKKI_GUI_HH
