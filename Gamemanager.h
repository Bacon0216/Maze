#ifndef GAMEMANAGER_H_INCLUDED
#define GAMEMANAGER_H_INCLUDED
#include <Windows.h>

#include "cpu.h"
#include <conio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

using namespace std;

class Gamemanager
{
public:
    Gamemanager() = default;
    void OpenFile(int , char** );
    void Menu();
    void CreateMaze();
    void Gamemode();
    void Findpath();
    void AutoPlay();
    void GetInputKey();
    void PrintMaze();

    bool Getmode();
private:
    CPU cpu; 
    bool IsAutoPlay;
    int maze_row;
    int maze_col;
    int Playerposition_row;
    int Playerposition_col;
    int Endposition_row;
    int Endposition_col;
    ifstream file;
    vector<string> filelist;
    vector<vector<vector<char>>> mazelist;
    vector<vector<char>> maze;
};

#endif //GAMEMANAGER_H_INCLUDED