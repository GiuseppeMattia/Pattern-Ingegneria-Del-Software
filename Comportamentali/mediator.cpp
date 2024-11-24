#include <iostream>
#include <string>

using namespace std;

/*
    Si vuole creare un' applicazione che permetta di comunicare tra più
    utenti usando il pattern del Mediatore (Mediator)
*/

class User;

/*
    Mediatore
*/

class Mediator{
    public:
        virtual void send(const string& s, const User* u1, const User* u2) const = 0;
};

/*
    Classe collega
*/

class User{
    private:
        Mediator* mediator;
        string name;
    public:
        User(string s, Mediator* m): name(s), mediator(m) {}

        void sendMessage(const string& s, const User* u) const{
            cout<<name<<" invia un messaggio a "<<u->name<<": "<<s<<endl;
            mediator->send(s, this, u);
        }

        void receive(const string& s, const User* u) const{
            cout<<name<<" riceve un messaggio da "<<u->name<<": "<<s<<endl;
        }
};

/*
    Mediatore concreto
*/

class ChatMediator: public Mediator{
    public:
        void send(const string& s, const User* u1, const User* u2) const override{
            u2->receive(s, u1);
        }
};



int main(){
    Mediator* mediator = new ChatMediator();

    User* u1 = new User("Alice", mediator);
    User* u2 = new User("Bob", mediator);

    u1->sendMessage("Ciao, come stai?", u2);

    delete u2;
    delete u1;
    delete mediator;
    return 0;
}
