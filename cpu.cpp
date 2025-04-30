#include "cpu.h" 


void CPU::pushpath(char c)
{
    path.push(c);
}

void CPU::pushV_path(char c)
{
    v_path.push_back(c);
}

void CPU::popV_path()
{
    v_path.pop_back();
}

void CPU::GoUpward()
{
    CPUposition_row--;
}

void CPU::GoDownward()
{
    CPUposition_row++;
}

void CPU::GoLeft()
{
    CPUposition_col--;
}

void CPU::GoRight()
{
    CPUposition_col++;
}

void CPU::Run()
{
    if (path.front() == 'W')
    {
        CPUposition_row--;
    }
    else if (path.front() == 'A')
    {
        CPUposition_col--;
    }
    else if (path.front() == 'S')
    {
        CPUposition_row++;
    }
    else if (path.front() == 'D')
    {
        CPUposition_col++;
    }
    path.pop();

}

void CPU::Setshortest()
{
    if (v_path.size() <= shortest.size() || shortest.size() == 0)
    {
        shortest.clear();
        shortest.resize(v_path.size());
        shortest = v_path;
    }
}

void CPU::Setpath()
{
    cout << "\nshortest size : " << shortest.size() << "\n";
    while(shortest.size() != 0)
    {
        path.push(shortest.front());
        shortest.erase(shortest.begin());
    }
    count = path.size();
}

int CPU::Getpathsize()
{
    return path.size();
}

int CPU::Getcount()
{
    return count;
}

int CPU::Getrow() const
{
    return CPUposition_row;
}

int CPU::Getcol() const
{
    return CPUposition_col;
}

void CPU::Setrow(int i)
{
    CPUposition_row = i;
}

void CPU::Setcol(int i)
{
    CPUposition_col = i;
}