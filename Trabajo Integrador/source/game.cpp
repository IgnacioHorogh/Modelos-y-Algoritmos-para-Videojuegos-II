#ifndef NDEBUG
#include <vld.h>
#include <iostream>
#endif
#include "raylib.h"
#include <box2d.h>
#include <vector>
#include "game.h"
#include "cajas.h"



const int screenWidth = 1000;
const int screenHeight = 600;

bool saltoactivo = true;

b2Vec2 gravity(0.0f, 9.8f);
b2World world(gravity);

b2BodyDef boxDef;
b2Body* boxBody = world.CreateBody(&boxDef);

Color fondo = { 110, 100, 215, 255 };
Color textoPrincipal = RAYWHITE;
Color textoSecundario = ORANGE;
Color sueloColor = Fade(DARKGREEN, 0.7f);




void InitGame() {
	InitWindow(screenWidth, screenHeight, "MAVI -TP Integrador");
	SetTargetFPS(60);


	b2BodyDef groundDef;
	groundDef.type = b2_staticBody;
	groundDef.position.Set(screenWidth / 2.0f, screenHeight - 40.0f);
	b2Body* groundBody = world.CreateBody(&groundDef);

	b2PolygonShape groundShape;
	groundShape.SetAsBox(screenWidth / 2.0f, 20.0f);
	groundBody->CreateFixture(&groundShape, 0.0f);

    Cajas();
    Joints();
    JugadorCrear();
    ObstaculoCrear();



}

void DrawGame() {

    BeginDrawing();
    ClearBackground(fondo);
    DrawRectangle(0, screenHeight - 60, screenWidth, 40, sueloColor);

}


void UpdateGame() {
    while (!WindowShouldClose())
    {

        world.Step(2.5f / 60.0f, 8, 3);
        DrawGame();


        //Cajas del puente

        for (const auto& box : boxes)
        {

            b2Vec2 pos = box.body->GetPosition();

            Rectangle rect = {
                pos.x - box.width / 2.0f,
                pos.y - box.height / 2.0f,
                box.width,
                box.height
            };
                    
           
            DrawRectangleLinesEx(rect, 2, DARKPURPLE);

        }


        //Escalera

        b2Body* escalones[4] ={escalon1,escalon2,escalon3,escalon4};
        float ancho[4] = { 40,40,40,40 };
        float alto[4] = { 40,86,86,40 };


        for (int i = 0; i < 4; i++)
        {
            b2Vec2 pos = escalones[i]->GetPosition();
            Rectangle rect ={pos.x - ancho[i] / 2, pos.y - alto[i] / 2,ancho[i],alto[i]};
            DrawRectangleLinesEx(rect, 2, DARKGREEN);
        }




        //Joint
      


        for (int i = 0; i < boxes.size() - 1; i++)
        {
            b2Vec2 anchorA = boxes[i].body->GetWorldPoint(b2Vec2(25.0f, 0.0f));

            b2Vec2 anchorB = boxes[i + 1].body->GetWorldPoint(b2Vec2(-25.0f, 0.0f));

            DrawLineEx(Vector2{ anchorA.x, anchorA.y }, Vector2{ anchorB.x, anchorB.y },4.0f,PURPLE);}




        ///Ubicacion de los anchors
        anchorPos = anchorBody->GetPosition();

        anchorPos2 = anchorBody2->GetPosition();


        ///Ubicacion de la union de los joints
        ladoizq = boxes[0].body->GetWorldPoint(b2Vec2(-25.0f, 0.0f));

        ladoder = boxes[5].body->GetWorldPoint(b2Vec2(25.0f, 0.0f));


  

        //Anchor 1 (izq)
       
        DrawLineEx(Vector2{ anchorPos.x, anchorPos.y },Vector2{ ladoizq.x, ladoizq.y }, 4.0f, GREEN);
        DrawCircle(anchorPos.x, anchorPos.y, 8, DARKGREEN);

        //Anchor 2 (der)

        
        DrawLineEx(Vector2{ anchorPos2.x, anchorPos2.y },Vector2{ ladoder.x, ladoder.y },4.0f, GREEN);
        DrawCircle(anchorPos2.x, anchorPos2.y, 8, DARKGREEN);

        ///Jugador
        b2Vec2 jugadorPos = Jugador->GetPosition();
        Rectangle rectJugador = { jugadorPos.x - 15.0f,jugadorPos.y - 15.0f,25.0f,25.0f};
        DrawRectangleLinesEx(rectJugador, 2, ORANGE);
       
        //////"Antifly"-Límite - de saltos        
        if (jugadorPos.y > 400.0f) { saltoactivo = true; }

        ///Obstaculo

        b2Vec2 obstaculoPos = obstaculo->GetPosition();
        Rectangle rectObstaculo ={obstaculoPos.x - 25.0f,obstaculoPos.y - 20.0f,50.0f,50.0f};
        DrawRectangleLinesEx(rectObstaculo, 2, RED);


        ///Inputs

        if (IsKeyPressed(KEY_SPACE) && saltoactivo){Jugador->ApplyLinearImpulseToCenter(b2Vec2(0.0f, -20000.0f), true);saltoactivo = false;}
        if (IsKeyPressed(KEY_RIGHT)) { Jugador->ApplyLinearImpulseToCenter(b2Vec2(+10000.0f, 0.0f), true); }
        if (IsKeyPressed(KEY_LEFT)) { Jugador->ApplyLinearImpulseToCenter(b2Vec2(-10000.0f, 0.0f), true); }
        if (IsKeyPressed(KEY_R)) { JugadorReiniciar(); }


        ///Textos

        Instrucciones(textoPrincipal, textoSecundario);


        EndDrawing();
    }


}

