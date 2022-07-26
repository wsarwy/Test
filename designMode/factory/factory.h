#include <iostream>
#include "abstractNormalProduct.h"

using namespace std; 


class abstractNormalFactory
{
    private:

    public:
    abstractNormalFactory(){}

    ~abstractNormalFactory(){}

    virtual abstractNormalProduct* createProduct() = 0 ;

};


class normalFactory1 : public abstractNormalFactory
{
    private:

    public:
    normalFactory1(){}

    ~normalFactory1(){}

    virtual abstractNormalProduct* createProduct() override
    {
        cout<<"normalFactory1 create product1"<<endl;
        return new normalProduct1();
    }
};

class normalFactory2: public abstractNormalFactory
{
    private:

    public:
    normalFactory2(){}

    ~normalFactory2(){}

    virtual abstractNormalProduct* createProduct() override
    {
        cout<<"normalFactory2 create product2"<<endl;
        return new normalProduct2();
    }
};