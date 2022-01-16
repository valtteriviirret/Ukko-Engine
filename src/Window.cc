#include "Window.hh"

Window::Window()
{
	// create fixed size window (could change to fullscreen later), and other settings
	window = SDL_CreateWindow("Chess", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Screen::width, Screen::height, SDL_WINDOW_RESIZABLE);
	
	// if could not create window
	if(!window)
		std::cout << "Could not create window! " << SDL_GetError() << "\n";
	else
	{
		// create the renderer
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if(!renderer)
			std::cout << "Could not create renderer! " << SDL_GetError() << "\n";
		else
		{
			// set the renderer
			Renderer::set(renderer);
		}
	}
}

Window::~Window()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = nullptr;
	renderer = nullptr;
}

