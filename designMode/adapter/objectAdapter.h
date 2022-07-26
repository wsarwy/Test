#include <string>
#include <iostream>

using namespace std;

class interfaceTarget1
{
    virtual void request() = 0;
};

class objectAdaptee
{
    public:
    void specialRequest(int num)
    {
        cout<<" adaptee request : "<<num<< endl;
    }
};

class objectAdapter : public interfaceTarget1
{
    public:
    void request()
    {
        adaptee = new objectAdaptee();
        adaptee->specialRequest(9);
        cout<<" object adapter function success"<<endl;
    } 

    private:
    objectAdaptee* adaptee;
};