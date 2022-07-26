#include "abstractPrototype.h"

class ConcretePrototype : public AbstractPrototype
{
public:
    ConcretePrototype(){}
    ~ConcretePrototype(){}

    ConcretePrototype(const ConcretePrototype& rhs) 
    {
        this->number = rhs.number;
        this->serial = rhs.serial;
        this->str = rhs.str;
    }

    ConcretePrototype* clone()
    {
        return new ConcretePrototype(*this);
    }

    void initial()
    {
        this->number = 0;
        this->serial = 0;
        this->str = "1";
    }

private:
    int number;
    double serial;
    string str;

};

class ConcretePrototypeB : public AbstractPrototype
{
    public:
    ConcretePrototypeB(){}
    ~ConcretePrototypeB()
    {

    }

    ConcretePrototypeB(const ConcretePrototypeB& rhs)
    {
        this->differ = rhs.differ;
        this->strCount = rhs.strCount;
        this->str = new char(this->strCount);
        for (int i = 0; i < this->strCount; i++)
        {
            this->str[i] = rhs.str[i];
        }
    }

    void initial()
    {
        this->differ = "1";
        this->strCount = 1;
    }

    ConcretePrototypeB* clone()
    {
        return new ConcretePrototypeB(*this);
    }

    void setDiffer(string str) { this->differ = str;}
    void setStr(char* str) { this->str = str;}
    void setStrCount(int value) { this->strCount = value;}

    


    private:
    string differ;
    char* str;
    int strCount;

};