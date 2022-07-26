#include <iostream>
#include <string>
#include "simpleProduct.h"
using namespace std;

class simpleFactory
{
    private:

    public:
    simpleFactory(){}
    ~simpleFactory(){}

    abstractSimpleProduct* createProduct(string cmd)
    {
        if(cmd == "create Product1")
        {
            cout<<"simpleFactory create product1"<<endl;
            return new simpleProduct1();
        }
        else if(cmd == "create Product2")
        {
            cout<<"simpleFactoryactory Product2"<<endl;
            return new simpleProduct2();
        }
        else
        {
            return nullptr;
        }
    }
};