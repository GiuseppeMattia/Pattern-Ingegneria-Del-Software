#include <iostream>

using namespace std;

/*
    Si vuole creare un applicazione che, data in input un' espressione
    aritmetica, calcoli il risultato usando il pattern dell'Interprete (Interpreter)
*/

/*
    Espressione astratta
*/

class Expression{
    public:
        virtual int interpret() const = 0;
};

/*
    Espressione terminale
*/

class Number: public Expression{
    private:
        int n;
    public:
        Number(int num): n(num) {}

        int interpret() const override{
            return n;
        }
};

/*
    Espressione non terminale
*/

class Addition: public Expression{
    private:
        Expression* left;
        Expression* right;
    public:
        Addition(Expression* l, Expression* r) : left(l), right(r) {}

        int interpret() const override{
            return left->interpret() + right->interpret();
        }
};

/*
    Espressione non terminale
*/

class Subtraction: public Expression{
    private:
        Expression* left;
        Expression* right;
    public:
        Subtraction(Expression* l, Expression* r): left(l), right(r) {}

        int interpret() const override {
            return left->interpret() - right->interpret();
        }
};

/*
    Espressione non terminale
*/

class Multiplication: public Expression{
    private:
        Expression* left;
        Expression* right;
    public:
        Multiplication(Expression* l, Expression* r): left(l), right(r) {}

        int interpret() const override {
            return left->interpret() * right->interpret();
        }
};

/*
    Espressione non terminale
*/

class Division: public Expression{
    private:
        Expression* left;
        Expression* right;
    public:
        Division(Expression* l, Expression* r): left(l), right(r) {}

        int interpret() const override {
            if (right->interpret() == 0) {
                throw invalid_argument("Impossibile dividere per zero");
            }

            return left->interpret() / right->interpret();
        }
};

/*
    Contesto
*/

class Context{

};

int main(){
    //((5 + 7) * (12 - 10)) / 8
    Expression* e = new Division(
                        new Multiplication(
                                new Addition(new Number(5), new Number(7)),
                                new Subtraction(new Number(12), new Number(10))
                        ), new Number(8));

    cout<<e->interpret()<<endl;     // 3

    delete e;
    return 0;
}
