#ifndef UKKOSHAKKI_GUI_HH
#define UKKOSHAKKI_GUI_HH

#include "SDL2/SDL.h"
#include "Square.hh"
#include "SquareManager.hh"
#include "ScreenSize.hh"

class GUI 
{
public:
    static bool onMouseRollOver(SDL_Point& mousePos, SDL_Rect& square);
    static Square* onSelect(SDL_Point& mousePos);
};


#endif //UKKOSHAKKI_GUI_HH
