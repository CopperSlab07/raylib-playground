// From nuklear_raylib repo: https://github.com/RobLoach/raylib-nuklear
// along with full_fledge demo from nuklear (raw version): https://github.com/Immediate-Mode-UI/Nuklear/raw/refs/heads/master/demo/x11/main.c

#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#define RAYLIB_NUKLEAR_IMPLEMENTATION
#include "raylib-nuklear.h"

int main() {
    InitWindow(1208, 720, "raylib-nuklear example");
    SetTargetFPS(60);
    // Create the Nuklear Context
    int fontSize = 20;
    struct nk_context *ctx = InitNuklear(fontSize);

    while (!WindowShouldClose()) {
        // Update the Nuklear context, along with input
        UpdateNuklear(ctx);

        // Nuklear GUI Code
        // https://github.com/Immediate-Mode-UI/Nuklear/wiki/Window
        if (nk_begin(ctx, "Demo", nk_rect(50, 50, 400, 400),
            NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
            NK_WINDOW_CLOSABLE|NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
        {
            enum {EASY, HARD};
            static int op = EASY;
            static int property = 20;

            nk_layout_row_static(ctx, 30, 80, 1);
            if (nk_button_label(ctx, "button"))
                fprintf(stdout, "button pressed\n");
            nk_layout_row_dynamic(ctx, 30, 2);
            if (nk_option_label(ctx, "easy", op == EASY)) op = EASY;
            if (nk_option_label(ctx, "hard", op == HARD)) op = HARD;
            nk_layout_row_dynamic(ctx, 25, 1);
            nk_property_int(ctx, "Compression:", 0, &property, 100, 10, 1);
        }
        nk_end(ctx);
        //if (nk_window_is_hidden(ctx, "Demo")) break;

        // Render
        BeginDrawing();
            ClearBackground(GetColor(0x181818FF));

            // Render the Nuklear GUI
            DrawNuklear(ctx);

        EndDrawing();
    }

    // De-initialize the Nuklear GUI
    UnloadNuklear(ctx);

    CloseWindow();
    return 0;
}
