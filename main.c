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
#define G 6.67408

#define MAX(a, b) ((a)>(b)? (a) : (b))
#define MIN(a, b) ((a)<(b)? (a) : (b))
#define DEGTORAD(θ) ((θ) * (PI / 180))
#define RADTODEG(θ) ((θ) * (180 / PI))

int runtime = 0;
double deltaTime;

bool f11Down = false;
Vector2 realMouse = {0, 0};
Vector2 mouse = {0, 0};


/**======================
 ** Begin planetary bodies implementation
 *========================**/ 


Planet planets[10];
int planetCount = 0;


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
    //stable but weird orbit Planet p1 = {(Vector2){500, 1000}, (Vector2){300, 0}, 100, 10, RED};
    Planet p1 = {(Vector2){SCREENWIDTH/2, 900}, (Vector2){450, 0}, 100, 10, RED};

    Planet star = {(Vector2){SCREENWIDTH/2, SCREENHEIGHT/2}, (Vector2){0, 0}, 1000000, 100, YELLOW};
    planets[0] = p1;
    planets[1] = star;

    planetCount = 2;

    int distance = distanceV2(p1.position, star.position);
    planets[0].velocity.x = getStableOribitalVelocity(star.mass, distance);
    printf("velocity: %f\n", planets[0].velocity.x);
    //end testing planets

    // force test

    //Vector2 force1 = {4, 224};
    //Vector2 force2 = {2, 0};

    Vector2 force1 = {59, 315};
    Vector2 force2 = {72.5, 200};



    Vector2 net = calcNetForce((Vector2[]){force1, force2}, 3);
    printf("Net force: %f, %f\n", net.x, net.y);

    while(!WindowShouldClose()){
        runtime += 1;
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
        //printf("Planet %d: %f, %f\n", 0, planets[0].velocity.x, planets[0].velocity.y);
        //system("cls");

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
    for(int i = 0; i < planetCount; i++){
        int lineLength = 100;


        double lineX = planets[i].velocity.x + planets[i].position.x;
        double lineY = planets[i].velocity.y + planets[i].position.y;

        if(runtime % 144 == 0){
            //printf("lineX: %f\n", lineX);
            //printf("lineY: %f\n", lineY);
        }
        
        
        DrawCircleV(planets[i].position, planets[i].radius, planets[i].color);
        DrawLineV(planets[i].position, (Vector2){lineX, lineY}, WHITE);
    }
}

void handlePlanets(){

    for(int i = 0; i < planetCount; i++){
        Vector2 forces[10];
        int forceCount = 0;
        Vector2 netForce;
        for(int j = 0; j < planetCount; j++){
            if(i != j){
                forces[forceCount] = calcForceBetweenBodies(planets[i], planets[j]);
                forceCount++;
            }
        }

        netForce = calcNetForce(forces, forceCount);
        double forceX = cos(DEGTORAD(netForce.y)) * netForce.x;
        double forceY = sin(DEGTORAD(netForce.y)) * netForce.x;


        if((i == 0) && (runtime % 144 == 0)){
            //printf("Forces: %f, %f\n", forceX, forceY);
            //printf("velocity: %f, %f\n", planets[i].velocity.x, planets[i].velocity.y);
            //printf("seconds: %f\n", runtime/144.0);
        }

        planets[i].velocity.x += (forceX / (planets[i].mass)) * deltaTime;
        planets[i].velocity.y += (forceY / (planets[i].mass)) * deltaTime;



        Planet* planet = &planets[i];

        planet -> position.x += planet -> velocity.x * deltaTime; 
        planet -> position.y += planet -> velocity.y * deltaTime;
    }
}

Vector2 calcForceBetweenBodies(Planet p1, Planet p2){
    double distance = sqrt(pow(p1.position.x - p2.position.x, 2) + pow(p1.position.y - p2.position.y, 2));
    double magnitude = (G * p1.mass * p2.mass) / pow(distance, 2);
    double angle = atan2(p2.position.y - p1.position.y, p2.position.x - p1.position.x);

    if(angle < 0){
        angle += 2 * PI;
    }
    else if(angle > 2 * PI){
        angle -= 2 * PI;
    }
    Vector2 force = {magnitude, RADTODEG(angle)};
    //printf("magnitude: %f\n", magnitude);
    //printf("%f", G * p1.mass * p2.mass);
    return force;
}

Vector2 calcNetForce(Vector2 forces[], int length){
    double netForceX = 0.0;
    double netForceY = 0.0;

    for(int i = 0; i < length; i++){

        double magnitude = forces[i].x;
        double angleInDegrees = forces[i].y;

        double angleInRadians = angleInDegrees * (PI / 180);

        double forceX = magnitude * cos(angleInRadians);
        double forceY = magnitude * sin(angleInRadians);

        netForceX += forceX;
        netForceY += forceY;
    }

    double magnitude = sqrt(netForceX * netForceX + netForceY * netForceY);
    double angle = atan2(netForceY, netForceX);
    angle = angle * (180 / PI);

    if(angle > 360){
        angle -= 360;
    }
    else if(angle < 0){
        angle += 360;
    }
    //printf("angle Before: %f\n", angle);

    if(angle > 360){
        angle -= 360;
    }
    else if(angle < 0){
        angle += 360;
    }


    //printf("angle After: %f\n", angle);


    Vector2 force;
    force.x = magnitude;
    force.y = angle;

    //printf("magnitude: %f\n", magnitude);
    //printf("netForceX: %f\n", netForceX);
    //printf("netForceY: %f\n", netForceY);

    return force;
}


double getStableOribitalVelocity(double mass, double radius){
    return sqrt((G * mass) / radius);
}


double distanceV2(Vector2 v1, Vector2 v2){
    return sqrt(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2));
}