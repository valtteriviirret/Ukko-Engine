//
// Created by valiant on 19.1.2022.
//

#ifndef UKKOSHAKKI_GUI_HH
#define UKKOSHAKKI_GUI_HH

#include "SDL2/SDL.h"
#include "Renderer.hh"
#include "Square.hh"

class GUI {
private:
    static SDL_Point mousePos;
public:
    static bool onMouseRollOver(SDL_Rect& square);
};


#endif //UKKOSHAKKI_GUI_HH
