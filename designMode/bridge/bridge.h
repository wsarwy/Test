#include <string>
#include <iostream>

using namespace std;

class abstractFunction
{
   virtual void operation() = 0;
};

class implementFunctionA : public abstractFunction
{
    void operation()
    {
        cout<<" function A implement"<<endl;
    }

};

class implementFunctionB : public abstractFunction
{
    void operation()
    {
        cout<< " function B implement" <<endl;
    }
};

class abstractProduct
{
    virtual void setFunction(abstractFunction* rhs) = 0;
    virtual void operation() = 0;
};


class product : public abstractProduct
{
    public:

    void setFunction( abstractFunction* rhs)
    {
        this->m_function = rhs;
    }
    
    void operation()
    {
        this->operation();
    }

    private:
    abstractFunction *m_function;
};