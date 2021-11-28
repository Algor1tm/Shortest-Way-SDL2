#include "Program.h"

MyWindow::MyWindow(const char* title, Grid* grd, Menu* Menu, int width, int height, MyColor::Color* bgcolor)
{
	grid = grd;
	menu = Menu;
	Width = width;
	Height = height;
	SquareSize = 40;
	Interval = 1;
	bgColor = bgcolor;
	TypeOfSquare = 0;
	MousePressed = 0;


	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) 
	{
		printf("System Initialized!...\n");

		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_RESIZABLE);
		if(window)
			printf("Window Created!...\n");

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			printf("Renderer Created!...\n");
		if (window && renderer) {
			printf("---------------------------------------------------------------\n");
			printf("Size: % d x % d\n", Width, Height);
		}
		isRunning = 1;
	}
	else {
		window = nullptr;
		renderer = nullptr;
		isRunning = 0;
	}
}


void MyWindow::show(int flag) 
{
	SDL_SetRenderDrawColor(renderer, bgColor->r, bgColor->g, bgColor->b, 255);
	SDL_RenderClear(renderer);

	grid->show(renderer, Width, Height, TitleHeight, SquareSize, Interval, flag);
	menu->show(renderer, Width, TitleHeight);
	SDL_RenderPresent(renderer);
}

void MyWindow::HandleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = 0;
		break;
	case SDL_MOUSEBUTTONDOWN:
	{
		int x = event.button.x;
		int y = event.button.y;
		Vector2i pos(x, y);
		onclick(pos);
		// only in grid can draw with mouse pressed
		if (y > TitleHeight)
			MousePressed = 1;
		break;
	}
	case SDL_MOUSEMOTION:
	{
		// only barrier and default
		if (MousePressed == 1 && (TypeOfSquare == 3 || TypeOfSquare == 0))
		{
			int x = event.button.x;
			int y = event.button.y;
			Vector2i pos(x, y);
			onclick(pos);
			SDL_Delay(1);
		}
		break;
	}
	case SDL_MOUSEBUTTONUP:
		MousePressed = 0;
		break;
	case SDL_WINDOWEVENT:
		if (event.window.event == SDL_WINDOWEVENT_RESIZED)
		{
			int flag = 0;
			int newWidth = event.window.data1;
			int newHeight = event.window.data2;
			if ((Width - Interval) / (SquareSize + Interval) == \
				(newWidth - Interval) / (SquareSize + Interval) && \
				(Height - TitleHeight - Interval) / (Interval + SquareSize) == \
				(newHeight - TitleHeight - Interval) / (Interval + SquareSize))

				flag = 1;
			Width = newWidth;
			Height = newHeight;
			if (!flag)
				printf("Resized: %d x %d\n", Width, Height);
			show(flag);
		}
		break;
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) 
		{
		case SDLK_w: doCommand(Menu::Commands::IncreaseSizeOfSquare); break;
		case SDLK_s: doCommand(Menu::Commands::DecreaseSizeOfSquare); break;
		case SDLK_d: doCommand(Menu::Commands::IncreaseInterval); break;
		case SDLK_a: doCommand(Menu::Commands::DecreaseInterval); break;
		case SDLK_q: doCommand(Menu::Commands::Clear); break;
		case SDLK_SPACE: doCommand(Menu::Commands::FindPath); break;
		case SDLK_e: grid->print(); break;
		}
		break;
	}
}

void MyWindow::onclick(Vector2i pos)
{
	if (pos.y < TitleHeight)
	{ 
		Menu::Commands cmd = menu->onclick(renderer, pos, TypeOfSquare);
		doCommand(cmd);
	}
	else 
	{
		grid->onclick(renderer, pos, TypeOfSquare);
	}
}

void MyWindow::doCommand(Menu::Commands cmd)
{
	printf("Command: ");
	switch (cmd) 
	{
	case (Menu::Commands::Nothing):
		break;
	case (Menu::Commands::DefaultSquare):
		printf("Default Square\n");
		TypeOfSquare = 0;
		break;
	case (Menu::Commands::StartSquare):
		printf("Start Square\n");
		TypeOfSquare = 1;
		break;
	case (Menu::Commands::TargetSquare):
		printf("Target Square\n");
		TypeOfSquare = 2;
		break;
	case (Menu::Commands::BarrierSquare):
		printf("Barrier Square\n");
		TypeOfSquare = 3;
		break;
	case (Menu::Commands::IncreaseSizeOfSquare):
		printf("Increase Size of Square\n");
		SquareSize += 5;
		show();
		SDL_RenderPresent(renderer);
		break;
	case (Menu::Commands::DecreaseSizeOfSquare):
		if (SquareSize < 6)
			break;
		printf("Decrease Size of Square\n");
		SquareSize -= 5;
		show();
		break;
	case(Menu::Commands::IncreaseInterval):
		printf("Increase Interval of Squares\n");
		Interval += 1;
		show();
		break;
	case(Menu::Commands::DecreaseInterval):
		if (Interval < 1)
			break;
		printf("Decrease Interval of Squares\n");
		Interval -= 1;
		show();
		break;
	case (Menu::Commands::Clear):
		printf("Clear\n");
		grid->show(renderer, Width, Height, TitleHeight, SquareSize, Interval);
		SDL_RenderPresent(renderer);
		break;
	case (Menu::Commands::FindPath):
		printf("Find Path\n");
		grid->findPath(renderer);
		break;
	}
}


MyWindow::~MyWindow()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	printf("Program closed!\n");
}
