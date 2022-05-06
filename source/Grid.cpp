#include "Grid.h"
#include <cmath>
#include <iostream>


void Grid::show(SDL_Renderer* renderer, int WndWidth, int WndHeight, int titleHeight, 
					int sq_size, int interval, int flag)
{
	Height = WndHeight;
	Width = WndWidth;
	TitleHeight = titleHeight;
	SquareSize = sq_size;
	Interval = interval;

	int n;
	if (!flag)
	{
		length = 1 + (int)((WndWidth - Interval) / (Interval + SquareSize)) * \
			(int)((WndHeight - TitleHeight - Interval) / (Interval + SquareSize));
		printf("Number of Sqaures: %d\n", length);
		if (AllSquares != 0)
			delete[] AllSquares;
		AllSquares = new int[length];
		for (int i = 0; i < length; i++)
			AllSquares[i] = 0;
		StartSquare = Vector2i(-1, -1);
		NumOfTargets = 0;
		isFounded = 0;
	}
	else 
		n = 1;

	MyColor::Color color = MyColor::WHITE;

	for (int i = 0; WndHeight - TitleHeight - SquareSize - Interval - i * (SquareSize + Interval) > 0; i++)
	{
		for (int j = 0; WndWidth - Interval - SquareSize - j * (SquareSize + Interval) > 0; j++)
		{
			if (flag) 
			{
				switch (AllSquares[n]) {
				case(4):
					color = PathColor;
					break;
				case(3):
					color = BarrierColor;
					break;
				case(2):
					color = TargetColor;
					break;
				case(1):
					color = StartColor;
					break;
				default:
					color = MyColor::WHITE;
				}
				n++;
			}
			drawSquare(renderer, Vector2i(Interval + j * (SquareSize + Interval),
				TitleHeight + Interval + i * (SquareSize + Interval)), &color);
		}
	}
}

int Grid::findPath(SDL_Renderer* renderer)
{
	int NumsqW = (Width - Interval) / (SquareSize + Interval);
	Vector2i sqdraw;
	MyColor::Color white = MyColor::WHITE;
	if (isFounded)
	{
		for (int i = 0; i < length; i++)
		{
			if (AllSquares[i] == 4)
			{
				AllSquares[i] = 0;
				sqdraw = Vector2i(Interval + ((i - 1) % NumsqW) * (SquareSize + Interval),
					Interval + TitleHeight + ((i - 1) / NumsqW) * (SquareSize + Interval));
				drawSquare(renderer, sqdraw, &white);
			}
		}
		SDL_RenderPresent(renderer);
	}
	if (NumOfTargets == 0)
		return -1;
	if (StartSquare.x == -1)
		return -1;
	std::vector<int> founded;
	int temp;
	std::vector<int> searching;
	int Startsq = StartSquare.x + (StartSquare.y - 1) * NumsqW;


	searching.push_back(Startsq);
	searching.push_back(Startsq);
	for (unsigned i = 0; i < searching.size(); i += 2)
	{
		if (AllSquares[searching[i]] != 1)
		{
			sqdraw = Vector2i(Interval + ((searching[i] - 1) % NumsqW) * (SquareSize + Interval),
				Interval + TitleHeight + ((searching[i] - 1) / NumsqW) * (SquareSize + Interval));
			drawSquare(renderer, sqdraw, &PathColor);
			SDL_RenderPresent(renderer);
			if (searching.size() > 250 && searching.size() < 400)
				SDL_Delay(1);
			else if (searching.size() > 250 && searching.size() < 400)
				SDL_Delay(5);
			else if (searching.size() > 80 && searching.size() < 400)
				SDL_Delay(7);
			else if (searching.size() > 20 && searching.size() < 400)
				SDL_Delay(10);
			else if (searching.size() > 0 && searching.size() < 400)
				SDL_Delay(15);
		}

		temp = addtoSearch(&searching, &founded, searching[i], -NumsqW, NumsqW);
		if (temp) {
			founded.push_back(temp);
			founded.push_back(searching[i]);
			if (founded.size() == 2 * NumOfTargets) break;
		}
		temp = addtoSearch(&searching, &founded, searching[i], 1, NumsqW);
		if (temp) {
			founded.push_back(temp);
			founded.push_back(searching[i]);
			if (founded.size() == 2 * NumOfTargets) break;
		}
		temp = addtoSearch(&searching, &founded, searching[i], NumsqW, NumsqW);
		if (temp) {
			founded.push_back(temp);
			founded.push_back(searching[i]);
			if (founded.size() == 2 * NumOfTargets) break;
		}
		temp = addtoSearch(&searching, &founded, searching[i], -1, NumsqW);
		if (temp) {
			founded.push_back(temp);
			founded.push_back(searching[i]);
			if (founded.size() == 2 * NumOfTargets) break;
		}
	}
	SDL_Delay(250);
	for (int i = 0; i < length; i++)
	{
		if (AllSquares[i] == 4)
		{
			AllSquares[i] = 0;
			sqdraw = Vector2i(Interval + ((i - 1) % NumsqW) * (SquareSize + Interval),
				Interval + TitleHeight + ((i - 1) / NumsqW) * (SquareSize + Interval));
			drawSquare(renderer, sqdraw, &white);
		}
	}
	if (founded.size() == 0)
	{
		SDL_Delay(400);
		SDL_RenderPresent(renderer);
		return -1;
	}
	// in reverse order with target and start
	std::vector<int> path;
	for (unsigned j = 0; j < founded.size(); j += 2) 
	{
		path.push_back(founded[j]);
		path.push_back(founded[j + 1]);
		temp = founded[j + 1];
		for (int i = searching.size() - 2; i > -1; i -= 2)
		{
			if (searching[i] == searching[i + 1])
				break;
			else if (searching[i] == temp)
			{
				path.push_back(searching[i + 1]);
				temp = searching[i + 1];
			}
		}

		int delay = 300 / path.size();
		for (unsigned i = path.size() - 1; i > 1; i--)
		{
			AllSquares[path[i - 1]] = 4;
			sqdraw = Vector2i(Interval + ((path[i - 1] - 1) % NumsqW) * (SquareSize + Interval),
				Interval + TitleHeight + ((path[i - 1] - 1) / NumsqW) * (SquareSize + Interval));
			drawSquare(renderer, sqdraw, &PathColor);
			SDL_RenderPresent(renderer);
			SDL_Delay(delay);
		}

		path.clear();
	}
	isFounded = 1;
	return 1;
}
int Grid::addtoSearch(std::vector<int>* arr, std::vector<int>* founded, int sq, int delta, int NumsqW)
{
	if (AllSquares[sq + delta] != 4 && AllSquares[sq + delta] != 3 && \
		AllSquares[sq + delta] != 1 && sq + delta > 0 \
		&& sq + delta < length)
	{
		if (((sq + delta) % NumsqW == 1 && delta == 1) || ((sq + delta) % NumsqW == 0 && delta == -1))
			return 0;
		for (unsigned i = 0; i < founded->size(); i++) {
			if ((*founded)[i] == sq + delta) return 0;
		}
		if (AllSquares[sq + delta] == 2)
			return sq + delta;
		arr->push_back(sq + delta);
		arr->push_back(sq);
		AllSquares[sq + delta] = 4;
		return 0;
	}
	return 0;
}

int Grid::onclick(SDL_Renderer* renderer, Vector2i mousePos, int type)
{
	Vector2i sq = findSquare(mousePos);
	if (sq.x == -1 || sq.y == -1)
		return -1;
	int num = sq.x + (sq.y - 1) * ((Width - Interval) / (Interval + SquareSize));
	Vector2i sqpos(Interval + (sq.x - 1) * (SquareSize + Interval),
		Interval + TitleHeight + (sq.y - 1) * (SquareSize + Interval));

	MyColor::Color cl;
	switch (type) {
	case(3):
		cl = BarrierColor;
		break;
	case(2):
		cl = TargetColor;
		break;
	case(1):
		cl = StartColor;
		break;
	default:
		cl = MyColor::WHITE;
	}
	if (((AllSquares[num] == 0 || AllSquares[num] == 4) && !(cl == MyColor::WHITE)) \
				|| AllSquares[num] != 0 && cl == MyColor::WHITE)
	{
		if (AllSquares[num] == 2)
			NumOfTargets--;
		drawSquare(renderer, sqpos, &cl);
		SDL_RenderPresent(renderer);
		AllSquares[num] = type;

		if (type == 2)
			NumOfTargets++;
		// Exception: StartSquare can be only 1
		if (type == 1)
		{
			if (StartSquare.x != -1)
			{
				sqpos = Vector2i(Interval + (StartSquare.x - 1) * (SquareSize + Interval),
					Interval + TitleHeight + (StartSquare.y - 1) * (SquareSize + Interval));
				cl = MyColor::WHITE;
				drawSquare(renderer, sqpos,	&cl);
				SDL_RenderPresent(renderer);
				num = StartSquare.x + (StartSquare.y - 1) * ((Width - Interval) / (Interval + SquareSize));
				AllSquares[num] = 0;
			}
			StartSquare = Vector2i(sq.x, sq.y);
		}

	}
	return 1;
}

Vector2i Grid::findSquare(Vector2i mousePos)
{
	if (mousePos.y < TitleHeight)
		return Vector2i(-1, -1);

	int x = static_cast<int>(ceil((mousePos.x - Interval) / (Interval + SquareSize))) + 1;
	if (x * (Interval + SquareSize) < mousePos.x || x > (Width - Interval) / (SquareSize + Interval))
		return Vector2i(-1, -1);

	int y = static_cast<int>(ceil((mousePos.y - Interval - TitleHeight) / \
		(Interval + SquareSize))) + 1;
	if (y * (Interval + SquareSize) < mousePos.y - TitleHeight || \
												y > (Height - Interval - TitleHeight) / (SquareSize + Interval))
		return Vector2i(-1, -1);

	return Vector2i(x, y);
}


void Grid::drawSquare(SDL_Renderer* renderer, Vector2i SQpos, MyColor::Color* SQ_color)
{
	SDL_Rect square = { SQpos.x, SQpos.y, SquareSize, SquareSize};
		
	SDL_SetRenderDrawColor(renderer, SQ_color->r, SQ_color->g, SQ_color->b, 255);
	SDL_RenderFillRect(renderer, &square);

	//borders
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &square);
}

void Grid::print()
{
	for (int i = 0; i < length; i++)
		printf("%d: %d, ", i, AllSquares[i]);
	printf("\n");
}


Grid::~Grid()
{
	delete[] AllSquares;
}

Grid::Grid()
{
	Height = 0;
	Width = 0;
	TitleHeight = 0;
	SquareSize = 0;
	Interval = 0;
	StartColor = MyColor::Color(0, 193, 71);
	TargetColor = MyColor::Color(79, 220, 208);
	BarrierColor = MyColor::Color(23, 21, 4);
	PathColor = MyColor::Color(219, 0, 105);
	AllSquares = 0;
	length = 0;
	StartSquare.x = -1; StartSquare.y = -1;
	NumOfTargets = 0;
	isFounded = 0;
}
