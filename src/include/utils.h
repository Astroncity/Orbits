#ifndef UTILS_H
#define UTILS_H
#include "raylib.h"



typedef struct Node{
    void* data;
    struct Node* next;
}Node;


void removeNode(Node** root, bool (*compare)(void*, void*), void* target);
void printLinkedList(Node** root);
Node* getLastNode(Node** root);
bool compareTrailPoints(void* a, void* b);
Node* addNode(void* data, Node** root);
void deAllocateLinkedList(Node** root);




void clamp(double* value, double max);
Vector2 vector2Clamp(Vector2 v, Vector2 min, Vector2 max);




#endif // UTILS_H