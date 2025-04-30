#include "Gamemanager.h"

void Gamemanager::OpenFile(int argc, char** argv)
{
    for (int i = 1; i < argc; i++)
    {
        file.open(argv[i], ios::in);
        if (!file.is_open())
        {
            cout << "Fail to open file:" << argv[i] << endl;
            exit(1);
        }
        filelist.push_back(argv[i]);
        CreateMaze();
        mazelist.push_back(maze);
        maze.clear();
        file.close();
    }
}

void Gamemanager::Menu()
{

    cout << "Use 'W' and 'D' to change the maze\nUse 'S' to select the maze you want\n";
    int maptag = 0;
    for (int i = 0; i < mazelist[maptag].size(); i++)
    {
        for (int j = 0; j < mazelist[maptag][i].size(); j++)
        {
            cout << mazelist[maptag][i][j];
        }
        cout << "\n";
    }
    cout << "Maze " << maptag + 1 << "\n";

    while(true)
    {
        if (_kbhit())
        {
            char ch = _getch();
            ch = toupper(ch);
            
            if (ch == 'A' && maptag != 0)
            {
                maptag--;
                system("cls");
                cout << "Use 'W' and 'D' to change the maze\nUse 'S' to select the maze you want\n";
                for (int i = 0; i < mazelist[maptag].size(); i++)
                {
                    for (int j = 0; j < mazelist[maptag][i].size(); j++)
                    {
                        cout << mazelist[maptag][i][j];
                    }
                    cout << "\n";
                }
                cout << "Maze " << maptag + 1 << "\n";
            }
            if (ch == 'D' && maptag != mazelist.size() - 1)
            {
                maptag++;
                system("cls");
                cout << "Use 'W' and 'D' to change the maze\nUse 'S' to select the maze you want\n";
                for (int i = 0; i < mazelist[maptag].size(); i++)
                {
                    for (int j = 0; j < mazelist[maptag][i].size(); j++)
                    {
                        cout << mazelist[maptag][i][j];
                    }
                    cout << "\n";
                }
                cout << "Maze " << maptag + 1 << "\n";
            }
            if (ch == 'S')
            {
                file.open(filelist[maptag], ios::in);
                break;
            }
        }
    }
}

void Gamemanager::CreateMaze()
{
    string line;
    getline(file, line);
    stringstream rc(line);
    rc >> maze_row >> maze_col;

    while (getline(file, line))
    {
        stringstream ss(line);
        vector<char> v;
        char object;

        while(ss >> object)
        {
            if(object == '0')
            {
                Playerposition_row = maze.size();
                Playerposition_col = v.size();
                cpu.Setrow(maze.size());
                cpu.Setcol(v.size());
            }
            else if (object == '1')
            {
                Endposition_row = maze.size();
                Endposition_col = v.size();
            }
            v.push_back(object);
        }
        maze.push_back(v);
    }
}

void Gamemanager::Gamemode()
{
    cout << "Choose the mode : (1:cpu, 2:player) ";
    int mode;
    cin >> mode;
    if (mode == 1)
    {
        IsAutoPlay = true;
    }
    else if (mode == 2)
    {
        IsAutoPlay = false;
    }
}

void Gamemanager::Findpath()
{
    if (cpu.Getrow() == Endposition_row && cpu.Getcol() == Endposition_col)
    {
        cpu.Setshortest();
        return;
    }

    if (cpu.Getrow() > 0 && (maze[cpu.Getrow() - 1][cpu.Getcol()] == '-' || maze[cpu.Getrow() - 1][cpu.Getcol()] == '1'))
    {
        bool IsEnd = false;
        if (maze[cpu.Getrow() - 1][cpu.Getcol()] == '1')
        {
            IsEnd = true;
        }

        maze[cpu.Getrow() - 1][cpu.Getcol()] = '0';
        maze[cpu.Getrow()][cpu.Getcol()] = '+';
        cpu.GoUpward();
        cpu.pushV_path('W');
        Findpath();
        cpu.popV_path();
        maze[cpu.Getrow() + 1][cpu.Getcol()] = '0';
        if (IsEnd)
        {
            maze[cpu.Getrow()][cpu.Getcol()] = '1';
        }
        else
        {
            maze[cpu.Getrow()][cpu.Getcol()] = '-';
        }
        cpu.GoDownward();
    }
    if(cpu.Getrow() < maze_row - 1 && (maze[cpu.Getrow() + 1][cpu.Getcol()] == '-' || maze[cpu.Getrow() + 1][cpu.Getcol()] == '1'))
    {
        bool IsEnd = false;
        if (maze[cpu.Getrow() + 1][cpu.Getcol()] == '1')
        {
            IsEnd = true;
        }

        maze[cpu.Getrow() + 1 ][cpu.Getcol()] = '0';
        maze[cpu.Getrow()][cpu.Getcol()] = '+';
        cpu.GoDownward();
        cpu.pushV_path('S');
        Findpath();
        cpu.popV_path();
        maze[cpu.Getrow() - 1][cpu.Getcol()] = '0';
        if (IsEnd)
        {
            maze[cpu.Getrow()][cpu.Getcol()] = '1';
        }
        else 
        {
            maze[cpu.Getrow()][cpu.Getcol()] = '-';
        }
        cpu.GoUpward();
    }
    if (cpu.Getcol() > 0 && (maze[cpu.Getrow()][cpu.Getcol() - 1] == '-' || maze[cpu.Getrow()][cpu.Getcol() - 1] == '1'))
    {
        bool IsEnd = false;
        if (maze[cpu.Getrow()][cpu.Getcol() - 1] == '1')
        {
            IsEnd = true;
        }

        maze[cpu.Getrow()][cpu.Getcol() - 1] = '0';
        maze[cpu.Getrow()][cpu.Getcol()] = '+';
        cpu.GoLeft();
        cpu.pushV_path('A');
        Findpath();
        cpu.popV_path();
        maze[cpu.Getrow()][cpu.Getcol() + 1] = '0';
        if (IsEnd)
        {
            maze[cpu.Getrow()][cpu.Getcol()] = '1';
        }
        else 
        {
            maze[cpu.Getrow()][cpu.Getcol()] = '-';
        }
        cpu.GoRight();
    }
    if (cpu.Getcol() < maze_col - 1 && (maze[cpu.Getrow()][cpu.Getcol() + 1] == '-' || maze[cpu.Getrow()][cpu.Getcol() + 1] == '1'))
    {
        bool IsEnd = false;
        if (maze[cpu.Getrow()][cpu.Getcol() + 1] == '1')
        {
            IsEnd = true;
        }

        maze[cpu.Getrow()][cpu.Getcol() + 1] = '0';
        maze[cpu.Getrow()][cpu.Getcol()] = '+';
        cpu.GoRight();
        cpu.pushV_path('D');
        Findpath();
        cpu.popV_path();
        maze[cpu.Getrow()][cpu.Getcol() - 1] = '0';
        if (IsEnd)
        {
            maze[cpu.Getrow()][cpu.Getcol()] = '1';
        }
        else
        {
            maze[cpu.Getrow()][cpu.Getcol()] = '-';
        }
        cpu.GoLeft();
    }
}

void Gamemanager::AutoPlay()
{
    Findpath();
    cpu.Setpath();
    system("cls");
    PrintMaze();
    while (cpu.Getpathsize() != 0)
    {
        Sleep(300);
        maze[cpu.Getrow()][cpu.Getcol()] = '-';
        cpu.Run();
        maze[cpu.Getrow()][cpu.Getcol()] = '0';
        system("cls");
        PrintMaze();
    }
    cout << "Need at least " << cpu.Getcount() << " steps to get to exit";
}

void Gamemanager::GetInputKey()
{
    int count = 0;
    while (true) 
    {
        if (_kbhit())
        {
            char ch = getch();
            ch = toupper(ch);
            if (ch == 'W') 
            {
                if (Playerposition_row - 1 >= 0 && maze[Playerposition_row - 1][Playerposition_col] == '-')
                {
                    maze[Playerposition_row - 1][Playerposition_col] = '0';
                    maze[Playerposition_row][Playerposition_col] = '-';
                    Playerposition_row -= 1;
                    count++;
                }
                else if (Playerposition_row - 1 >= 0 && maze[Playerposition_row - 1][Playerposition_col] == '1')
                {
                    maze[Playerposition_row - 1][Playerposition_col] = '0';
                    maze[Playerposition_row][Playerposition_col] = '-';
                    Playerposition_row -= 1;
                    count++;
                    system("cls");
                    PrintMaze();
                    cout << "\n! You Win !\n";
                    cout << "You spent " << count << " steps to reach the exit";
                    break;
                }
                system("cls");
                PrintMaze();
            }
            if (ch == 'A') 
            {
                if (Playerposition_col - 1 >= 0 && maze[Playerposition_row][Playerposition_col - 1] == '-')
                {
                    maze[Playerposition_row][Playerposition_col - 1] = '0';
                    maze[Playerposition_row][Playerposition_col] = '-';
                    Playerposition_col -= 1;
                    count++;
                }
                else if (Playerposition_col - 1 >= 0 && maze[Playerposition_row][Playerposition_col - 1] == '1')
                {
                    maze[Playerposition_row][Playerposition_col - 1] = '0';
                    maze[Playerposition_row][Playerposition_col] = '-';
                    Playerposition_col -= 1;
                    count++;
                    system("cls");
                    PrintMaze();
                    cout << "\n! You Win !\n"; 
                    cout << "You spent " << count << " steps to reach the exit";
                    break;
                }
                system("cls");
                PrintMaze();
            }
            if (ch == 'S') 
            {
                if (Playerposition_row + 1 < maze_row && maze[Playerposition_row + 1][Playerposition_col] == '-')
                {
                    maze[Playerposition_row + 1][Playerposition_col] = '0';
                    maze[Playerposition_row][Playerposition_col] = '-';
                    Playerposition_row += 1;
                    count++;
                }
                else if (Playerposition_row + 1 < maze_row && maze[Playerposition_row + 1][Playerposition_col] == '1')
                {
                    maze[Playerposition_row + 1][Playerposition_col] = '0';
                    maze[Playerposition_row][Playerposition_col] = '-';
                    Playerposition_row += 1;
                    count++;
                    system("cls");
                    PrintMaze();
                    cout << "\n! You Win !\n";
                    cout << "You spent " << count << " steps to reach the exit";
                    break;
                }
                system("cls");
                PrintMaze();
            }
            if (ch == 'D') 
            {
                if (Playerposition_col + 1 < maze_col && maze[Playerposition_row][Playerposition_col + 1] == '-')
                {
                    maze[Playerposition_row][Playerposition_col + 1] = '0';
                    maze[Playerposition_row][Playerposition_col] = '-';
                    Playerposition_col += 1;
                    count++;
                }
                else if (Playerposition_col + 1 < maze_col && maze[Playerposition_row][Playerposition_col + 1] == '1')
                {
                    maze[Playerposition_row][Playerposition_col + 1] = '0';
                    maze[Playerposition_row][Playerposition_col] = '-';
                    Playerposition_col += 1;
                    count++;
                    system("cls");
                    PrintMaze();
                    cout << "\n! You Win !\n";
                    cout << "You spent " << count << " steps to reach the exit";
                    break;
                }            
                system("cls");
                PrintMaze();

            }
        }
        
    }
}

void Gamemanager::PrintMaze()
{
    for (int i = 0; i < maze_row; i++)
    {
        for (int j = 0; j < maze_col; j++)
        {
            cout << maze[i][j];
        }
        cout << "\n";
    }
}

bool Gamemanager::Getmode()
{
    return IsAutoPlay;
}