#include "Text.h"

Text::Text(std::string _text, bool playerTurn)
{
	text = _text;
	font = FontLoader::loadFont("Assets/Fonts/TYPEWR__.TTF", 12);
	if (!playerTurn)
		color = {0, 255, 255};
	else
		color = {255, 255, 0};

	position.x = Screen::getWidth() - 200;
	position.y = Screen::getHeight() - 50;

	setText();
}

Text::~Text()
{
	SDL_DestroyTexture(textTexture);
	TTF_CloseFont(font);
}

void Text::setText()
{
	SDL_Surface* surf = TTF_RenderText_Blended(font, text.c_str(), color);
	textTexture = SDL_CreateTextureFromSurface(Renderer::get(), surf);
	SDL_FreeSurface(surf);
	SDL_QueryTexture(textTexture, nullptr, nullptr, &position.w, &position.h);
}

void Text::render()
{
	SDL_RenderCopy(Renderer::get(), textTexture, nullptr, &position);
}
