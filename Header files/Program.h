#pragma once
#include "Grid.h"
#include "Menu.h"


class MyWindow {
	int isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
	Grid* grid;
	Menu* menu;
	int Height;
	int Width;
	// normally doesnt change, but can be
	int TitleHeight = 30;
	int SquareSize;
	int Interval;
	MyColor::Color* bgColor;
	// 0 - Default, 1 - Start, 2 - Target, 3 - Barrier
	int TypeOfSquare;
	// 1 while mouse is pressed, else - 0
	int MousePressed;

public:
	MyWindow(const char* title, Grid* grd, Menu* menu, int width, int height, MyColor::Color* bgcolor);
	~MyWindow();
	void HandleEvents();
	// redraw all window(call grid.show() and menu.show())
	void show(int flag = 0);
	// handle event mouse click
	void onclick(Vector2i pos);
	void doCommand(Menu::Commands cmd);
	int running() { return isRunning; }
};