#include "dino.hpp"

Dino::Dino(){
	// ���Ͽ��� GPU �޸𸮸� �̿��� �ؽ��ĸ� �ε��Ѵ�
	image = LoadTexture("Graphics/dino.png");
	position.x = 100;
	position.y = 100;
	speed = 10;
}

Dino::~Dino() {
	// GPU �޸𸮿��� �ؽ��ĸ� ��ε��Ѵ�.
	UnloadTexture(image);
}

void Dino::Draw() {
	// ��ġ�� Vector2�� ���ǵ� Texture2D�� �׸���.
	DrawTextureV(image, position, WHITE);
}

void Dino::Update() {
	// Ű�� ���ȴ��� Ȯ���Ѵ�.
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
 