#include <string>
#include <iostream>
using namespace std;

class Color
{
    public:
    virtual void showColor(string pen, string name) = 0;
};

class Red : public Color
{
    void showColor(string pen, string name)
    {
        cout<< pen <<" red "<< name <<"."<<endl;
    }
};

class Green : public Color
{
    void showColor(string pen, string name)
    {
        cout<< pen << " green "<<name<<"."<<endl;
    }
};

class Shape
{
    public:
    virtual void show() = 0;
    
    void setColor(Color* rhs)
    {
        this->m_color = rhs;
    }

    protected:
    Color* m_color;
};

class Triangle : public Shape
{
    public:
    void show()
    {
        this->m_color->showColor("big pen", "triangle");
        cout<<" paint special triangle success"<<endl;
    }
};

class Rectangle : public Shape
{
    public:
    void show()
    {
        this->m_color->showColor("small pen", "rectangle");
        cout<<" paint special rectangle success"<<endl;
    }
};
