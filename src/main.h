#ifndef MAIN_H
#define MAIN_H

#include "raylib.h"
#include "utils.h"
#define MAX_TRAIL_LENGTH 2000

typedef enum Class{
    PLANET,
    STAR
}Class;

typedef struct TrailPoint{
    Vector2 position;
    int id;
}TrailPoint;

typedef struct Planet{
    Vector2 position;
    Vector2 velocity;
    long mass;
    double radius;
    Color color;
    Class class;
    int id;
    Node* trailRoot;
    int lifespan;
    int trailLength;
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
void handlePlanetTrails();
void drawPlanetTrails();
void addStar();
//void handleSlider();

#endif // MAIN_H