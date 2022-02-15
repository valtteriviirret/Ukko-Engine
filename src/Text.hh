#ifndef UKKOSHAKKI_TEXT_H
#define UKKOSHAKKI_TEXT_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Renderer.hh"
#include "ScreenSize.hh"
#include "FontLoader.hh"
#include "Piece.hh"


class Text
{
public:
	Text(std::string _text, bool playerTurn);
	~Text();
	void setText();
	void render();
	SDL_Rect position;
private:
	std::string text;
	TTF_Font* font;
	SDL_Texture* textTexture;
	SDL_Color color;
};


#endif //UKKOSHAKKI_TEXT_H
