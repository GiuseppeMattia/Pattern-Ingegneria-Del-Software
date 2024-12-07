#include <iostream>

using namespace std;

/*
    Si vuole creare una calcolatrice usando il pattern della Strategia (Strategy)
*/

/*
    Strategia
*/

class Operation{
    public:
        virtual double compute(double a, double b) const = 0;
};

/*
    Strategia concreta
*/

class Addition: public Operation{
    public:
        virtual double compute(double a, double b) const override{
            return a + b;
        }
};

/*
    Strategia concreta
*/

class Subtraction: public Operation{
    public:
        virtual double compute(double a, double b) const override{
            return a - b;
        }
};

/*
    Strategia concreta
*/

class Multiplication: public Operation{
    public:
        virtual double compute(double a, double b) const override{
            return a * b;
        }
};

/*
    Strategia concreta
*/

class Division: public Operation{
    public:
        virtual double compute(double a, double b) const override{
            if(b == 0){
                throw invalid_argument("Impossibile dividere per zero");
            }

            return a / b;
        }
};


/*
    Contesto
*/

class Calculator{
    private:
        Operation* currentState;

    public:
        Calculator(){
            currentState = NULL;
        }

        void setState(Operation* o){
            currentState = o;
        }

        void compute(double a, double b){
            if(currentState){
                double c = currentState->compute(a, b);

                cout<<"Risultato: "<<c<<endl;
            }
        }
};

int main(){
    Calculator* calculator = new Calculator();
    
    Addition* addition = new Addition();
    Subtraction* subtraction = new Subtraction();
    Multiplication* multiplication = new Multiplication();
    Division* division = new Division();

    calculator->setState(addition);
    calculator->compute(4, 5);

    calculator->setState(subtraction);
    calculator->compute(4, 5);

    calculator->setState(multiplication);
    calculator->compute(4, 5);

    calculator->setState(division);
    calculator->compute(4, 5);

    try {
        calculator->compute(4, 0);
    } catch (const exception& e) {
        cout << "Errore: " << e.what() << endl;
    }

    delete addition;
    delete subtraction;
    delete multiplication;
    delete division;
    delete calculator;
    return 0;
}
