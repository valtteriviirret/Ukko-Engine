#ifndef UKKOSHAKKI_GUI_HH
#define UKKOSHAKKI_GUI_HH

#include "SDL2/SDL.h"
#include "Square.hh"
#include "SquareManager.hh"
#include "ScreenSize.hh"
#include "PieceRenderer.hh"

typedef struct Button {
    SDL_Rect rect;
    int textureID;
    int returnValue;
} Button;

class GUI
{
public:
	static bool onMouseRollOver(SDL_Point &mousePos, SDL_Rect &square);
	static Square *onSelect(SDL_Point &mousePos);
    static void renderPromotionUI(SDL_Renderer* ren);
};


#endif //UKKOSHAKKI_GUI_HH
