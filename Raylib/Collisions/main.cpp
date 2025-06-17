#include <raylib.h>
#include "dino.hpp"

int main() {
	// â�� OpenGl Context�� �ʱ�ȭ�Ѵ�.
	// OpenGl Context��? -> OpenGL API�� ����Ͽ� �׷����� �������ϴµ� �ʿ��� ��� ������ ������ ������ �����̴�.
	InitWindow(1200, 800, "Raylib Collisions");

	// ��ǥ FPS �� �����Ѵ�.
	SetTargetFPS(60);

	Dino dino;
	Rectangle obstacle = Rectangle{800, 200, 200, 175};

	// ���� ���α׷��� �ݾƾ� �ϴ��� Ȯ���Ѵ�. (ESC �����ų� �ݱ� �������� ������ ��)
	while (WindowShouldClose() == false) {
		dino.Update();
		
		// �� �簢�� ������ �浹 Ȯ���Ѵ�.
		bool isColliding = CheckCollisionRecs(dino.GetRect(), obstacle);

		// �׸��� ���� ĵ����(�����ӹ���)�� �����Ѵ�.
		BeginDrawing();
		// ������ �����Ѵ�.
		ClearBackground(WHITE);

		// Ȯ��� �Ű������� ����Ͽ� �簢�� ������ �׸��� 
		DrawRectangleLinesEx(obstacle, 5, BLACK);

		dino.Draw();
		dino.DrawHitbox(isColliding);

		/// ĵ���� �׸��� ���� �� ���۱�ü 
		EndDrawing();
	}

	// â�� �ݰ� OpenGL Context�� ��ε��Ѵ�.
	CloseWindow();
}