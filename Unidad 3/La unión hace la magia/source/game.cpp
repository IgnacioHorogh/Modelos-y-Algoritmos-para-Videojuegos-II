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

b2Vec2 gravity(0.0f, 9.8f);
b2World world(gravity);

b2BodyDef boxDef;
b2Body* boxBody = world.CreateBody(&boxDef);

Color fondo = { 110, 100, 215, 255 };
Color textoPrincipal = RAYWHITE;
Color textoSecundario = DARKPURPLE;
Color sueloColor = Fade(DARKGREEN, 0.7f);




void InitGame() {
	InitWindow(screenWidth, screenHeight, "MAVI III -La union hace la magia");
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
            float angle = box.body->GetAngle() * RAD2DEG;

            Rectangle rect = {
                pos.x - box.width / 2.0f,
                pos.y - box.height / 2.0f,
                box.width,
                box.height
            };

            Vector2 origin = { box.width / 2.0f, box.height / 2.0f };
           
            DrawRectangleLinesEx(rect, 2, DARKPURPLE);

        }




        //Joint
      


        for (int i = 0; i < boxes.size() - 1; i++)
        {
            b2Vec2 anchorA = boxes[i].body->GetWorldPoint(b2Vec2(50.0f, 0.0f));

            b2Vec2 anchorB = boxes[i + 1].body->GetWorldPoint(b2Vec2(-50.0f, 0.0f));

            DrawLineEx(Vector2{ anchorA.x, anchorA.y }, Vector2{ anchorB.x, anchorB.y },4.0f,PURPLE);}




        ///Ubicacion de los anchors
        anchorPos = anchorBody->GetPosition();

        anchorPos2 = anchorBody2->GetPosition();


        ///Ubicacion de la union de los joints
        ladoizq = boxes[0].body->GetWorldPoint(b2Vec2(-50.0f, 0.0f));

        ladoder = boxes[5].body->GetWorldPoint(b2Vec2(50.0f, 0.0f));


        //Ubicacion del eje del pendulo y de su union

        b2Vec2 puntoeje = boxes[2].body->GetWorldPoint(b2Vec2(0.0f, 25.0f));        

        b2Vec2 pendulopunta = pendulo->GetWorldPoint(b2Vec2(0.0f, -40.0f));

        b2Vec2 penduloPos = pendulo->GetPosition();

        //Anchor 1 (izq)

        DrawCircle(anchorPos.x, anchorPos.y, 8, ORANGE);
        DrawLineEx(Vector2{ anchorPos.x, anchorPos.y },Vector2{ ladoizq.x, ladoizq.y }, 4.0f, ORANGE);

        //Anchor 2 (der)

        DrawCircle(anchorPos2.x, anchorPos2.y, 8, ORANGE);
        DrawLineEx(Vector2{ anchorPos2.x, anchorPos2.y },Vector2{ ladoder.x, ladoder.y },4.0f,ORANGE);




        /////PENDULO
    

        Rectangle penduloRect = {penduloPos.x - 20.0f,penduloPos.y - 40.0f, 40.0f, 80.0f};


        DrawCircle(puntoeje.x, puntoeje.y, 6, YELLOW);
        DrawLineEx(Vector2{ puntoeje.x, puntoeje.y }, Vector2{ pendulopunta.x, pendulopunta.y }, 4.0f, RED );  
        DrawRectangleLinesEx(penduloRect, 2, RED);



        /////Comprobadores de físicas, Space para mover la caja, A y D para mover el pendulo

        if (IsKeyPressed(KEY_SPACE)){boxes[2].body->ApplyLinearImpulseToCenter(b2Vec2(-100000.0f, -1000000.0f),true);}

        if (IsKeyPressed(KEY_A)) { pendulo->ApplyLinearImpulseToCenter(b2Vec2(-100000.0f, 0.0f), true); }

        if (IsKeyPressed(KEY_D)) { pendulo->ApplyLinearImpulseToCenter(b2Vec2(100000.0f, 0.0f), true); }



        EndDrawing();
    }


}

