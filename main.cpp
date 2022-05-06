#include "Program.h"


int main(int argc, char* argv[]) {
	const int FPS = 500;
	const int frameDelay = 1000 / FPS;
	int frameStart;
	int frameTime;

	MyColor::Color* color = new MyColor::Color(254, 164, 44);
	Grid* grid = new Grid();
	Menu* menu = new Menu();

	MyWindow* myWindow = new MyWindow("Shortest Way", grid, menu, 1026, 606, color); // 1026 606
	myWindow->show();

	while (myWindow->running())
	{
		frameStart = SDL_GetTicks();
		myWindow->HandleEvents();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}
	delete myWindow;
	delete menu;
	delete grid;
	delete color;
	return 0;
}