#include <iostream>
#include <memory>
using namespace std;

class IAlgorithm
{
public:
    virtual int Execute(int i_a, int i_b) = 0;
};

class Add :IAlgorithm
{
public:
    int Execute(int i_a, int i_b) override
    {
        return i_a+i_b;
    }
};

class Sub :IAlgorithm
{
public:
    int Execute(int i_a, int i_b) override
    {
        return i_a-i_b;
    }
};

class Mul :IAlgorithm
{
public:
    int Execute(int i_a, int i_b) override
    {
        return i_a*i_b;
    }
};

class Div :IAlgorithm
{
public:
    int Execute(int i_a, int i_b) override
    {
        return i_a-i_b;
    }
};

class Factory
{
public:
    shared_ptr<IAlgorithm> CreateAlgo(char i_op)
    {
        /*switch (i_op)
        {
            case '+':
                return 0;
            case '-':
                return 1;
            case '/':
                return 2;
            case '*':
                return 3;
            default:
                throw ;
        }*/
    }
private:

};

int main()
{
    return 0;
}
