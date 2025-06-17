#include "dino.hpp"

Dino::Dino(){
	// 파일에서 GPU 메모리를 이용해 텍스쳐를 로드한다
	image = LoadTexture("Graphics/dino.png");
	position.x = 100;
	position.y = 100;
	speed = 10;
}

Dino::~Dino() {
	// GPU 메모리에서 텍스쳐를 언로드한다.
	UnloadTexture(image);
}

void Dino::Draw() {
	// 위치가 Vector2로 정의된 Texture2D를 그린다.
	DrawTextureV(image, position, WHITE);
}

void Dino::Update() {
	// 키가 눌렸는지 확인한다.
	if (IsKeyDown(KEY_RIGHT)) position.x += speed;
	if (IsKeyDown(KEY_LEFT)) position.x -= speed;
	if (IsKeyDown(KEY_UP)) position.y -= speed;
	if (IsKeyDown(KEY_DOWN)) position.y += speed;
}

Rectangle Dino::GetRect()
{
	return Rectangle{ position.x, position.y, float(image.width), float(image.height)};
}

void Dino::DrawHitbox(bool isColliding) {
	Color outlineColor = isColliding ? RED : BLACK;
	DrawRectangleLinesEx(GetRect(), 3, outlineColor);
}
 