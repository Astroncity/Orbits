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
#define PHYSICSSCALE 1000000000000
#define G 0.0000000000667 * PHYSICSSCALE

#define MAX(a, b) ((a)>(b)? (a) : (b))
#define MIN(a, b) ((a)<(b)? (a) : (b))
#define DEGTORAD(θ) ((θ) * (PI / 180))
#define RADTODEG(θ) ((θ) * (180 / PI))
#define TAU 2 * PI

#define MAX_PLANETS 100

int runtime = 0;
double deltaTime;
double timeScale = 1.0;

bool debug = false;

// Key toggles
bool f11Down = false;
bool spaceDown = false;
bool upArrowDown = false; 
bool downArrowDown = false;

Vector2 realMouse = {0, 0};
Vector2 mouse = {0, 0};



Planet planets[MAX_PLANETS];
int planetCount = 0;
int merges = 0;


int main(){
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(SCREENWIDTH, SCREENHEIGHT, "Orbits");
    float scale = MIN((float)GetScreenWidth()/SCREENWIDTH, (float)GetScreenHeight()/SCREENHEIGHT);
    //SetWindowIcon(LoadImageFromMemory(".png", logoImage, sizeof(logoImage)));
    
    SetTargetFPS(144);
    RenderTexture2D target = LoadRenderTexture(SCREENWIDTH, SCREENHEIGHT);
    SetTextureFilter(target.texture, TEXTURE_FILTER_BILINEAR);  // Scale renderer

    SetExitKey(KEY_F1); 

    initEmptyPlanets();

    // Testing planets
    //Planet p1 = {(Vector2){SCREENWIDTH/2, 900}, (Vector2){450, 0}, 100, 10, BLUE, PLANET, 0};
    Planet star = {(Vector2){SCREENWIDTH/2, SCREENHEIGHT/2}, (Vector2){0, 0}, 5000000, 100, YELLOW, STAR, 0};

    //planets[0] = p1;
    planets[0] = star;
    planetCount = 1;

    // End testing planets


    while(!WindowShouldClose()){
        runtime += 1;
        deltaTime = GetFrameTime() * timeScale;

        // Scaling mouse position
        realMouse = GetMousePosition();
        mouse.x = (realMouse.x - (GetScreenWidth() - (SCREENWIDTH*scale))*0.5f)/scale;
        mouse.y = (realMouse.y - (GetScreenHeight() - (SCREENHEIGHT*scale))*0.5f)/scale;
        mouse = vector2Clamp(mouse, (Vector2){0, 0}, (Vector2){(float)SCREENWIDTH, (float)SCREENHEIGHT});


        if(IsKeyPressed(KEY_SPACE) && !spaceDown){
            addPlanet();
        }
        else{
            spaceDown = false;
        }

        if(IsKeyPressed(KEY_UP) && !upArrowDown){
            timeScale += 0.05;
        }
        else{
            upArrowDown = false;
        }

        if(IsKeyPressed(KEY_DOWN) && !downArrowDown){
            timeScale -= 0.05;
        }

        if(timeScale < 0){
            timeScale = 0;
        }
        else if(timeScale > 5){
            timeScale = 5;
        }
        else{
            downArrowDown = false;
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
            DrawText(TextFormat("Planet Count: %i", planetCount), 10, 10, 20, WHITE);
            DrawText(TextFormat("Time Scale: %f", timeScale), 10, 30, 20, WHITE);
            DrawText(TextFormat("Merges: %i", merges), 10, 70, 20, WHITE);
            
        EndDrawing();

    }

    // Clean up
    UnloadRenderTexture(target);
    CloseWindow();
}


void drawPlanets(){
    for(int i = 0; i < planetCount; i++){

        double lineX = planets[i].velocity.x + planets[i].position.x;
        double lineY = planets[i].velocity.y + planets[i].position.y;        
        
        DrawCircleV(planets[i].position, planets[i].radius, planets[i].color);

        if(debug){DrawLineEx(planets[i].position, (Vector2){lineX, lineY}, 5, BLUE);} // Vector Arrow
    }
}


void handlePlanets(){
    for(int i = 0; i < planetCount; i++){
        calcAppliedForce(i);
    }
    calcPlanetCollisions();
}




void calcAppliedForce(int i){
    Vector2 forces[MAX_PLANETS];
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

    planets[i].velocity.x += (forceX / (planets[i].mass)) * deltaTime;
    planets[i].velocity.y += (forceY / (planets[i].mass)) * deltaTime;

    Planet* planet = &planets[i];

    planet -> position.x += planet -> velocity.x * deltaTime; 
    planet -> position.y += planet -> velocity.y * deltaTime;
}


Vector2 calcForceBetweenBodies(Planet p1, Planet p2){
    double distance = sqrt(pow(p1.position.x - p2.position.x, 2) + pow(p1.position.y - p2.position.y, 2));
    double magnitude = (G * p1.mass * p2.mass) / pow(distance, 2);
    double angle = atan2(p2.position.y - p1.position.y, p2.position.x - p1.position.x);

    angle = clampAngle(angle);
    Vector2 force = {magnitude, RADTODEG(angle)};

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

    angle = clampAngle(angle);
    angle = RADTODEG(angle);

    Vector2 force;
    force.x = magnitude;
    force.y = angle;

    return force;
}


double getStableOribitalVelocity(double mass, double radius){
    return sqrt((G * mass) / radius);
}


double distanceV2(Vector2 v1, Vector2 v2){
    return sqrt(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2));
}


void addPlanet(){
    int mass = GetRandomValue(500, 5000);
    Color color = (Color){GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), 255};

    //Planet p = {(Vector2){SCREENWIDTH / 2, mouse.y}, (Vector2){0, 0}, mass, 10, RED, PLANET, planetCount};
    Planet* p = initPlanet((Vector2){SCREENWIDTH / 2, mouse.y}, (Vector2){0, 0}, mass, color);

    
    Planet* star = &planets[getNearestStar(p -> position)];
    
    double stableVel = getStableOribitalVelocity(star -> mass, distanceV2(star -> position, p -> position));
    p -> velocity.x = stableVel;
}


int getNearestStar(Vector2 pos){
    int nearestStar = 0;
    double nearestDistance = distanceV2(pos, planets[0].position);

    for(int i = 0; i < planetCount; i++){

        if(planets[i].class == STAR){
            double distance = distanceV2(pos, planets[i].position);
            if(distance < nearestDistance){
                nearestDistance = distance;
                nearestStar = i;
            }
        }
    }
    return nearestStar;
}


double clampAngle(double angle){
    while(angle > TAU || angle < 0){

        if(angle > TAU){
            angle -= TAU;
        }
        else if(angle < 0){
            angle += TAU;
        }
    }
    return angle;
}


Planet* initPlanet(Vector2 pos, Vector2 vel, double mass, Color color){
    double radius = mass / 100;

    Planet p = {pos, vel, mass, radius, color, PLANET, planetCount};
    planets[planetCount] = p;
    planetCount++;
    return &planets[planetCount - 1];
}


void destroyPlanet(int id){
    Planet empty = {(Vector2){0, 0}, (Vector2){0, 0}, 0, 0 , (Color){0, 0, 0, 0}, PLANET, -1};

    planets[id] = planets[planetCount - 1];
    planets[id].id = id;

    planets[planetCount - 1] = empty;
    planetCount--;
}

void calcPlanetCollisions(){
    for(int i = 0; i < planetCount; i++){
        for(int j = 0; j < planetCount; j++){
            if(i == j){break;}
            if(planets[i].class == PLANET && planets[j].class == PLANET){
                if(distanceV2(planets[i].position, planets[j].position) < planets[i].radius + planets[j].radius){
                    Color color = (Color){(planets[i].color.r + planets[j].color.r) / 2, (planets[i].color.g + planets[j].color.g) / 2, (planets[i].color.b + planets[j].color.b) / 2, 255};
                    Planet pi = planets[i];
                    Planet pj = planets[j];
;

                    destroyPlanet(planets[i].id);
                    destroyPlanet(planets[j].id);

                    initPlanet(pi.position, pi.velocity, pi.mass + pj.mass, color);
                    merges++;
                }
            }
            else if(planets[i].class == PLANET && planets[j].class == STAR){
                if(distanceV2(planets[i].position, planets[j].position) < planets[i].radius + planets[j].radius){
                    destroyPlanet(planets[i].id);
                }
            }
        }
    }


}


void initEmptyPlanets(){
    for(int i = 0; i < MAX_PLANETS; i++){
        Planet p = {(Vector2){0, 0}, (Vector2){0, 0}, 0, 0 , (Color){0, 0, 0, 0}, PLANET, -1};
        planets[i] = p;
    }
}