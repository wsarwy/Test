#include <string>
using namespace std;

class AbstractPrototype
{
public:
    AbstractPrototype(){}
    ~AbstractPrototype(){}

    virtual AbstractPrototype* clone() = 0;

    virtual void initial() = 0;

private:
};