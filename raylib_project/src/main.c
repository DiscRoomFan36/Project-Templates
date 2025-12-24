
#include "Bested.h"
#undef Clamp // TODO we gotta do something about this...




#ifdef PLATFORM_WEB
    #include <emscripten/emscripten.h>
#endif


#include <raylib.h>
#include <raymath.h>

// NOTE. this is useful, see 'Stylish Sudoku' for this file.
// #include "raylib_helpers.c"



// funny functions, display the color they represent in VSCode.
//
// is the reason I use VSCode to edit colors,
//
// even though this feature is because of CSS, (i presume,)
// its super helpful to have a color picker in your editor.
#define rgba(_r, _g, _b, _a) ( (Color){.r = (_r), .g = (_g), .b = (_b), .a = (_a*255) + 0.5} )
#define rgb(r, g, b) rgba((r), (g), (b), 1)


// just a helper function. should go in raylib_helpers.c
internal void toggle_when_pressed(bool *to_toggle, int key) { *to_toggle ^= IsKeyPressed(key); }


// TODO @Bested.h
#define Proper_Mod(x, y) ({ Typeof(y) _y = (y); (((x) % _y) + _y) % _y; })




#define INITAL_WINDOW_WIDTH     (16*100)
#define INITAL_WINDOW_HEIGHT    ( 9*100)

global_variable s32 window_width  = INITAL_WINDOW_WIDTH;
global_variable s32 window_height = INITAL_WINDOW_HEIGHT;





void do_one_frame(void);


int main(void) {
    // SetConfigFlags(FLAG_WINDOW_RESIZABLE);  // the context contains the window width/height, and stuff updates dynamically.
    // SetTraceLogLevel(LOG_WARNING);          // only show warning or worse logs, the console is being spammed in LOG_INFO mode.
    InitWindow(INITAL_WINDOW_WIDTH, INITAL_WINDOW_HEIGHT, "Raylib Project");

#ifdef PLATFORM_WEB
    emscripten_set_main_loop(do_one_frame, 0, 1);

#else
    // probably could hit 144fps, but maybe later.
    //
    // also only run this when building for desktop.
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        do_one_frame();
    }
#endif

    CloseWindow();
    return 0;
}



void do_one_frame() {
    // clear temporary allocator every frame
    // Arena_Clear(context.scratch);

    BeginDrawing();
    ClearBackground(GRAY);

    { // update window width
        window_width  = GetScreenWidth();
        window_height = GetScreenHeight();
    }

    DrawRectangle(window_width/2 - 100, window_height/2 - 100, 200, 200, RED);

    DrawFPS(10, 10);

    EndDrawing();
}







////////////////////////////////////////////
//             final includes
////////////////////////////////////////////

#define BESTED_IMPLEMENTATION
#include "Bested.h"

