#include <assert.h>
#include <raylib.h>
#include "entities.h"


typedef struct {
	Location entities[2048];
	int score;
	
} State;

State state = {0};

static void handle_event(void) {
	int check = 0;
	const int event = GetKeyPressed();
	switch (event) {
	case KEY_J:
		printf("key_pressed: %c\n", event);
		for (int count = 0; count < 2048; count++){
			if (CheckCollisionCircles((Vector2){.x = 250, .y = 570}, 80, (Vector2){.x = state.entities[count].x, .y = state.entities[count].y}, 64)
			&& state.entities[count].colour == 1 ) { 
					state.score++;
					check = 1;
				}
			}
		if (!check){
			state.score--;	
		}
		
		break;			
	case KEY_K:
		printf("key_pressed: %c\n", event);
		for (int count = 0; count < 2048; count++){
			if (CheckCollisionCircles((Vector2){.x = 250, .y = 570}, 80, (Vector2){.x = state.entities[count].x, .y = state.entities[count].y}, 64)
			&& state.entities[count].colour == 2 ) { 
					state.score++;
					check = 1;
				}
			}
		
		if (!check){
			state.score--;	
		}
		break;
	default:
	}
}

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
	
	// load entities to represent song 
	int x_start = 1750;

	for (int i = 0; i < 2048; i+= 2){
		x_start += 500;
		state.entities[i] =  (Location){.x = x_start, .y = 500, .colour = 1};
		state.entities[i+1] =  (Location){.x = x_start + 250, .y = 500, .colour = 2};

	}
		
	//
	
	char text_buffer[8] = {0};
	while(!WindowShouldClose()){
	BeginDrawing();
		handle_event();
		ClearBackground(BLACK);
		DrawRectangle(0, 400, 1920, 320, SKYBLUE);
		DrawCircle(250, 570, 80, WHITE);
		sprintf(text_buffer,"%03d", state.score);
		DrawText(text_buffer, 0,0, 100, WHITE);

		for (int count = 0; count < 2048; count++){
			Texture2D entity_colour;
			if (state.entities[count].colour == 1){
				entity_colour = red;
			}
			else if (state.entities[count].colour == 2){
				entity_colour = blue;
			}
			else {
				entity_colour = empty;
			}
			if (state.entities[count].x > 0){
				DrawTextureV(entity_colour, (Vector2){.x =state.entities[count].x, .y =state.entities[count].y}, WHITE);
				state.entities[count].x -= 10;
			}
		}
	EndDrawing();
	
	}

	CloseWindow();

	return 0;
}
