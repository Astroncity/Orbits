#ifndef UTILS_H
#define UTILS_H
#include "raylib.h"



typedef struct Node{
    void* data;
    struct Node* next;
}Node;


void removeTrailPoint(Node** root, int val);
void printLinkedList(Node** root);
Node* getLastNode(Node** root);
//Node* addNode(void* data, Node** root);




void clamp(double* value, double max);
Vector2 vector2Clamp(Vector2 v, Vector2 min, Vector2 max);




#endif // UTILS_H