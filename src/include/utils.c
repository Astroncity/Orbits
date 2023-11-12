#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include "../main.h"

void clamp(double* value, double max){
    if(*value > max){
        *value = max;
    }
}

Vector2 vector2Clamp(Vector2 v, Vector2 min, Vector2 max){
    Vector2 result = v;
    if(result.x < min.x){
        result.x = min.x;
    }
    if(result.x > max.x){
        result.x = max.x;
    }
    if(result.y < min.y){
        result.y = min.y;
    }
    if(result.y > max.y){
        result.y = max.y;
    }
    return result;
}


bool compareTrailPoints(void* a, void* b){
    TrailPoint* pointA = (TrailPoint*)a;
    TrailPoint* pointB = (TrailPoint*)b;
    return pointA -> id == pointB -> id;
}

void removeNode(Node** root, bool (*compare)(void*, void*), void* target){
    Node* current = *root;
    Node* next = current -> next;
    Node* prev = NULL;

    Node* targetNode = (Node*)target;

    while(next != NULL){
        if(compare(current -> data, targetNode -> data)){
            if(prev == NULL){
                Node* temp = current;
                *root = next;
                free(temp -> data);
                free(temp);
            }
            else{
                Node* temp = current;
                prev -> next = current -> next;
                free(temp -> data);
                free(temp);
            }
        }
        prev = current;
        current = next;
        next = current -> next;
    }
}

void printLinkedList(Node** root){
    Node* current = *root;
    while(current != NULL){
        TrailPoint* point = current->data;
        printf("%d\n", point -> id);
        current = current -> next;
    }
    printf("\n");
}


Node* getLastNode(Node** root){
    Node* current = *root;
    while(current -> next != NULL){
        current = current -> next;
    }
    return current;
}

void deAllocateLinkedList(Node** root){
    Node* current = *root;
    while(current != NULL){
        Node* next = current -> next;
        free(current -> data);
        free(current); 
        current = next;
    }
}

Node* addNode(void* new, Node** root){
    Node* last = getLastNode(root);
    Node* newNode = (Node*)malloc(sizeof(Node));
    Node* inputNode = (Node*)new;
    newNode -> data = inputNode -> data;
    newNode -> next = NULL;
    last -> next = newNode;
    return newNode;
}