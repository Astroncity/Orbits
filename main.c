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
#define G 0.0000000000667408

#define MAX(a, b) ((a)>(b)? (a) : (b))
#define MIN(a, b) ((a)<(b)? (a) : (b))

int runtime = 0;
double deltaTime;

bool f11Down = false;
Vector2 realMouse = {0, 0};
Vector2 mouse = {0, 0};


/**======================
 ** Begin planetary bodies implementation
 *========================**/ 


Planet planets[10];


int main(){
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(SCREENWIDTH, SCREENHEIGHT, "Orbits");
    //SetWindowIcon(LoadImageFromMemory(".png", logoImage, sizeof(logoImage)));
    float scale = MIN((float)GetScreenWidth()/SCREENWIDTH, (float)GetScreenHeight()/SCREENHEIGHT);
    SetTargetFPS(144);
    RenderTexture2D target = LoadRenderTexture(SCREENWIDTH, SCREENHEIGHT);
    SetTextureFilter(target.texture, TEXTURE_FILTER_BILINEAR);  // Scale renderer

    SetExitKey(KEY_F1); 

    //testing planets
    Planet p1 = {(Vector2){200, 200}, (Vector2){10, 0}, 100, 10, RED};
    Planet star = {(Vector2){SCREENWIDTH/2, SCREENHEIGHT/2}, (Vector2){0, 0}, 100000, 100, YELLOW};
    planets[0] = p1;
    planets[1] = star;
    //end testing planets

    // force test

    Vector2 force1 = {4, 224};
    Vector2 force2 = {2, 0};

    Vector2 net = netForce((Vector2[]){force1, force2}, 3);
    printf("Net force: %f, %f\n", net.x, net.y);

    while(!WindowShouldClose()){
        runtime += GetFrameTime();
        deltaTime = GetFrameTime();

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

        handlePlanets();

        BeginTextureMode(target);
        ClearBackground(BLACK);

        drawPlanets();
        EndTextureMode();



        BeginDrawing();
        ClearBackground(BLACK); 
        // Draw render texture to screen, properly scaled
        DrawTexturePro(target.texture, (Rectangle){ 0.0f, 0.0f, (float)target.texture.width, (float)-target.texture.height },
                       (Rectangle){ (GetScreenWidth() - ((float)SCREENWIDTH*scale))*0.5f, (GetScreenHeight() - ((float)SCREENHEIGHT*scale))*0.5f,
                       (float)SCREENWIDTH*scale, (float)SCREENHEIGHT*scale }, (Vector2){ 0, 0 }, 0.0f, WHITE);
        
        DrawFPS(10, 50);
        EndDrawing();

    }
}


void drawPlanets(){
    for(int i = 0; i < 10; i++){
        DrawCircleV(planets[i].position, planets[i].radius, planets[i].color);
    }
}

void handlePlanets(){

    for(int i = 0; i < 10; i++){
        Planet* planet = &planets[i];

        planet -> position.x += planet -> velocity.x * deltaTime; 
        planet -> position.y += planet -> velocity.y * deltaTime;
    }
}

Vector2 forceBetweenBodies(Planet p1, Planet p2){
    double distance = sqrt(pow(p1.position.x - p2.position.x, 2) + pow(p1.position.y - p2.position.y, 2));
    double magnitude = (G * p1.mass * p2.mass) / pow(distance, 2);
    double angle = atan2(p2.position.y - p1.position.y, p2.position.x - p1.position.x);
    Vector2 force = {magnitude * cos(angle), magnitude * sin(angle)};
    return force;
}

Vector2 netForce(Vector2* forces, int length){
    double netForceX = 0.0;
    double netForceY = 0.0;

    for(int i = 0; i < length; i++){
        int dirx;
        int diry;

        if(forces[i].y > 0 && forces[i].y < 180){
            diry = 1;
        }
        else{
            diry = -1;
        }

        if((forces[i].x > 0 && forces[i].x < 90) || (forces[i].x > 270 && forces[i].x < 360)){
            dirx = 1;
        }
        else{
            dirx = -1;
        }


        double magnitude = forces[i].x;
        double angleInDegrees = forces[i].y;

        double angleInRadians = angleInDegrees * (PI / 180);

        double forceX = magnitude * cos(angleInRadians) * dirx;
        double forceY = magnitude * sin(angleInRadians) * diry;

        netForceX += forceX;
        netForceY += forceY;
    }

    double magnitude = sqrt(netForceX * netForceX + netForceY * netForceY);
    double angle = atan2(netForceY, netForceX);

    angle = angle * (180 / PI);

    Vector2 force;
    force.x = magnitude;
    force.y = angle;

    printf("angle: %f\n", angle);
    printf("magnitude: %f\n", magnitude);

    return force;
}