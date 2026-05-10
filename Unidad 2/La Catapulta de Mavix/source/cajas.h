#pragma once

#include "raylib.h"
#include <box2d.h>
#include <vector>

extern struct PhysicsBox
{
    b2Body* body;
    float width;
    float height;
    Color color;
};

extern std::vector<PhysicsBox> boxes;

extern float impulsoX;
extern float impulsoY;

void Cajas();

