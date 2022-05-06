#pragma once
#include "MyColor.h"
#include "Button.h"
#include <vector>


class Menu {
	// normally doesnt change, but can be
	int TitleHeight;
	int Width;
	std::vector<Button> buttons;

public:
	// uses to initialize members
	void show(SDL_Renderer* renderer, int WndWidth, int TitleHeight);
	void initButtons();
	Menu() { TitleHeight = 0, Width = 0; }
	// each button return one of these commands onclick on it
	// MyWindow::doCommand will perform one of it
	enum class Commands
	{
		Nothing = -1, DefaultSquare = 0, StartSquare = 1, TargetSquare = 2, BarrierSquare = 3,
		IncreaseSizeOfSquare = 4, DecreaseSizeOfSquare = 5, IncreaseInterval = 6, DecreaseInterval = 7,
		Clear = 8, FindPath = 9
	};
	Commands onclick(SDL_Renderer* renderer, Vector2i pos, int SQtype);
private:
	static void StartButton(SDL_Renderer* renderer, Vector2i pos, int size);
	static void TargetButton(SDL_Renderer* renderer, Vector2i pos, int size);
	static void BarrierButton(SDL_Renderer* renderer, Vector2i pos, int size);
	static void ClearButton(SDL_Renderer* renderer, Vector2i pos, int size) { ; }
	static void IncreaseSizeButton(SDL_Renderer* renderer, Vector2i pos, int size);
	static void DecreaseSizeButton(SDL_Renderer* renderer, Vector2i pos, int size);
	static void IncreaseIntervalButton(SDL_Renderer* renderer, Vector2i pos, int size);
	static void DecreaseIntervalButton(SDL_Renderer* renderer, Vector2i pos, int size);
	static void FindPathButton(SDL_Renderer* renderer, Vector2i pos, int size);
};
