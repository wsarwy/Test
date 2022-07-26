#include <string>
using namespace std;

class  Product
{
private:
    /* data */
    string property1;
    string property2;
    string property3;

public:
    Product(/* args */);
    ~Product();

    void setProperty1(string str) { this->property1 = str;}
    void setProperty2(string str) { this->property2 = str;}
    void setProperty3(string str) { this->property3 = str;}
};

 Product:: Product(/* args */)
{
    // this->property1 = "property1";
    // this->property2 = "property2";
    // this->property3 = "property3";
}

 Product::~ Product()
{
}
