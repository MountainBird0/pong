// �׸��� : RectangleShape 
// ���� ������ �̵� �Լ�
// �ӵ�, �ð�
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

	//4�� ���
	FloatRect GetGlobalBounds();

	//�����ؼ��Ѿ
	const RectangleShape &GetShape();

	void SetMoveDir(Sides side);

	// �������� �ӵ��� ���� �̵���Ŵ(�ð��ʿ�)
	void Update(float dt);

};

