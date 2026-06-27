#pragma once

#include "raylib.h"
#include <box2d.h>

extern const int screenWidth;
extern const int screenHeight;

extern b2Vec2 gravity;
extern b2World world;

extern b2BodyDef boxDef;
extern b2Body* boxBody;

extern Color fondo;
extern Color sueloColor;

//Textos
extern Color textoPrincipal;
extern Color textoSecundario;


//Texturas
extern Texture2D jugadorTexture;
extern Texture2D SoporteTexture;
extern Texture2D Soporte2Texture;

//Contact - Colisión

extern bool saltoactivo;
extern bool instruccionesb;





void InitGame();
void UpdateGame();
void DrawGame();


