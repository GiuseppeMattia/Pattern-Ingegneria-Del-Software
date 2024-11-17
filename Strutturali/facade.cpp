#include <iostream>
#include <unistd.h>

using namespace std;

/*
    Si vuole creare un' applicazione che permetta di accendere una macchina
    utilizzando il pattern della Facciata (Facade) 
*/

/*
    Classe sottosistema
*/

class Engine{
    public:
        void start() const{
            cout<<"Motore in accensione..."<<endl;
            sleep(3);
            cout<<"Motore acceso"<<endl;
        }
};

/*
    Classe sottosistema
*/

class Lights{
    public:
        void start() const{
            cout<<"Luci in accensione..."<<endl;
            sleep(1);
            cout<<"Luci accese"<<endl;
        }
};

/*
    Classe sottosistema
*/

class Radio{
    public:
        void start() const{
            cout<<"Radio in accensione"<<endl;
            sleep(1);
            cout<<"Radio accesa"<<endl;
        }
};

/*
    Facciata
*/

class Car{
    private:
        Engine* engine;
        Lights* lights;
        Radio* radio;
    public:
        Car(){
            engine = new Engine();
            lights = new Lights();
            radio = new Radio();
        }

        void start() const{
            cout<<"Accendendo la macchina..."<<endl;
            engine->start();
            lights->start();
            radio->start();
            cout<<"Macchina accesa"<<endl;
        }
};

int main(){
    Car* car = new Car();

    car->start();

    delete car;
    return 0;
}