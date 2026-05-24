#ifndef NDEBUG
#include <vld.h>
#include <iostream>
#endif
#include "raylib.h"
#include <box2d.h>
#include <vector>
#include "cajas.h"
#include "game.h"


//INICIADORES IMPORTANTES
std::vector<PhysicsBox> boxes;


//AnchorpOS
b2Vec2 anchorPos;
b2Vec2 anchorPos2;

//Costados de la caja
b2Vec2 ladoizq;
b2Vec2 ladoder;

//Ubicacion de los anchor's
b2BodyDef anchorDef;
b2BodyDef anchorDef2;

//Iniciadores de los anchor's
b2Body* anchorBody;
b2Body* anchorBody2;

//Pendulo
b2Body* pendulo;


//Impulsos para comprobar las fisicas
float impulsoX = 300000.0f;
float impulsoY = -1000000.0f;



void Cajas() {



	//Crear Caja

	for (int i = 0; i < 6; i++) {
		boxDef.type = b2_dynamicBody;
		boxDef.position.Set(100.0f+ 150*i, 150.0f);

		boxBody = world.CreateBody(&boxDef);

		b2PolygonShape boxShape;
		boxShape.SetAsBox(50.0f, 25.0f);

		b2FixtureDef boxFixture;
		boxFixture.shape = &boxShape;
		boxFixture.density = 1.0f;
		boxFixture.friction = 0.4f;
		boxFixture.restitution = 0.2f;

		boxBody->CreateFixture(&boxFixture);

		boxes.push_back({ boxBody, 100.0f, 50.0f, Fade(SKYBLUE, 0.95f) });

	}


	////creando el pendulo
	b2BodyDef penduloDef;
	penduloDef.type = b2_dynamicBody;
	penduloDef.position.Set(400.0f, 300.0f);

	pendulo = world.CreateBody(&penduloDef);

	b2PolygonShape penduloShape;
	penduloShape.SetAsBox(20.0f, 40.0f);

	b2FixtureDef penduloFixture;
	penduloFixture.shape = &penduloShape;
	penduloFixture.density = 1.0f;
	penduloFixture.friction = 0.4f;
	penduloFixture.restitution = 0.2f;

	pendulo->CreateFixture(&penduloFixture);




}





//Funcion de Joint

void CrearJoint(b2Body* bodyA, b2Body* bodyB, b2Vec2 pointA, b2Vec2 pointB, float largo) {

	b2DistanceJointDef jointDef;

	jointDef.Initialize(
		bodyA,
		bodyB,
		pointA,
		pointB
	);

	jointDef.length = largo;

	jointDef.stiffness = 5.0f;
	jointDef.damping = 5.0f;

	world.CreateJoint(&jointDef);

}

//Funcion de anchor

void CrearAnchor(b2Body*& anchorBody, b2BodyDef& anchorDef, float X, float Y, b2Body* BodyA, b2Vec2 BodyB) {

	b2DistanceJointDef anchorJoint;

	anchorDef.type = b2_staticBody;
	anchorDef.position.Set(X, Y);

	anchorBody = world.CreateBody(&anchorDef);

	anchorJoint.Initialize(
		anchorBody,
		BodyA,
		anchorBody->GetWorldCenter(),
		BodyB

	);

	anchorJoint.length = 130.0f;
	anchorJoint.stiffness = 5.0f;
	anchorJoint.damping = 5.0f;

	world.CreateJoint(&anchorJoint);


}


//Creacion de los joints,anchors y pendulo
void Joints() {


	CrearAnchor(anchorBody,anchorDef,20.0f,100.0f,boxes[0].body,boxes[0].body->GetWorldPoint(b2Vec2(-50.0f, 0.0f)));

	CrearAnchor(anchorBody2, anchorDef2, 950.0f, 100.0f, boxes[5].body, boxes[5].body->GetWorldPoint(b2Vec2(50.0f, 0.0f)));


	for (int i = 0; i < boxes.size() - 1; i++)
	{
		CrearJoint(boxes[i].body,boxes[i + 1].body,boxes[i].body->GetWorldPoint(b2Vec2(50.0f, 0.0f)),boxes[i + 1].body->GetWorldPoint(b2Vec2(-50.0f, 0.0f)),30.0f);
	}


	//PENDULO
	b2RevoluteJointDef revoluteDef;

	b2Vec2 puntoeje = boxes[2].body->GetWorldPoint(b2Vec2(0.0f, 25.0f)); revoluteDef.Initialize(boxes[2].body,pendulo, puntoeje);

	world.CreateJoint(&revoluteDef);


}