#pragma once

#include <box2d.h>



//Estado actual del juego
enum class EstadoJuego
{
    Waiting,
    Running,
    EventDetected,
    Finished
};

//Colisiones



enum class BodyTag
{
    Jugador,
    Meta
};

struct BodyData{BodyTag tag;};

class MyContactListener : public b2ContactListener {

public:
    void BeginContact(b2Contact* contact) override;
    void EndContact(b2Contact* contact) override;
};


extern EstadoJuego estado;