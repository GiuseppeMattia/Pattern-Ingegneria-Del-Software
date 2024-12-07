#include <iostream>
#include <unistd.h>

using namespace std;

/*
    Si vuole creare un' applicazione che permetta di chiamare un' ascensore
    usando il pattern dello Stato (State)
*/

/*
    Stato
*/

class State{
    public:
        virtual void move(int n) = 0;
        virtual void openDoors() const = 0;
        virtual void closeDoors() const = 0;
};

/*
    Contesto
*/

class Elevator{
    private:
        State* state;
    public:
        Elevator(){
            state = NULL;
        }

        void setState(State* s){
            state = s;
        }

        void move(int n) {
            state->move(n);
        }

        void openDoors() {
            state->openDoors();
        }

        void closeDoors(){
            state->closeDoors();
        }
};

/*
    Sottoclasse di stato concreta
*/

class MovingState: public State{
    private:
        Elevator* elevator;
    public:
        MovingState(Elevator* e): elevator(e) {}

        void move(int n) override{
            cout<<"L'ascensore è già in movimento"<<endl;
        }

        void openDoors() const override{
            cout<<"Impossibile aprire le porte quando l'ascensore è in movimento"<<endl;
        }

        void closeDoors() const override{
            cout<<"Porte già chiuse"<<endl;
        }
};

/*
    Sottoclasse di stato concreta
*/

class StillState: public State{
    private:
        Elevator* elevator;
    public:
        StillState(Elevator* e): elevator(e) {}

        void move(int n) override{
            this->closeDoors();
            elevator->setState(new MovingState(elevator));
            cout<<"Muovendosi verso il piano "<<n<<"..."<<endl;
            sleep(4 * n);   // Simula il movimento verso un piano
            elevator->setState(this);
            cout<<"Siete arrivati al piano "<<n<<endl;
            this->openDoors();
        }

        void openDoors() const override{
            cout<<"Aprendo le porte..."<<endl;
            sleep(0.5); //Simula un tempo di apertura delle porte
            cout<<"Porte aperte"<<endl;
        }

        void closeDoors() const override{
            cout<<"Chiudendo le porte..."<<endl;
            sleep(0.5); //Simula un tempo di chiusura delle porte
            cout<<"Porte chiuse"<<endl;
        }
};

int main(){
    Elevator* elevator = new Elevator();

    // Ascensore già chiamata
    elevator->setState(new MovingState(elevator));

    // Verifico che l'ascensore non faccia niente se in movimento
    elevator->move(0);
    elevator->openDoors();
    elevator->closeDoors();

    // L'ascensore arriva al mio piano
    elevator->setState(new StillState(elevator));

    // Cambio di piano
    elevator->move(1);

    delete elevator;
    return 0;
}
