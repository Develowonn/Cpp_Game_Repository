#pragma once // 헤더파일 중복으로 불러오는걸 방지 
#include <raylib.h>

class Dino {
public:
	Dino();  // 생성자
	~Dino(); // 소멸자
	void Draw();
	void Update();
	Rectangle GetRect();
	void DrawHitbox(bool isColliding);
private:
	Texture2D image;
	Vector2	  position;
	int		  speed;
};