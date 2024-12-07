#include <iostream>

using namespace std;

/*
    Si vuole creare un' applicazione che crei un sistema di controllo
    domotico usando il pattern del Comando (Command)
*/

/*
    Comando
*/

class Command{
    public:
        virtual void execute() = 0;
};

/*
    Ricevitore
*/

class Lights{
    private:
        bool on;
    public:
        Lights(){
            on = false;
        }

        void turnOn() {
            on = true;
            cout<<"Luci accese"<<endl;
        }

        void turnOff(){
            on = false;
            cout<<"Luci spente"<<endl;
        }
};

/*
    Ricevitore
*/

class AirConditioner{
    private:
        int temperature;
    public:
        AirConditioner(){
            temperature = 0;
        }

        void increaseTemperature() {
            temperature++;
            cout<<"Temperatura aumentata da "<<temperature - 1<<" a "<<temperature<<endl;
        }

        void decreaseTemperature() {
            temperature--;
            cout<<"Temperatura diminuita da "<<temperature + 1<<" a "<<temperature<<endl;
        }
};

/*
    Comando concreto
*/

class LightsOn: public Command{
    private:
        Lights* lights;
    public:
        LightsOn(Lights* l): lights(l) {}

        void execute() override{
            lights->turnOn();
        }
};

/*
    Comando concreto
*/

class LightsOff: public Command{
    private:
        Lights* lights;
    public:
        LightsOff(Lights* l): lights(l) {}

        void execute() override{
            lights->turnOff();
        }
};

/*
    Comando concreto
*/

class Increase: public Command{
    private:
        AirConditioner* airConditioner;
    public:
        Increase(AirConditioner* a): airConditioner(a) {}

        void execute() override{
            airConditioner->increaseTemperature();
        }
};

/*
    Comando concreto
*/

class Decrease: public Command{
    private:
        AirConditioner* airConditioner;
    public:
        Decrease(AirConditioner* a): airConditioner(a) {}

        void execute() override{
            airConditioner->decreaseTemperature();
        }
};

/*
    Invocatore
*/

class Remote{
    private:
        Command* command;
    public:
        void setCommand(Command* c){
            command = c;
        }

        void executeCommand(){
            command->execute();
        }
};

int main(){
    Lights* lights = new Lights();
    AirConditioner* airConditioner = new AirConditioner();

    Command* lightsOn = new LightsOn(lights);
    Command* lightsOff = new LightsOff(lights);
    Command* increase = new Increase(airConditioner);
    Command* decrease = new Decrease(airConditioner);

    Remote* remote = new Remote();

    int n;
    cout<<"Inserisci 1 per dare un comando alle luci o 2 per darlo al condizionatore: ";
    cin>>n;
    
    if(n == 1){
        cout<<"Inserisci 1 per accendere le luci, 2 per spegnerle: ";
        cin>>n;
        
        if(n == 1){
            remote->setCommand(lightsOn);
            remote->executeCommand();
        }
        else if(n == 2){
            remote->setCommand(lightsOff);
            remote->executeCommand();
        }
        else{
            cout<<"Comando non riconosciuto"<<endl;
        }
    }
    else if(n == 2){
        cout<<"Inserisci 1 per aumentare la temperatura, 2 per abbassarla: ";
        cin>>n;
        
        if(n == 1){
            remote->setCommand(increase);
            remote->executeCommand();
        }
        else if(n == 2){
            remote->setCommand(decrease);
            remote->executeCommand();
        }
        else{
            cout<<"Comando non riconosciuto"<<endl;
        }
    }
    else{
        cout<<"Dispositivo non riconosciuto"<<endl;
    }

    delete decrease;
    delete increase;
    delete lightsOff;
    delete lightsOn;
    delete airConditioner;
    delete lights;
    delete remote;
    return 0;
}
