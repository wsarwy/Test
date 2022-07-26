#include "abstractBuilder.h"

class concreteBuilderA : public Abstractbulider
{
private:
    /* data */
public:
    concreteBuilderA(/* args */){}
    ~concreteBuilderA(){}

    concreteBuilderA(const concreteBuilderA& rhs) = delete;
    concreteBuilderA& operator=(const concreteBuilderA& rhs) = delete;

    void buildProperty1()
    {
        product->setProperty1("property A 1");
    }

    void buildProperty2()
    {
        product->setProperty2("property A 2");
    }

    void buildProperty3()
    {
        product->setProperty3("property A 3");
    }

    Product* getProduct()
    {
        return product;
    } 
};

class concreteProductB : public Abstractbulider
{
private:
    /* data */
public:
    concreteProductB(/* args */){}
    ~concreteProductB(){}

    concreteProductB(const concreteProductB& rhs) = delete;
    concreteProductB& operator=(const concreteProductB& rhs) = delete;


    void buildProperty1()
    {   
        product->setProperty1("property B 1");
    }

    void buildProperty2()
    {
        product->setProperty2("property B 2");
    }

    void buildProperty3()
    {
        product->setProperty3("property B 3");
    }

    Product* getProduct()
    {
        return product;
    }
};


