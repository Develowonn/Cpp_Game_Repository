#include <raylib.h>
#include "dino.hpp"

int main() {
	// 창과 OpenGl Context를 초기화한다.
	// OpenGl Context란? -> OpenGL API를 사용하여 그래픽을 렌더링하는데 필요한 모든 정보를 가지는 데이터 구조이다.
	InitWindow(1200, 800, "Raylib Collisions");

	// 목표 FPS 를 설정한다.
	SetTargetFPS(60);

	Dino dino;
	Rectangle obstacle = Rectangle{800, 200, 200, 175};

	// 응용 프로그램을 닫아야 하는지 확인한다. (ESC 누르거나 닫기 아이콘을 눌렀을 때)
	while (WindowShouldClose() == false) {
		dino.Update();
		
		// 두 사각형 사이의 충돌 확인한다.
		bool isColliding = CheckCollisionRecs(dino.GetRect(), obstacle);

		// 그리기 전에 캔버스(프레임버퍼)를 설정한다.
		BeginDrawing();
		// 배경색을 설정한다.
		ClearBackground(WHITE);

		// 확장된 매개변수를 사용하여 사각형 윤곽선 그리기 
		DrawRectangleLinesEx(obstacle, 5, BLACK);

		dino.Draw();
		dino.DrawHitbox(isColliding);

		/// 캔버스 그리기 종료 및 버퍼교체 
		EndDrawing();
	}

	// 창을 닫고 OpenGL Context를 언로드한다.
	CloseWindow();
}