#include <iostream>
#include <vector>
using namespace std;

double divide(int x, int y)
{
    if( x == 0)
    {
        throw "divide by zero";
    }

    return (x/y);
}

int main()
{
    
}