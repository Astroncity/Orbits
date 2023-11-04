#include "raylib.h"
#include "main.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "include/utils.h"

#define SCREENWIDTH 1920
#define SCREENHEIGHT 1080

#define MAX(a, b) ((a)>(b)? (a) : (b))
#define MIN(a, b) ((a)<(b)? (a) : (b))

int runtime = 0;

bool f11Down = false;
Vector2 realMouse = {0, 0};
Vector2 mouse = {0, 0};



int main(){
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(SCREENWIDTH, SCREENHEIGHT, "Orbits");
    //SetWindowIcon(LoadImageFromMemory(".png", logoImage, sizeof(logoImage)));
    float scale = MIN((float)GetScreenWidth()/SCREENWIDTH, (float)GetScreenHeight()/SCREENHEIGHT);

    RenderTexture2D target = LoadRenderTexture(SCREENWIDTH, SCREENHEIGHT);
    SetTextureFilter(target.texture, TEXTURE_FILTER_BILINEAR);  // Scale renderer

    SetExitKey(KEY_F1); 

    while(!WindowShouldClose()){
        runtime += GetFrameTime();

        realMouse = GetMousePosition();
        mouse.x = (realMouse.x - (GetScreenWidth() - (SCREENWIDTH*scale))*0.5f)/scale;
        mouse.y = (realMouse.y - (GetScreenHeight() - (SCREENHEIGHT*scale))*0.5f)/scale;
        mouse = vector2Clamp(mouse, (Vector2){0, 0}, (Vector2){(float)SCREENWIDTH, (float)SCREENHEIGHT});


        if(IsKeyPressed(KEY_F11) && !f11Down){
            ToggleFullscreen();
        }
        else{
            f11Down = false;
        }

        BeginTextureMode(target);
        DrawCircle(SCREENWIDTH/2, SCREENHEIGHT/2, 100, RED);

        EndTextureMode();



        BeginDrawing();
            ClearBackground(BLACK);     // Clear screen background

            // Draw render texture to screen, properly scaled
            DrawTexturePro(target.texture, (Rectangle){ 0.0f, 0.0f, (float)target.texture.width, (float)-target.texture.height },
                           (Rectangle){ (GetScreenWidth() - ((float)SCREENWIDTH*scale))*0.5f, (GetScreenHeight() - ((float)SCREENHEIGHT*scale))*0.5f,
                           (float)SCREENWIDTH*scale, (float)SCREENHEIGHT*scale }, (Vector2){ 0, 0 }, 0.0f, WHITE);
        EndDrawing();
    }
}


//DrawFPS(10, 50);