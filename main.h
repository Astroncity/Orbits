#ifndef MAIN_H
#define MAIN_H

#include "raylib.h"

typedef struct Planet{
    Vector2 position;
    Vector2 velocity;
    float mass;
    float radius;
    Color color;
}Planet;

void drawPlanets();
void handlePlanets();
Vector2 forceBetweenBodies(Planet p1, Planet p2);
Vector2 netForce(Vector2* forces, int length);

#endif // MAIN_H