#ifndef MAIN_H
#define MAIN_H

#include "raylib.h"

typedef struct Planet{
    Vector2 position;
    Vector2 velocity;
    double mass;
    double radius;
    Color color;
}Planet;

void drawPlanets();
void handlePlanets();
Vector2 calcForceBetweenBodies(Planet p1, Planet p2);
Vector2 calcNetForce(Vector2 forces[], int length);
double getStableOribitalVelocity(double mass, double radius);
double distanceV2(Vector2 v1, Vector2 v2);

#endif // MAIN_H