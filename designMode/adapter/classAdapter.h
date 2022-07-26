#include <string>
#include <iostream>
using namespace std;

class interfaceTarget
{
    public:
    virtual void request() = 0;
};

class classAdaptee
{
    public:
    void specialRequest(int num)
    {
        cout<<" adaptee request : "<<num<< endl;
    }
};

class classAdapter : public interfaceTarget, public classAdaptee
{
    public:
    void request()
    {
        this->specialRequest(1);
        cout<<"adapter function success"<<endl;
    }
};