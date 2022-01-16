#include "Texture.hh"

namespace Texture
{
	SDL_Texture* load(std::string path)
	{
		// the actual texture
		SDL_Texture* texture = nullptr;

		// load image
		SDL_Surface* loadedSurface = IMG_Load(path.c_str());
		if(!loadedSurface)
			std::cout << "Unable to load image: " << path.c_str() << " " <<IMG_GetError() << "\n";
		else
		{
			// color key image
			SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

			// create texture from pixels
			texture = SDL_CreateTextureFromSurface(Renderer::get(), loadedSurface);

			if(!texture)
				std::cout << "Unable to create texture: " << path.c_str() << " " <<  SDL_GetError() << "\n";

			// get rid of loaded surface
			SDL_FreeSurface(loadedSurface);
		}

		return texture;
	}
}

