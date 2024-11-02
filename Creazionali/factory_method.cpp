#include <iostream>

using namespace std;

/*
    Si vuole creare un' applicazione che stampi un istogramma tramite diversi caratteri
    usando il pattern del Metodo Fabbrica (Factory Method)
*/

/*
    Prodotto
*/

class Carattere{
    public:
        Carattere(){};
        virtual char getChar() const = 0;           
};   

/*
    Prodotto concreto
*/

class Asterisco: public Carattere{
    public:
        Asterisco(){};
        char getChar() const override{
            return '*';
        }
};

/*
    Prodotto concreto
*/

class Chiocciola: public Carattere{
    public:
        Chiocciola(){};
        char getChar() const override{
            return '@';
        }
};

/*
    Creatore (con implementazione di defalut)
*/

class Stampatore{
    public:
        Stampatore(){};

        virtual Carattere* getStampatore() const = 0;       // Metodo fabbrica

        void stampa (int* v, int n){
            for(int i = 0; i < n; i++){
                for (int j = 0; j < v[i]; j++){
                    cout<< this->getStampatore()->getChar();
                }
                cout<<endl;
            }
        }
};

/*
    Creatore concreto
*/

class StampatoreAsterischi: public Stampatore{
    public:
        StampatoreAsterischi(){};
        Carattere* getStampatore() const override{
            return new Asterisco;
        }
};

/*
    Creatore concreto
*/

class StampatoreChiocciola: public Stampatore{
    public:
        StampatoreChiocciola(){};
        Carattere* getStampatore() const override{
            return new Chiocciola;
        }
};

int main(){
    Stampatore* asterisco = new StampatoreAsterischi();
    Stampatore* chiocciola = new StampatoreChiocciola();

    int v[5] = {10, 4, 8, 3, 5};

    asterisco->stampa(v, 5);
    cout<<endl;
    chiocciola->stampa(v, 5);
	
    delete asterisco;
    delete chiocciola;
    return 0;
}
