#ifndef MAIN_H
#define MAIN_H

#include "raylib.h"


typedef enum Class{
    PLANET,
    STAR
}Class;
typedef struct Planet{
    Vector2 position;
    Vector2 velocity;
    int mass;
    double radius;
    Color color;
    Class class;
    int id;
}Planet;

void drawPlanets();
void handlePlanets();
Vector2 calcForceBetweenBodies(Planet p1, Planet p2);
Vector2 calcNetForce(Vector2 forces[], int length);
double getStableOribitalVelocity(double mass, double radius);
double distanceV2(Vector2 v1, Vector2 v2);
void addPlanet();
int getNearestStar(Vector2 pos);
double clampAngle(double angle);
Planet* initPlanet(Vector2 pos, Vector2 vel, double mass, Color color);
void calcAppliedForce(int i);
void destroyPlanet(int id);
void initEmptyPlanets();
void calcPlanetCollisions();
void drawPlanetSettings();
void handleSlider();

#endif // MAIN_H