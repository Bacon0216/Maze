#include <iostream>
#include "Gamemanager.h"

int main(int argc, char** argv)
{
    if (argc == 1)
    {
        cout << "./a.out filename";
        return 0;
    }
    Gamemanager gamemanager;

    gamemanager.OpenFile(argc, argv);
    gamemanager.Menu();
    gamemanager.CreateMaze();
    gamemanager.Gamemode();

    if (gamemanager.Getmode())
    {
        gamemanager.AutoPlay();
    }
    else
    {
        gamemanager.PrintMaze();
        gamemanager.GetInputKey();
    }
}
