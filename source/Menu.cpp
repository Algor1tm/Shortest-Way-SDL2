#include "Menu.h"


void Menu::show(SDL_Renderer* renderer, int WndWidth, int title_height)
{
	Width = WndWidth;
	TitleHeight = title_height;

	initButtons();

	SDL_RenderDrawLine(renderer, 0, TitleHeight - 1, Width, TitleHeight - 1);
	SDL_RenderPresent(renderer);

	for (unsigned i = 0; i < buttons.size(); i++)
	{
		buttons[i].show(renderer, Width, TitleHeight);
	}

}

Menu::Commands Menu::onclick(SDL_Renderer* renderer, Vector2i pos, int SQtype)
{
	for (int i = 0; i < static_cast<int>(buttons.size()); i++)
	{
		if (buttons[i].inside(pos))
		{
			int cmd = buttons[i].onclick(renderer, TitleHeight);
			if (cmd == SQtype)
				return Menu::Commands::DefaultSquare;
			return static_cast<Menu::Commands>(cmd);
		}
	}
	return Menu::Commands::Nothing;
}

void Menu::initButtons()
{
	if (buttons.size() > 0)
		buttons.clear();

	int size = TitleHeight * 25 / 30;
	int intrvl = 2;
	buttons.push_back(Button(Vector2i(intrvl, 2), IncreaseSizeButton, 4));
	buttons.push_back(Button(Vector2i(intrvl + size + intrvl, 2), DecreaseSizeButton, 5));
	buttons.push_back(Button(Vector2i(intrvl + 2 * (size + intrvl), 2), IncreaseIntervalButton, 6));
	buttons.push_back(Button(Vector2i(intrvl + 3 * (size + intrvl), 2), DecreaseIntervalButton, 7));

	// check if buttons of colors are overlapping other buttons that above
	int center = Width / 2;
	if (center - 2 * size - intrvl >= intrvl + 4 * (size + intrvl))
	{
		buttons.push_back(Button(Vector2i(center - 2 * (size + intrvl), 2), StartButton, 1));
		buttons.push_back(Button(Vector2i(center - (size + intrvl), 2), TargetButton, 2));
		buttons.push_back(Button(Vector2i(center, 2), BarrierButton, 3));
		buttons.push_back(Button(Vector2i(center + (size + intrvl), 2), ClearButton, 8));
		buttons.push_back(Button(Vector2i(center + 2 * (size + intrvl), 2), FindPathButton, 9));
	}
	else
	{
		buttons.push_back(Button(Vector2i(intrvl + 4 * (size + intrvl), 2), StartButton, 1));
		buttons.push_back(Button(Vector2i(intrvl + 5 * (size + intrvl), 2), TargetButton, 2));
		buttons.push_back(Button(Vector2i(intrvl + 6 * (size + intrvl), 2), BarrierButton, 3));
		buttons.push_back(Button(Vector2i(intrvl + 7 * (size + intrvl), 2), ClearButton, 8));
		buttons.push_back(Button(Vector2i(intrvl + 8 * (size + intrvl), 2), FindPathButton, 9));
	}
}

void Menu::StartButton(SDL_Renderer* renderer, Vector2i pos, int size)
{
	MyColor::Color cl(0, 193, 71);
	int p = size / 5;

	SDL_Rect square = {pos.x + p, pos.y + p, size - 2 * p, size - 2 * p};
	SDL_SetRenderDrawColor(renderer, cl.r, cl.g, cl.b, 255);
	SDL_RenderFillRect(renderer, &square);
}

void Menu::TargetButton(SDL_Renderer* renderer, Vector2i pos, int size)
{
	MyColor::Color cl(79, 220, 208);
	int p = size / 5;

	SDL_Rect square = { pos.x + p, pos.y + p, size - 2 * p, size - 2 * p };
	SDL_SetRenderDrawColor(renderer, cl.r, cl.g, cl.b, 255);
	SDL_RenderFillRect(renderer, &square);
}

void Menu::BarrierButton(SDL_Renderer* renderer, Vector2i pos, int size)
{
	MyColor::Color cl(23, 21, 4);
	int p = size / 5;

	SDL_Rect square = { pos.x + p, pos.y + p, size - 2 * p, size - 2 * p };
	SDL_SetRenderDrawColor(renderer, cl.r, cl.g, cl.b, 255);
	SDL_RenderFillRect(renderer, &square);
}

void Menu::FindPathButton(SDL_Renderer* renderer, Vector2i pos, int size)
{
	MyColor::Color cl(219, 0, 105);
	int p = size / 5;

	SDL_Rect square = { pos.x + p, pos.y + p, size - 2 * p, size - 2 * p };
	SDL_SetRenderDrawColor(renderer, cl.r, cl.g, cl.b, 255);
	SDL_RenderFillRect(renderer, &square);
}

void Menu::IncreaseSizeButton(SDL_Renderer* renderer, Vector2i pos, int size) 
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawLine(renderer, pos.x + 3, pos.y + size - 3, pos.x + size - 3, pos.y + 3);
	SDL_RenderDrawLine(renderer, pos.x + 3, pos.y + size - 3, pos.x + 5, pos.y + size - 9);
	SDL_RenderDrawLine(renderer, pos.x + 3, pos.y + size - 3, pos.x + 9, pos.y + size - 5);
	SDL_RenderDrawLine(renderer, pos.x + size - 9, pos.y + 5, pos.x + size - 3, pos.y + 3);
	SDL_RenderDrawLine(renderer, pos.x + size - 5, pos.y + 9, pos.x + size - 3, pos.y + 3);
}

void Menu::DecreaseSizeButton(SDL_Renderer* renderer, Vector2i pos, int size)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawLine(renderer, pos.x + 8, pos.y + size - 8, pos.x + size - 8, pos.y + 8);
	SDL_RenderDrawLine(renderer, pos.x + 9, pos.y + size - 9, pos.x + 4, pos.y + size - 7);
	SDL_RenderDrawLine(renderer, pos.x + 9, pos.y + size - 9, pos.x + 7, pos.y + size - 4);
	SDL_RenderDrawLine(renderer, pos.x + size - 7, pos.y + 4, pos.x + size - 9, pos.y + 9);
	SDL_RenderDrawLine(renderer, pos.x + size - 4, pos.y + 7, pos.x + size - 9, pos.y + 9);
}

void Menu::IncreaseIntervalButton(SDL_Renderer* renderer, Vector2i pos, int size)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawLine(renderer, pos.x + 3, pos.y + size / 2, pos.x + size - 3, pos.y + size / 2);
	SDL_RenderDrawLine(renderer, pos.x + 3, pos.y + size / 2, pos.x + 8, pos.y + size / 2 - 3);
	SDL_RenderDrawLine(renderer, pos.x + 3, pos.y + size / 2, pos.x + 8, pos.y + size / 2 + 3);
	SDL_RenderDrawLine(renderer, pos.x + size - 8, pos.y + size / 2 - 3, pos.x + size - 3, pos.y + size / 2);
	SDL_RenderDrawLine(renderer, pos.x + size - 8, pos.y + size / 2 + 3, pos.x + size - 3, pos.y + size / 2);
}

void Menu::DecreaseIntervalButton(SDL_Renderer* renderer, Vector2i pos, int size)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawLine(renderer, pos.x + 6, pos.y + size / 2, pos.x + size - 8, pos.y + size / 2);
	SDL_RenderDrawLine(renderer, pos.x + 8, pos.y + size / 2, pos.x + 2, pos.y + size / 2 - 2);
	SDL_RenderDrawLine(renderer, pos.x + 8, pos.y + size / 2, pos.x + 2, pos.y + size / 2 + 2);
	SDL_RenderDrawLine(renderer, pos.x + size - 10, pos.y + size / 2, pos.x + size - 4, pos.y + size / 2 + 2);
	SDL_RenderDrawLine(renderer, pos.x + size - 10, pos.y + size / 2, pos.x + size - 4, pos.y + size / 2 - 2);
}
