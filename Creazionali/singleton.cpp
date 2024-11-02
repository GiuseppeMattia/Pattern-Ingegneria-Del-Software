#include <iostream>

using namespace std;

/*
    Si vuole creare una calcolatrice usando il pattern del Singoletto (Singleton)
*/

/*
    Classe singleton
*/

class Calculator{
    private:
        Calculator(){};
        static Calculator* instance;
    public:
        static Calculator* getInstance(){
            if(instance == NULL){
                instance = new Calculator;
            }
            return instance;
        }

        Calculator(const Calculator& c) = delete;
        Calculator& operator=(const Calculator& c) = delete;

        double add(double a, double b){
            return a + b;
        }

        double subtract(double a, double b) const{
            return a - b;
        }

        double multiply(double a, double b) const{
            return a * b;
        }

        double divide(double a, double b){
            if(b == 0){
                throw invalid_argument("Impossibile dividere per zero");
            }

            return a / b;
        }
};

Calculator* Calculator::instance = NULL;

int main(){
    cout<<"1 + 2 = "<<Calculator::getInstance()->add(1, 2)<<endl;
    cout<<"1 - 2 = "<<Calculator::getInstance()->subtract(1, 2)<<endl;
    cout<<"1 * 2 = "<<Calculator::getInstance()->multiply(1, 2)<<endl;
    cout<<"1 / 2 = "<<Calculator::getInstance()->divide(1, 2)<<endl;

    try{
        cout<<"1 / 0 = "<<Calculator::getInstance()->divide(1, 0)<<endl;
    }
    catch(invalid_argument& e){
        cout<<"Impossibile dividere 1 e 0"<<endl;
    }

    return 0;
}