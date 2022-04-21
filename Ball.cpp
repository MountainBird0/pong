#include "Ball.h"

Ball::Ball(float x, float y) : originalPosition(x, y), position(x, y)
{
	dir.x = 1.f;
	dir.y = 1.f;

	float length = sqrt(dir.x * dir.x + dir.y * dir.y);
	dir.x /= length; // 길이가 1인 단위벡터
	dir.y /= length;

	shape.setSize(Vector2f(10, 10));
	shape.setPosition(position);
	shape.setFillColor(Color::White);
}

FloatRect Ball::GetGlobalBounds()
{
	return shape.getGlobalBounds();
}

const RectangleShape &Ball::GetShape()
{
	return shape;
}

void Ball::reboundSides()
{
	dir.x *= -1.f;
}

void Ball::reboundBatOrTop()
{
	dir.y *= -1.f ;
}

void Ball::reboundBottom()
{
	position = originalPosition;
}


// 포지션 갱신
void Ball::Update(float dt)
{
	position += dir * dt * speed;
	shape.setPosition(position);
}
