#pragma once
#include "SDL.h"
#include "Vector2i.h"
#include "MyColor.h"
#include <vector>


// (1, 1)  (2, 1) ...  *(grid coordinates)
// (1, 2)  (2, 2)
// ...
class Grid {
	int SquareSize;
	int Interval;
	int Height;
	int Width;
	// normally doesnt change, but can be
	int TitleHeight;
	MyColor::Color StartColor;
	MyColor::Color TargetColor;
	MyColor::Color BarrierColor;
	MyColor::Color PathColor;
	// Array of types of squares
	// 0 - default, 1 - start, 2 - target, 3 - barrier, 4 - path
	int* AllSquares;
	// number of squares
	int length;
	// coordinates of start square(grid coordinates)
	Vector2i StartSquare;
	int NumOfTargets;
	int isFounded;

public:
	Grid();
	~Grid();
	// uses to initialize members
	// flag: 1 if number of squares has not changed - redraw colors
	void show(SDL_Renderer* renderer, int WndWidth, int WndHeight, int TitleHeight, 
					int sq_size, int interval, int flag = 0);

	//	SQpos - left upper corner
	void drawSquare(SDL_Renderer* renderer, Vector2i SQpos, MyColor::Color* cl);


	// return square in grid coordinates 
	Vector2i findSquare(Vector2i coords);

	// coords: left upper corner of square
	int onclick(SDL_Renderer* renderer, Vector2i coords, int type);
	void print();

	int findPath(SDL_Renderer* renderer);
private:
	// auxiliary function for findPath()
	int addtoSearch(std::vector<int>* arr, std::vector<int>* founded, int sq, int delta, int NumsqW);
};
