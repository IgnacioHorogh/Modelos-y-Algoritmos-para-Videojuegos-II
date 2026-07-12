#include "contacto.h"
#include "cajas.h"
#include "game.h"


void MyContactListener::BeginContact(b2Contact* contact)
{
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();

    b2Body* bodyA = fixtureA->GetBody();
    b2Body* bodyB = fixtureB->GetBody();

    BodyData* dataA = reinterpret_cast<BodyData*>(bodyA->GetUserData().pointer);

    BodyData* dataB = reinterpret_cast<BodyData*>(bodyB->GetUserData().pointer);


    if (!dataA || !dataB)return;

    bool jugadorLlegoMeta = (dataA->tag == BodyTag::Jugador && dataB->tag == BodyTag::Meta) || (dataA->tag == BodyTag::Meta && dataB->tag == BodyTag::Jugador);
  
    if (jugadorLlegoMeta) { estado = EstadoJuego::EventDetected; }

}

void MyContactListener::EndContact(b2Contact* contact){}


