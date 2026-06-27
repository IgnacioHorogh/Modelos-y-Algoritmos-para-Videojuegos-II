#pragma once

#include "raylib.h"
#include <box2d.h>
#include <vector>
#include "contacto.h"

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




//Conexiones izq y der
extern b2Vec2 ladoizq;
extern b2Vec2 ladoder;


//Inicializacion de voids
void Cajas();
void Joints();
void JugadorCrear();
void JugadorReiniciar();
void Instrucciones(Color textoPrincipal, Color textoSecundario, bool instruccionesb);


//Funciones para no repetir tanto

void CrearAnchor(b2Body*& anchorBody, b2BodyDef& anchorDef,float posX,float posY,b2Body* BodyA,b2Vec2 BodyB);

void CrearJoint(b2Body* bodyA,b2Body* bodyB,b2Vec2 pointA,b2Vec2 pointB,float largo);

b2Body* CrearFigura(float x,float y,float ancho,float alto,float densidad,float friccion,float rebote,b2BodyType tipo);


//Jugador
extern b2Body* Jugador;


//Escalera

extern b2Body* escalon1;
extern b2Body* escalon2;
extern b2Body* escalon3;
extern b2Body* escalon4;


//Obstaculo
extern b2Body* obstaculo;

//Contact - Colisión
extern b2Body* meta;
void CrearMeta();


extern BodyData jugadorData;
extern BodyData metaData;
