#pragma once
#include <SFML/Graphics.hpp>

#include "Ball.h"

using namespace sf;

class Brick
{
private:
	Vector2f position;
	RectangleShape shape;
		 
public:
	bool crash = false;
	Brick(float x, float y);

	//4�� ���
	FloatRect GetGlobalBounds();

	//�����ؼ��Ѿ
	const RectangleShape &GetShape();

	bool isInter(Ball &ball)
	{
		return GetGlobalBounds().intersects(ball.GetGlobalBounds());
	}
	void CrashCheck(Ball &ball)
	{
		if (!isInter(ball))
		{
			return;
		}
		crash = true;
	}


	void Update(float dt);
};

