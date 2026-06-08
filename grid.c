#include <stdio.h>
#include <raylib.h>

#define DISPLAY_WIDTH  800
#define DISPLAY_HEIGHT 600

#define TILE_WIDTH  100
#define TILE_HEIGHT 100

#define MAP_WIDTH  7
#define MAP_HEIGHT 5

//#define MAX_TILES MAP_WIDTH * MAP_HEIGHT

float cursor_outline_thickness = 5.0f;

typedef struct Tile {
    Rectangle hitbox;
    //Vector2 pos;
    Color color;
    //struct Tile *next;
    //struct Tile *prev;
} Tile;

//Tile map[MAP_WIDTH * MAP_HEIGHT] = {0};

typedef struct Tiles {
    //Vector2 anchor;
    Tile data[MAP_HEIGHT][MAP_WIDTH];
} Tiles;

Tiles tilemap = {0};

void tilemap_append(int map_x, int map_y, Color color){
    if(map_x <= MAP_WIDTH && map_y <= MAP_HEIGHT && map_x >= 0 && map_y >= 0){
        tilemap.data[map_y][map_x].color         = color;
        tilemap.data[map_y][map_x].hitbox.x      = /*tilemap.anchor.x*/ map_x * (TILE_WIDTH + cursor_outline_thickness);
        tilemap.data[map_y][map_x].hitbox.y      = /*tilemap.anchor.y*/ map_y * (TILE_HEIGHT + cursor_outline_thickness);
        tilemap.data[map_y][map_x].hitbox.width  = TILE_WIDTH;
        tilemap.data[map_y][map_x].hitbox.height = TILE_HEIGHT;
    }
    else {
        printf("Out of the fucking bounds!\n");
    }
};

void tilemap_append_ex(int map_x, int map_y, int width, int height, Color color){
    if(map_x <= MAP_WIDTH && map_y <= MAP_HEIGHT && map_x >= 0 && map_y >= 0){
        tilemap.data[map_y][map_x].color         = color;
        tilemap.data[map_y][map_x].hitbox.x      = map_x * (TILE_WIDTH + cursor_outline_thickness);
        tilemap.data[map_y][map_x].hitbox.y      = map_y * (TILE_HEIGHT + cursor_outline_thickness);
        tilemap.data[map_y][map_x].hitbox.width  = width;
        tilemap.data[map_y][map_x].hitbox.height = height;
    }
    else {
        printf("Out of the fucking bounds!\n");
    }
};

void tilemap_init(Vector2 anchor){
    //tilemap.anchor = anchor;
    for(int y = 0; y < MAP_HEIGHT; y++){
        for(int x = 0; x < MAP_WIDTH; x++){   
            tilemap_append(x, y, BLANK);
        }
    }
}

int main(void){
    Rectangle cursor = {
        .x = 0,
        .y = 0,
        .width =  TILE_WIDTH  + cursor_outline_thickness * 2,
        .height = TILE_HEIGHT + cursor_outline_thickness * 2
    };
    Vector2 cursor_map_pos = {0};

    //tilemap_init((Vector2){.x = (DISPLAY_WIDTH) - (MAP_WIDTH / 2) * (TILE_WIDTH * cursor_outline_thickness), .y = (DISPLAY_HEIGHT) - (MAP_HEIGHT / 2) * (TILE_HEIGHT * cursor_outline_thickness)});
    tilemap_init((Vector2){.x = 0, .y = 0});
    
    tilemap_append(0, 0, WHITE);
    tilemap_append_ex(1, 1, 100, 50, RED);
    tilemap_append_ex(1, 2, 50, 50, GREEN);
    tilemap_append_ex(1, 3, 25, 100, BLUE);
    tilemap_append_ex(2, 1, 75, 12, YELLOW);
    tilemap_append_ex(2, 2, 35, 65, MAGENTA);
    tilemap_append_ex(2, 3, 18, 72, SKYBLUE);
    tilemap_append(3, 4, BLACK);
    tilemap_append(5, 5, GetColor(0xFF1848FF));
    
    InitWindow(DISPLAY_WIDTH, DISPLAY_HEIGHT, "title");
    SetTargetFPS(60);
    while(!WindowShouldClose()){
        //TODO: bounds checking
        if(IsKeyPressed(KEY_A) && cursor_map_pos.x > 0)                cursor_map_pos.x --;
        if(IsKeyPressed(KEY_D) && cursor_map_pos.x < (MAP_WIDTH - 1))  cursor_map_pos.x ++;
        if(IsKeyPressed(KEY_W) && cursor_map_pos.y > 0)                cursor_map_pos.y --;
        if(IsKeyPressed(KEY_S) && cursor_map_pos.y < (MAP_HEIGHT - 1)) cursor_map_pos.y ++;

        cursor.x = tilemap.data[(int)cursor_map_pos.y][(int)cursor_map_pos.x].hitbox.x - cursor_outline_thickness;
        cursor.y = tilemap.data[(int)cursor_map_pos.y][(int)cursor_map_pos.x].hitbox.y - cursor_outline_thickness;
        cursor.width = tilemap.data[(int)cursor_map_pos.y][(int)cursor_map_pos.x].hitbox.width + cursor_outline_thickness * 2;
        cursor.height = tilemap.data[(int)cursor_map_pos.y][(int)cursor_map_pos.x].hitbox.height + cursor_outline_thickness * 2;
        
        BeginDrawing();
        ClearBackground(GetColor(0x181818FF));
        //DrawRectangleRec(test_object, GREEN);
        for(int i = 0; i < MAP_HEIGHT; i++){
            for(int j = 0; j < MAP_HEIGHT; j++){
                if(ColorToInt(tilemap.data[i][j].color) != 0) DrawRectangleRec(tilemap.data[i][j].hitbox, tilemap.data[i][j].color);
            }
        }
        if(ColorToInt(tilemap.data[(int)cursor_map_pos.y][(int)cursor_map_pos.x].color) == ColorToInt(RED)){
            DrawRectangleLinesEx(cursor, cursor_outline_thickness, GetColor(0x18FF18FF));
        }
        else {
            DrawRectangleLinesEx(cursor, cursor_outline_thickness, GetColor(0xFF1818FF));
        }
        DrawFPS(DISPLAY_WIDTH - 80, DISPLAY_HEIGHT - 20);
        DrawText(TextFormat("%f, %f", cursor_map_pos.x, cursor_map_pos.y), 0, DISPLAY_HEIGHT - 20, 20, RED);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
