#pragma once
#include "Sdl.h"

namespace MyColor {
	struct Color
	{
		int r;
		int g;
		int b;


		Color(int _r, int _g, int _b) { r = _r, g = _g, b = _b; }
		Color(SDL_Color cl) { r = cl.r, g = cl.g, b = cl.b; }
		Color() { r = 0, g = 0, b = 0; }
		int operator==(Color other) { return other.r == r && other.g == g && other.b == b; }
	};

	static const Color WHITE = Color(255, 255, 255);
	static const Color BLACK = Color(0, 0, 0);
}


