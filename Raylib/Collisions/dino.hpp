#pragma once // ������� �ߺ����� �ҷ����°� ���� 
#include <raylib.h>

class Dino {
public:
	Dino();  // ������
	~Dino(); // �Ҹ���
	void Draw();
	void Update();
	Rectangle GetRect();
	void DrawHitbox(bool isColliding);
private:
	Texture2D image;
	Vector2	  position;
	int		  speed;
};