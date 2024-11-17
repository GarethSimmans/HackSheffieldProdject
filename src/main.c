#include <assert.h>
#include <raylib.h>
#include "entities.h"

typedef struct {
    Location entities[2048];
    int score;
    int idx;
} State;

State state = {0};

typedef struct {
    Texture2D red; 
    Texture2D blue;
    Texture2D empty;
} Assets;

Assets assets = {0};

static void load_assets(void) {
    Image redImage = LoadImage("assets/red.png");
    ImageResize(&redImage, 128, 128);
    Texture2D red = LoadTextureFromImage(redImage);

    Image blueImage = LoadImage("assets/blue.png");
    ImageResize(&blueImage, 128, 128);
    Texture2D blue = LoadTextureFromImage(blueImage);

    Image emptyImage = LoadImage("assets/empty.png");
    ImageResize(&emptyImage, 128, 128);
    Texture2D empty = LoadTextureFromImage(emptyImage);

    assets.red = red;
    assets.blue = blue;
    assets.empty = empty;
}

static void handle_event(void) {
    const int event = GetKeyPressed();
    switch (event) {
    case KEY_J:
        printf("key_pressed: %c\n", event);
        for (int i = state.idx; i < 2048; i++){
            if (CheckCollisionCircles(
                (Vector2){.x = 250, .y = 570},
                80,
                (Vector2){.x = state.entities[i].x, .y = state.entities[i].y},
                64
            ) && state.entities[i].colour == TRED ) {
                 state.idx = i + 1;
            }
        }
        break;
    case KEY_K:
        printf("key_pressed: %c\n", event);
        for (int i = state.idx; i < 2048; i++){
            if (CheckCollisionCircles(
                (Vector2){.x = 250, .y = 570},
                80,
                (Vector2){.x = state.entities[i].x, .y = state.entities[i].y},
                64
            ) && state.entities[i].colour == TBLUE ) {
                 state.idx = i + 1;
            }
        }
        break;
    }
}

static void init(void) {
    SetTargetFPS(60);
    state.score = 100;

    if (!IsWindowFullscreen()) {
        ToggleFullscreen();
    }

    int width = GetScreenWidth();
    int height = GetScreenHeight();

    InitWindow(width,height,"taiko");

    // load entities to represent song
    int x_start = 1750;

    for (int i = 0; i < 2048; i+= 2){
        x_start += 240;
        state.entities[i] =  (Location){.x = x_start, .y = 500, .colour = 0};
        state.entities[i+1] = (Location){.x = x_start + 120, .y = 500, .colour = 1};
    }

}

static void destroy(void) {
    CloseWindow();
}

static void update(void) {
    for (int i = state.idx; i < 2048; i += 1) {
        if (state.entities[i].x > 0) {
            state.entities[i].x -= 10;
        } else if (state.entities[i].x <= 0 && state.entities[i].colour != EMPTY) {
            state.idx = i + 1;
            state.score -= 1;
        }
    }
}

static void render(void) {
    char text_buffer[8] = {0};
    BeginDrawing();
    ClearBackground(BLACK);
    DrawRectangle(0, 400, 1920, 320, SKYBLUE);
    DrawCircle(250, 570, 80, WHITE);
    sprintf(text_buffer,"%03d", state.score);
    DrawText(text_buffer, 0,0, 100, WHITE);

    for (int i = state.idx; i < 2048; i += 1) {
        switch (state.entities[i].colour) {
        case TRED:
            DrawTextureV(
                assets.red,
                (Vector2){
                    .x = state.entities[i].x,
                    .y = state.entities[i].y,
                },
                WHITE
            );
            break;
        case TBLUE:
            DrawTextureV(
                assets.blue,
                (Vector2){
                    .x = state.entities[i].x,
                    .y = state.entities[i].y,
                },
                WHITE
            );
            break;
        case EMPTY:
            DrawTextureV(
                assets.empty,
                (Vector2){
                    .x = state.entities[i].x,
                    .y = state.entities[i].y,
                },
                WHITE
            );
            break;
        default:
        }
    }
    EndDrawing();
}

int main(int argc, char *argv[]) {
    init();
    load_assets();
    while(!WindowShouldClose()){
        if (state.score == 0){
            float time = GetTime();
            printf("Time Lasted: %f\n", time);
            break;
        }
        handle_event();
        update();
        render();

    }
    destroy();
    return 0;
}
