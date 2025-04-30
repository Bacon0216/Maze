#ifndef CPU_H_INCLUDED
#define CPU_H_INCLUDED
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class CPU
{
public:
    CPU() = default;
    void pushpath(char);
    void pushV_path(char);
    void popV_path();

    void GoUpward();
    void GoDownward();
    void GoLeft();
    void GoRight();
    void Run();

    void Setshortest();
    void Setpath();
    int Getpathsize();
    int Getcount();

    int Getrow() const;
    int Getcol() const;
    void Setrow(int);
    void Setcol(int);
    
private:
    int CPUposition_row;
    int CPUposition_col;
    int count;
    queue<char> path;
    vector<char> v_path;
    vector<char> shortest;
};

#endif //CPU_H_INCLUDED