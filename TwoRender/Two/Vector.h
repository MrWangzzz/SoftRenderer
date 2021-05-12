#pragma once
class Vector2
{
public:
	float x;
	float y;

	Vector2();
	Vector2(const float x, const float y);
	Vector2(Vector2& vec);

private:

};

Vector2::Vector2()
{
}

Vector2::Vector2(const float x1, const float y1) 
{
	x = x1;
	y = y1;
}
Vector2::Vector2(Vector2& vec) 
{
	Vector2() = vec;
}