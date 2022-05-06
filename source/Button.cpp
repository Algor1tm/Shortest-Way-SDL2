#include "Button.h"
#include "MyColor.h"
#include <iostream>

int Button::onclick(SDL_Renderer* renderer, int TitleHeight)
{
	size = TitleHeight * 25 / 30;
	SDL_Rect square = { pos.x, pos.y, size, size };

	SDL_SetRenderDrawColor(renderer, 211, 211, 211, 255);
	SDL_RenderFillRect(renderer, &square);

	drawContent(renderer, pos, size);

	//borders
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &square);

	SDL_RenderPresent(renderer);
	SDL_Delay(100);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &square);

	drawContent(renderer, pos, size);

	//borders
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &square);

	SDL_RenderPresent(renderer);

	return command;
}


void Button::show(SDL_Renderer* renderer, int WndWidth, int TitleHeight)
{	
	//	CHANGE
	size = TitleHeight * 25 / 30;
	SDL_Rect square = { pos.x, pos.y, size, size };

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &square);

	drawContent(renderer, pos, size);

	//borders
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &square);

	/*SDL_RenderPresent(renderer);*/
}

int Button::inside(Vector2i mousePos)
{
	if (mousePos.x >= pos.x && mousePos.x <= pos.x + size)
	{
		if (mousePos.y >= pos.y && mousePos.y <= pos.y + size)
			return 1;
	}
	return 0;
}

Button::Button(Vector2i _pos, void (*func)(SDL_Renderer* , Vector2i, int), int value)
{
	size = 0;
	pos = _pos;
	drawContent = func;
	command = value;
}