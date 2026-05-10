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
	InitWindow(screenWidth, screenHeight, "MAVI II -La Catapulta de Mavix");
	SetTargetFPS(60);


	b2BodyDef groundDef;
	groundDef.type = b2_staticBody;
	groundDef.position.Set(screenWidth / 2.0f, screenHeight - 40.0f);
	b2Body* groundBody = world.CreateBody(&groundDef);

	b2PolygonShape groundShape;
	groundShape.SetAsBox(screenWidth / 2.0f, 20.0f);
	groundBody->CreateFixture(&groundShape, 0.0f);

    Cajas();

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
            DrawRectanglePro(rect, origin, angle, box.color);
            DrawRectangleLinesEx(rect, 2, DARKBLUE);

        }

        if (IsKeyPressed(KEY_SPACE))
        {
            boxBody->ApplyLinearImpulseToCenter(b2Vec2(impulsoX, impulsoY), true);
        }

        EndDrawing();
    }


}

