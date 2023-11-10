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


void removeTrailPoint(Node** root, int val){
    Node* current = *root;
    Node* next = current -> next;
    Node* prev = NULL;

    while(next != NULL){
        TrailPoint* point = current->data;
        if(point -> id == val){
            if(prev == NULL){
                Node* temp = current;
                *root = next;
                free(temp);
            }
            else{
                Node* temp = current;
                prev -> next = current -> next;
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
}


Node* getLastNode(Node** root){
    Node* current = *root;
    while(current -> next != NULL){
        current = current -> next;
    }
    return current;
}


/*Node* addNode(void* data, Node** root){
    Node* last = getLastNode(root);
    Node* newNode = (Node*)malloc(sizeof(Node));
    last -> next = newNode;
    return &newNode;
}*/