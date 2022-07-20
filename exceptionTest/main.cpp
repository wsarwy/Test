#include <iostream>
#include <vector>
using namespace std;

double divide(int x, int y)
{
    if( y == 0)
    {
        throw string("divide by zero");
    }

    return (x/y);
}

class testArray
{
    public:
    int x = 10;
};

void func()
{
    testArray* test_array = new testArray[10];


    int* array = new int[10];

    try
    {
        divide(1,0);
    }
    catch(const string errmsg)
    {
        cout<< errmsg <<endl;
        delete[] array;
        throw;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    cout<<"delete []"<<endl;
    delete[] array;
}

int main()
{
    try
    {
        func();
    }
    catch(const string errmsg)
    {
        cout<<errmsg<<endl;
    }
    
    
}