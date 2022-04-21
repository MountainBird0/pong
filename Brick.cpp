#include "Brick.h"

Brick::Brick(float x, float y) : position(x + 200 , y + 100)
{
	shape.setSize(Vector2f(100, 20));
	shape.setPosition(position);
	shape.setFillColor(Color::Blue);
}

FloatRect Brick::GetGlobalBounds()
{
	return shape.getGlobalBounds();
}

const RectangleShape &Brick::GetShape()
{
	return shape;
}

void Brick::Update(float dt)
{
	shape.setPosition(position);
}
