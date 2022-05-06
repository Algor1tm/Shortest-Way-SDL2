#pragma once
#include "SDL.h"
#include "Vector2i.h"

// Only square button that have position and size
// drawContent: function that shows content of the button
// command: value that button return onclick(one of the value of Menu::Commands)
class Button {
	Vector2i pos;
	int size;
	void (*drawContent)(SDL_Renderer* , Vector2i , int);
	int command;
	
public:
	// _pos: position of the button
	// func: function that shows content of the button
	// value: value that button return onclick(most likely it is one of the value of Menu::Commands)
	Button(Vector2i _pos, void (*func)(SDL_Renderer* , Vector2i, int), int value);
	void show(SDL_Renderer* renderer, int WndWidth, int menuHeight);
	// makes animation of click
	// return: command
	int onclick(SDL_Renderer* renderer, int TitleHeight);
	int inside(Vector2i mousepos);
};
