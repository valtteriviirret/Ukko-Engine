//
// Created by valiant on 19.1.2022.
//

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
    	static SDL_Point mousePos;
};


#endif //UKKOSHAKKI_GUI_HH
