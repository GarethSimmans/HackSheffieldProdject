#include <assert.h>
#include <raylib.h>
#include "entities.h"

int main(int argc, char *argv[]) {
	
 

	SetTargetFPS(60);

	if (!IsWindowFullscreen()) {
		ToggleFullscreen();
	}
	
	int width = GetScreenWidth();
	int height = GetScreenHeight();

	InitWindow(width,height,"taiko");
	
	Image redImage = LoadImage("assets/red.png");
	ImageResize(&redImage, 128, 128);
	Texture2D red = LoadTextureFromImage(redImage);

	Image blueImage = LoadImage("assets/blue.png");
	ImageResize(&blueImage, 128, 128);
	Texture2D blue = LoadTextureFromImage(blueImage);

	Image emptyImage = LoadImage("assets/empty.png");
	ImageResize(&emptyImage, 128, 128);
	Texture2D empty = LoadTextureFromImage(emptyImage);
	
	Location entities[2048];

	int x_start = 1750;

	for (int i = 0; i < 2048; i++){
		x_start += 150;
		entities[i] =  (Location){.x = x_start, .y = 500, .colour = 1};
	}

	
	while(!WindowShouldClose()){

	BeginDrawing();
		ClearBackground(BLACK);
		DrawRectangle(0, 400, 1920, 320, SKYBLUE);
		DrawCircle(100, 570, 80, WHITE);


		for (int count = 0; count < 2048; count++){
			Texture2D entity_colour;
			if (entities[count].colour == 1){
				entity_colour = red;
			}
			else if (entities[count].colour == 2){
				entity_colour = blue;
			}
			else {
				entity_colour = empty;
			}
			DrawTextureV(entity_colour, (Vector2){.x =entities[count].x, .y =entities[count].y}, WHITE);
			entities[count].x -= 10;
		}
	EndDrawing();
	
	}

	CloseWindow();

	return 0;
}
