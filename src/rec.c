#include <stdio.h>
#include <raylib.h>
#include "entities.h"

static int idx = 0;
static int start = 1750; 
static int step = 120;
static int y = 500;

static FILE *input;

static void handle_event(void) {
    const int event = GetKeyPressed();
    switch (event) {
    case KEY_J:
        fprintf(input, "state.entities[%d] = (Location) { .x = %d, .y = %d, .colour = %d };\n", idx, start + (step * idx), y, TRED);
        break;
    case KEY_K:
        fprintf(input, "state.entities[%d] = (Location) { .x = %d, .y = %d, .colour = %d };\n", idx, start + (step * idx), y, TBLUE);
        break;
    default:
        fprintf(input, "state.entities[%d] = (Location) { .x = %d, .y = %d, .colour = %d };\n", idx, start + (step * idx), y, EMPTY);
        break;
    }
    idx += 1;
}

int main(void) {
    input = fopen("src/output.h", "w");
    InitAudioDevice();
    Sound song = LoadSound("song.wav");
    InitWindow(640, 480, "recorder");
    SetTargetFPS(3);
    PlaySound(song);
    WaitTime(1.73);
    while (!WindowShouldClose()) {
        printf("delta time: %f\n", GetFrameTime());
        handle_event();
        BeginDrawing();
        ClearBackground(WHITE);
        EndDrawing();
    }

    for (; idx < 2048; idx += 1) {
        fprintf(input, "state.entities[%d] = (Location) { .x = %d, .y = %d, .colour = %d };\n", idx, start + (step * idx), y, EMPTY);
    }
    fclose(input);
    return 0;
}
