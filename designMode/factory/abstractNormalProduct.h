

class abstractNormalProduct
{
    private:

    public:
    abstractNormalProduct(){}

    ~abstractNormalProduct(){}
};


class normalProduct1 : public abstractNormalProduct
{
    private:

    public:

    normalProduct1(){}

    ~normalProduct1(){}
};

class normalProduct2 : public abstractNormalProduct
{
private:
    /* data */
public:
    normalProduct2(/* args */);
    ~normalProduct2();
};

normalProduct2::normalProduct2(/* args */)
{
}

normalProduct2::~normalProduct2()
{
}
