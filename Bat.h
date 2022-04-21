// 그리기 : RectangleShape 
// 왼쪽 오른쪽 이동 함수
// 속도, 시간
#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

enum class Sides
{
	LEFT,
	RIGHT,
	NONE,
};

class Bat
{
private:
	Vector2f position;

	RectangleShape shape;

	float speed = 1000.f;
	Sides moveDir = Sides::NONE;

public:
	Bat(float x, float y);

	//4각 계산
	FloatRect GetGlobalBounds();

	//복사해서넘어감
	const RectangleShape &GetShape();

	void SetMoveDir(Sides side);

	// 포지션을 속도에 맞춰 이동시킴(시간필요)
	void Update(float dt);

};

