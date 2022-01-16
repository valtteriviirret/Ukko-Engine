#include "ScreenSize.hh"

namespace Screen
{
	// the screensizes
	int width;
	int height;

	void setWidth(int w) { width = w; }
	void setHeight(int h) { height = h; }

	int getWidth() { return width; }
	int getHeight() { return height; }
}
