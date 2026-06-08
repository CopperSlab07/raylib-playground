#include <raylib.h>

#define DISPLAY_WIDTH  800
#define DISPLAY_HEIGHT 600
#define PAUSED_BANNER_SIZE 20
#define CUBE_SIZE 1
#define MAX_CUBES 16
#define CUBE_COLOR_DEFAULT GREEN
#define CUBE_COLOR_OUTLINE_DEFAULT RAYWHITE

Vector3 cube_pos[MAX_CUBES] = {0};
int cube_count = 1;
void cube_append(void){
    if(cube_count < MAX_CUBES){
        int index = cube_count;
        cube_count++;
        cube_pos[cube_count] = (Vector3){.x = cube_pos[index].x + 1, .y = cube_pos[index].y, .z = cube_pos[index].z};
    }
    else {
        TraceLog(LOG_INFO, "You fat fuck, there's no more space!");
    }
}
void cube_pop(void){
    if(cube_count > 1){
        cube_pos[cube_count] = (Vector3){.x = 0, .y = 0, .z = 0};
        cube_count--;
    }
    else {
        TraceLog(LOG_INFO, "You scumbag, there's no other cubes!");
    }
}

int main(void){
    Camera3D cam = {
        .position = (Vector3){.x = 1, .y = 1, .z = 1},
        .target = (Vector3){.x = 0, .y = 0, .z = 0},
        .up = (Vector3){.x = 0, .y = 0, .z = 1},
        .fovy = 90,
        .projection = CAMERA_PERSPECTIVE //CAMERA_ORTHOGRAPHIC
    };
    
    InitWindow(DISPLAY_WIDTH, DISPLAY_HEIGHT, "cube");
    SetTargetFPS(60);
    SetExitKey(KEY_Q);
    DisableCursor();
    int paused = 0;
    Image screenshot = {0};
    Texture2D temp = {0};
    while(!WindowShouldClose()){
        if(IsKeyPressed(KEY_R)){
            //spawn = 1;
            cube_append();
        }

        if(IsKeyPressed(KEY_E)){
            cube_pop();
        }
        
        if(!paused) UpdateCamera(&cam, CAMERA_FREE);
        BeginDrawing();

        if (!paused){
            ClearBackground(GetColor(0x181818FF));
            BeginMode3D(cam);
            /*
                DrawCube((Vector3){0, 0, 0}, 1, 1, 1, GREEN);
                DrawCubeWires((Vector3){0, 0, 0}, 1, 1, 1, RAYWHITE);
            */
            for(int i = 0; i < cube_count; i++){
                DrawCube(cube_pos[i], CUBE_SIZE, CUBE_SIZE, CUBE_SIZE, CUBE_COLOR_DEFAULT);
                DrawCubeWires(cube_pos[i], CUBE_SIZE, CUBE_SIZE, CUBE_SIZE, CUBE_COLOR_OUTLINE_DEFAULT);
            }
            
            EndMode3D();
        }
 
        if(IsKeyPressed(KEY_ESCAPE)){
            screenshot = LoadImageFromScreen();
            temp = LoadTextureFromImage(screenshot);
            paused = !paused;
        }

        if(paused){
            DrawTexture(temp, 0, 0, GetColor(0xFFFFFFFF));
            DrawRectangle(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, GetColor(0x08080888));
            DrawText("PAUSED", (DISPLAY_WIDTH - MeasureText("PAUSED", PAUSED_BANNER_SIZE)) / 2, (DISPLAY_HEIGHT - PAUSED_BANNER_SIZE) / 2, PAUSED_BANNER_SIZE, GetColor(0xFFFFFFFF));
        }

        DrawFPS(DISPLAY_WIDTH - 80, DISPLAY_HEIGHT - 20);
        EndDrawing();                
    }
    CloseWindow();
    return 0;
}
