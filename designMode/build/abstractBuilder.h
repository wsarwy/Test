#include "product.h"

class Abstractbulider
{
    public:
    Abstractbulider()
    {
        product = new Product();
    }

    ~Abstractbulider()
    {
        if(product != nullptr)
        {
            delete product;
            product = nullptr;
        }
    }

    Abstractbulider(const Abstractbulider& rhs) = delete;
    Abstractbulider& operator=(const Abstractbulider& rhs) = delete;

    virtual void buildProperty1() = 0;
    virtual void buildProperty2() = 0;
    virtual void buildProperty3() = 0;
    virtual Product* getProduct() = 0;

    Product* product;

};