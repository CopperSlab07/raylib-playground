#include <stdint.h>
#include <raylib.h>

#define DISPLAY_WIDTH  1290
#define DISPLAY_HEIGHT 720
#define PAUSED_BANNER_SIZE 20
#define CUBE_SIZE 1
#define MAX_CUBES 16
#define CUBE_COLOR_DEFAULT GREEN
#define CUBE_COLOR_OUTLINE_DEFAULT RAYWHITE

typedef struct Platform {
    Vector3 origin;
    Vector3 size;
    Color color;
} Platform;

typedef struct Platforms {
    Platform platforms[MAX_CUBES];
    size_t count;
} Platforms;

Platform base = {
    .origin = (Vector3){0, 0, -1},
    .size = (Vector3){10, 10, 1},
};
/*
Vector3 cube_pos[MAX_CUBES] = {0};
int cube_count = 0;

void cube_append(void){
    if(cube_count == 0){
        cube_pos[cube_count] = (Vector3){0, 0, 0};
        cube_count++;
    }
    else if(cube_count < MAX_CUBES){
        int index = cube_count - 1;
        cube_pos[cube_count] = (Vector3){.x = cube_pos[index].x + 1, .y = cube_pos[index].y, .z = cube_pos[index].z};
        cube_count++;
    }
    else {
        TraceLog(LOG_INFO, "You fat fuck, there's no more space!");
    }
}

void cube_pop(void){
    if(cube_count > 0){
        cube_pos[cube_count] = (Vector3){.x = 0, .y = 0, .z = 0};
        cube_count--;
    }
    else {
        TraceLog(LOG_INFO, "You scumbag, there's no other cubes!");
    }
}
*/
typedef enum States {
    STATE_DEFAULT = 0,
    STATE_PAUSED = 1
} States;

int main(void){
    base.color = GetColor(0x18FFAAFF);
    int state = STATE_DEFAULT, prev_state = STATE_DEFAULT;
    Image screenshot = {0};
    Texture2D paused_background = {0};

    Camera3D cam = {
        .position = (Vector3){.x = 1, .y = 1, .z = 1},
        .target = (Vector3){.x = 0, .y = 0, .z = 0},
        .up = (Vector3){.x = 0, .y = 0, .z = 1},
        .fovy = 90,
        .projection = CAMERA_PERSPECTIVE,
        //.projection = CAMERA_ORTHOGRAPHIC,
    };
    
    InitWindow(DISPLAY_WIDTH, DISPLAY_HEIGHT, "cube");
    SetTargetFPS(60);
    SetExitKey(KEY_Q);
    DisableCursor();
    while(!WindowShouldClose()){
        //State handling
        if(IsKeyPressed(KEY_ESCAPE)){
            if(state != STATE_PAUSED){
                screenshot = LoadImageFromScreen();
                paused_background = LoadTextureFromImage(screenshot);
                SetWindowIcon(screenshot);
                prev_state = state;
                state = STATE_PAUSED;
            } else {
                state = prev_state;
                prev_state = STATE_PAUSED;
            }
        }
        
        //Input handling (after state handling)
        switch(state){
            case STATE_DEFAULT: {
/*
                if(IsKeyPressed(KEY_R)){
                    cube_append();
                }
            
                if(IsKeyPressed(KEY_E)){
                    cube_pop();
                }
*/
                if(IsKeyPressed(KEY_O)){
                    cam.fovy = 120;
                }

                if(IsKeyPressed(KEY_P)){
                    cam.fovy = 90;
                }

                UpdateCamera(&cam, CAMERA_THIRD_PERSON);
            }
            break;
        }
        
        //Actual drawing
        BeginDrawing();

        switch(state){
            case STATE_DEFAULT: {
                ClearBackground(GetColor(0x181818FF));
                BeginMode3D(cam);
                DrawCube(base.origin, base.size.x, base.size.y, base.size.z, base.color);
                DrawCubeWires(base.origin, base.size.x, base.size.y, base.size.z, RAYWHITE);
                /*
                for(int i = 0; i < cube_count; i++){
                    DrawCube(cube_pos[i], CUBE_SIZE, CUBE_SIZE, CUBE_SIZE, CUBE_COLOR_DEFAULT);
                    DrawCubeWires(cube_pos[i], CUBE_SIZE, CUBE_SIZE, CUBE_SIZE, CUBE_COLOR_OUTLINE_DEFAULT);
                }
                */
                DrawCube(cam.target, CUBE_SIZE, CUBE_SIZE, CUBE_SIZE, RED);
                DrawCubeWires(cam.target, CUBE_SIZE, CUBE_SIZE, CUBE_SIZE, RAYWHITE);
                EndMode3D();
            }
            break;
            
            case STATE_PAUSED: {
                DrawTexture(paused_background, 0, 0, GetColor(0xFFFFFFFF));
                DrawRectangle(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, GetColor(0x08080888));
                DrawText("PAUSED", (DISPLAY_WIDTH - MeasureText("PAUSED", PAUSED_BANNER_SIZE)) / 2, (DISPLAY_HEIGHT - PAUSED_BANNER_SIZE) / 2, PAUSED_BANNER_SIZE, GetColor(0xFFFFFFFF));
            }
        }

        DrawFPS(DISPLAY_WIDTH - 80, DISPLAY_HEIGHT - 20);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
