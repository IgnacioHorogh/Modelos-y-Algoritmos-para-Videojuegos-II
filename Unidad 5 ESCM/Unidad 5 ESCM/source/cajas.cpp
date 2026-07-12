#ifndef NDEBUG
#include <vld.h>
#include <iostream>
#endif
#include "raylib.h"
#include <box2d.h>
#include <vector>
#include "cajas.h"
#include "game.h"
#include "contacto.h"


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

//Jugador
b2Body* Jugador;
b2BodyDef jugadorDef;

//Escaleras
b2Body* escalon1;
b2Body* escalon2;
b2Body* escalon3;
b2Body* escalon4;


//Obstaculo
b2Body* obstaculo;
b2BodyDef obstaculoDef;

//Contact - Colisión
b2Body* meta;

BodyData jugadorData;
BodyData metaData;



//Funcion de crear recuadros
b2Body* CrearFigura(float x,float y,float ancho,float alto,	float densidad,	float friccion,	float rebote,b2BodyType tipo)

{
	b2BodyDef bodyDef;
	bodyDef.type = tipo;
	bodyDef.position.Set(x, y);
	b2Body* body = world.CreateBody(&bodyDef);
	b2PolygonShape shape;
	shape.SetAsBox(ancho, alto);
	b2FixtureDef fixture;
	fixture.shape = &shape;
	fixture.density = densidad;
	fixture.friction = friccion;
	fixture.restitution = rebote;
	body->CreateFixture(&fixture);
	return body;
}






////Jugador

void JugadorCrear(){Jugador = CrearFigura(50.0f,450.0f,15.0f,15.0f,	0.7f,0.5f,0.2f,b2_dynamicBody);

jugadorData.tag = BodyTag::Jugador;

Jugador->GetUserData().pointer = reinterpret_cast<uintptr_t>(&jugadorData);


}


///Reiniciar el juego
void JugadorReiniciar() {Jugador->SetTransform(b2Vec2(50.0f, 450.0f), 0.0f); Jugador->SetLinearVelocity(b2Vec2(0.0f, 0.0f)); estado = EstadoJuego::Waiting;	instruccionesb = true;}


void Cajas() {


	//Crear PUENTE

	for (int i = 0; i < 6; i++) {
		boxDef.type = b2_dynamicBody;
		boxDef.position.Set(300.0f+ 70*i, 450.0f);

		boxBody = world.CreateBody(&boxDef);

		b2PolygonShape boxShape;
		boxShape.SetAsBox(25.0f, 10.0f);

		b2FixtureDef boxFixture;
		boxFixture.shape = &boxShape;
		boxFixture.density = 0.5f;
		boxFixture.friction = 0.4f;
		boxFixture.restitution = 0.2f;

		boxBody->CreateFixture(&boxFixture);

		boxes.push_back({ boxBody, 50.0f, 20.0f, Fade(SKYBLUE, 0.95f) });

	}


	//Escalera
	escalon1 = CrearFigura(165.0f, 520.0f,20.0f, 20.0f,0.0f, 0.5f, 0.0f,b2_staticBody);
	escalon2 = CrearFigura(215.0f, 500.0f,20.0f, 43.0f,	0.0f, 0.5f, 0.0f,b2_staticBody);
	escalon3 = CrearFigura(	735.0f, 500.0f,	20.0f, 43.0f,0.0f, 0.5f, 0.0f,b2_staticBody);
	escalon4 = CrearFigura(	785.0f, 520.0f,	20.0f, 20.0f,0.0f, 0.5f, 0.0f,b2_staticBody);



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

	anchorJoint.length = 5.0f;
	anchorJoint.stiffness = 5.0f;
	anchorJoint.damping = 5.0f;

	world.CreateJoint(&anchorJoint);


}


//Creacion de los joints y anchors
void Joints() {


	CrearAnchor(anchorBody,anchorDef,250.0f,450.0f,boxes[0].body,boxes[0].body->GetWorldPoint(b2Vec2(-25.0f, 0.0f)));

	CrearAnchor(anchorBody2, anchorDef2, 700.0f, 450.0f, boxes[5].body, boxes[5].body->GetWorldPoint(b2Vec2(25.0f, 0.0f)));


	for (int i = 0; i < boxes.size() - 1; i++)
	{
		CrearJoint(boxes[i].body,boxes[i + 1].body,boxes[i].body->GetWorldPoint(b2Vec2(25.0f, 0.0f)),boxes[i + 1].body->GetWorldPoint(b2Vec2(-25.0f, 0.0f)),5.0f);
	}



}

//Instrucciones

void Instrucciones(Color textoPrincipal,Color textoSecundario, bool instruccionesb) {
	if (instruccionesb == true) {
		DrawText("- Instrucciones:", 10, 15, 28, textoPrincipal);
		DrawText("- Utiliza las flechas para moverte de <- izquierda  a derecha ->.", 10, 55, 22, textoSecundario);
		DrawText("- Oprime la tecla ESPACIO para realizar saltos.", 10, 90, 22, textoSecundario);
		DrawText("- Si deseas reiniciar la ubicacion de tu personaje usa la R .", 10, 125, 22, textoSecundario);
		DrawText("- Para abandonar el juego oprime la tecla ESC .", 10, 155, 22, textoSecundario);
		DrawText("- Tu objetivo es cruzar el puente hasta el otro extremo para ganar .", 10, 185, 22, textoSecundario);
		DrawText("- Oprime H para ocultar las instrucciones.", 10, 215, 22, textoSecundario);
	}
}



//Contact - Colisión - Creación visual
void CrearMeta(){meta = CrearFigura(950.0f,490.0f,25.0f,25.0f,0.0f,0.0f,0.0f,b2_staticBody);meta->GetFixtureList()->SetSensor(true);


metaData.tag = BodyTag::Meta;

meta->GetUserData().pointer = reinterpret_cast<uintptr_t>(&metaData);

}
