#include <iostream>
#include "abstractProduct.h"

class abstractFactory
{
private:
    /* data */
public:
    abstractFactory(/* args */){}
    ~abstractFactory(){}

    virtual abstractProduct* createProduct1() = 0;
    virtual abstractProduct* createProduct2() = 0;
};


//-------------------------------------------------------//

class productFactory1 : public abstractFactory
{
private:
    /* data */
public:
    productFactory1(/* args */){}
    ~productFactory1(){}

    virtual abstractProduct* createProduct1() override
    {
        std::cout<< "abstractFactory1 produce product1" << std::endl;
        return new abstractProduct1();
    }
    virtual abstractProduct* createProduct2() override
    {
        std::cout<< "abstractFactory1 produce product2" << std::endl;
        return new abstractProduct2();
    }
};

//---------------------------------------------------------//

class productFactory2: public abstractFactory
{
private:
    /* data */
public:
    productFactory2(/* args */){}
    ~productFactory2(){}

     virtual abstractProduct* createProduct1()
    {
        std::cout<< "abstractFactory2 produce product1" << std::endl;
        return new abstractProduct1();
    }
    virtual  abstractProduct* createProduct2()
    {
        std::cout<< "abstractFactory2 produce product2" << std::endl;
        return new abstractProduct2();
    }
};





