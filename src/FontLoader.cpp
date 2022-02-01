#include "FontLoader.h"

namespace FontLoader
{

	TTF_Font *loadFont(std::string path, int fontSize)
	{
		TTF_Font* font = TTF_OpenFont(path.c_str(), fontSize);

		if (!font)
		{
			path = "../" + path;
			font = TTF_OpenFont(path.c_str(), fontSize);
		}

		if (!font)
			std::cout << "Unable to load font from: " << path.c_str() << " " << TTF_GetError() << "\n";

		return font;
	}

}