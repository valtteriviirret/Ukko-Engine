#ifndef UKKOSHAKKI_FONTLOADER_H
#define UKKOSHAKKI_FONTLOADER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

namespace FontLoader {
	TTF_Font* loadFont(std::string path, int fontSize);
}

#endif //UKKOSHAKKI_FONTLOADER_H
