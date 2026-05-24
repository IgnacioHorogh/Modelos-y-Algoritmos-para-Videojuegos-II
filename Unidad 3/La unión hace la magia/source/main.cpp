#ifndef NDEBUG
#include <vld.h>
#include <iostream>
#endif
#include "raylib.h"
#include <box2d.h>
#include <vector>
#include "game.h"


int main(void)
{

    InitGame();

    UpdateGame();

    DrawGame();

    CloseWindow();


    return 0;
}
