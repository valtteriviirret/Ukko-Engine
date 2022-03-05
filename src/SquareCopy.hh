#ifndef SQUARECOPY_HH
#define SQUARECOPY_HH

#include <array>
#include "Square.hh"

class SquareCopy
{
	public:
		static void update(std::array <std::array <Square, 8>, 8> squares);
		static std::array <std::array <Square, 8>, 8> get();
	private:
		inline static std::array <std::array <Square, 8>, 8> _squares;
};

#endif
