#include <raylib.h>

int main(int argc, char *argv[]) {
	InitWindow(1920,1080,"taiko");
	SetTargetFPS(144);

	while(!WindowShouldClose()){

	BeginDrawing();
		ClearBackground(WHITE);
	EndDrawing();

	}

	CloseWindow();

	return 0;
}
