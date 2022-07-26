
#include "concreteBuilder.h"

class Director
{

 public:
    Director(){}
    ~Director()
    {
        if(this->m_abstractBuilder != nullptr)
        {
            delete m_abstractBuilder;
            this->m_abstractBuilder = nullptr;
        }
    }

    Director(const Director& rhs) = delete;
    Director& operator=(const Director& rhs) = delete;

    void setBuilder(Abstractbulider *builder) { this->m_abstractBuilder = builder;}

    Product* construct()
    {
        this->m_abstractBuilder->buildProperty1();
        this->m_abstractBuilder->buildProperty2();
        this->m_abstractBuilder->buildProperty3();
        return m_abstractBuilder->product;
    }
private:
    Abstractbulider *m_abstractBuilder;
};