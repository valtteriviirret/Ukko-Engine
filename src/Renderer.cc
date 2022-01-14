#include "Renderer.hh"

namespace Renderer
{
	// the renderer
	static SDL_Renderer* renderer;

	// setter and getter
	void set(SDL_Renderer* _renderer) { renderer = _renderer; }
	SDL_Renderer* get() { return renderer; }
}

