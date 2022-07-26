#include <string>
using namespace std;

class abstractProduct
{
private:
    /* data */    
    string property1;
    int serial;
    string company;
public:
    abstractProduct(/* args */){}
    ~abstractProduct(){}


};

//---------------------------------------------------------------//

class abstractProduct1 : public abstractProduct
{
private:
    /* data */
public:
    abstractProduct1(/* args */){}
    ~abstractProduct1(){}

    string country;
};


//------------------------------------------------------------//

class abstractProduct2 : public abstractProduct
{
private:
    /* data */
public:
    abstractProduct2(/* args */){}
    ~abstractProduct2(){}
};



