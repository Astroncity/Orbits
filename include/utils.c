#include "utils.h"

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
