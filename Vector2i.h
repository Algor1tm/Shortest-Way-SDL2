#pragma once

// uses as plane coordinates
// x: x coordinate
// y: y coordinate
struct Vector2i{
	int x;
	int y;

	Vector2i(int _x, int _y) { x = _x, y = _y; }
	Vector2i() { x = NULL, y = NULL; }
	Vector2i operator+(Vector2i other) { return Vector2i(x + other.x, y + other.y); }
	Vector2i operator-(Vector2i other) { return Vector2i(x - other.x, y - other.y); }
	Vector2i operator*(int k) { return Vector2i(x * k, y * k); }
	Vector2i operator/(int k) { return Vector2i(x / k, y / k); }
	int operator==(Vector2i other) { return other.x == x && other.y == y; }
};
