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



//Anchors
extern b2Body* anchorBody;
extern b2Body* anchorBody2;

extern b2Vec2 anchorPos;
extern b2Vec2 anchorPos2;

///Pendulo
extern b2Body* pendulo;


//Conexiones izq y der
extern b2Vec2 ladoizq;
extern b2Vec2 ladoder;


//Inicializacion de voids
void Cajas();
void Joints();


//Funciones para no repetir tanto

void CrearAnchor(b2Body*& anchorBody, b2BodyDef& anchorDef,float posX,float posY,b2Body* BodyA,b2Vec2 BodyB);

void CrearJoint(b2Body* bodyA,b2Body* bodyB,b2Vec2 pointA,b2Vec2 pointB,float largo);






