#include <iostream>
#include <string>

using namespace std;

/*
    Si vuole creare un' applicazione che permetta di configurare un automobile di diverse
    marche tramite l'utilizzo della Fabbrica Astratta (Abstract Factory)
*/

/*
    Prodotto astratto
*/

class Model{
    public:
        Model(){};
        virtual string getModel() const = 0;
};

/*
    Prodotto concreto
*/

class FiatModel: public Model{
    public:
        FiatModel(){};
        string getModel() const override{
            return "Panda 1000 FIRE";
        }
};

/*
    Prodotto concreto
*/

class LanciaModel: public Model{
    public:
        LanciaModel(){};
        string getModel() const override{
            return "Fulvia";
        }
};

/*
    Prodotto astratto
*/

class Engine{
    public:
        Engine(){};
        virtual string getEngine() const = 0;
};

/*
    Prodotto concreto
*/

class FiatEngine: public Engine{
    public:
        FiatEngine(){};
        string getEngine() const override{
            return "FIRE 1000";
        }
};

/*
    Prodotto concreto
*/

class LanciaEngine: public Engine{
    public:
        LanciaEngine(){};
        string getEngine() const override{
            return "V4";
        }
};

/*
    Fabbrica astratta
*/

class CarFactory{
    public:
        CarFactory(){};
        virtual Engine* createEngine() const = 0;
        virtual Model* createModel() const = 0;
};

/*
    Fabbrica concreta
*/

class FiatFactory: public CarFactory{
    public:
        FiatFactory(){};

        Model* createModel() const override{
            return new FiatModel;
        }

        Engine* createEngine() const override{
            return new FiatEngine;
        }
};

/*
    Fabbrica concreta
*/

class LanciaFactory: public CarFactory{
    public:
        LanciaFactory(){};

        Model* createModel() const override{
            return new LanciaModel;
        }

        Engine* createEngine() const override{
            return new LanciaEngine;
        }
};



void configureCar(const CarFactory* carFactory){
    Model* model = carFactory->createModel();
    Engine* engine = carFactory->createEngine();

    cout<<"Modello: "<<model->getModel()<<endl;
    cout<<"Motore: "<<engine->getEngine()<<endl;
}



int main(){
    CarFactory* fiat = new FiatFactory();
    CarFactory* lancia = new LanciaFactory();

    configureCar(fiat);
    cout<<endl;
    configureCar(lancia);

    delete fiat;
    delete lancia;
    return 0;
}