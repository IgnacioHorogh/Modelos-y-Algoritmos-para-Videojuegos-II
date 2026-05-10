#ifndef NDEBUG
#include <vld.h>
#include <iostream>
#endif
#include "raylib.h"
#include <box2d.h>
#include <vector>
#include "cajas.h"
#include "game.h"



std::vector<PhysicsBox> boxes;

float impulsoX = 300000.0f;
float impulsoY = -1000000.0f;



void Cajas() {



	//Crear Caja

	boxDef.type = b2_dynamicBody;
	boxDef.position.Set(100.0f, 500.0f);

	boxBody = world.CreateBody(&boxDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(25.0f, 25.0f);

	b2FixtureDef boxFixture;
	boxFixture.shape = &boxShape;
	boxFixture.density = 1.0f;
	boxFixture.friction = 0.4f;
	boxFixture.restitution = 0.2f;

	boxBody->CreateFixture(&boxFixture);

	boxes.push_back({ boxBody, 50.0f, 50.0f, Fade(SKYBLUE, 0.95f) });

}
