#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;

/*
    Si vuole creare un' applicazione che gestisca diversi circuiti di pagamento tramite un' unica
    interfaccia e utilizzando il pattern dell'Adattatore (Adapter)
*/

/*
    Obiettivo (Target)
*/

class Payment{
    public:
        virtual void processPayment(const double d) const = 0;
};

/*
    Adattato (Adaptee)
*/

class MasterCard{
    private:
        string number;
    public:
        MasterCard(string s){
            number = s;
        }

        void pay(const double d) const{
            sleep(3);   // Simula il tempo di processamento del pagamento
            cout<<"Pagati €"<<d<<" con circuito Mastercard"<<endl;
        }
};

/*
    Adattato (Adaptee)
*/

class Visa{
    private:
        string number;
    public:
        Visa(string s){
            number = s;
        }

        void pay(const double d) const{
            sleep(3);   // Simula il tempo di processamento del pagamento
            cout<<"Pagati €"<<d<<" con circuito Visa"<<endl;
        }
};

/*
    Adattatore
*/

class MasterCardAdapter: public Payment{
    private:
        MasterCard* mastercard;
    public:
        MasterCardAdapter(MasterCard* m): mastercard(m) {}
        
        void processPayment(const double d) const override{
            mastercard->pay(d);
        }
};

/*
    Adattatore
*/

class VisaAdapter: public Payment{
    private:
        Visa* visa;
    public:
        VisaAdapter(Visa* v): visa(v) {}

        void processPayment(const double d) const override{
            visa->pay(d);
        }
};

int main(){
    Payment* payment;
    int i;
    
    cout<<"Inserire 1 per pagare con circuito MasterCard, 2 per pagare con circuito Visa: ";
    cin>>i;

    if(i == 1){
        string s;
        
        cout<<"Inserire numero carta: ";
        cin>>s;

        MasterCard* mastercard = new MasterCard(s);
        payment = new MasterCardAdapter(mastercard);

        cout<<"Inserire l'importo: ";
        cin>>i;

        payment->processPayment(i);
    }
    else if(i == 2){
        string s;
        
        cout<<"Inserire numero carta: ";
        cin>>s;

        Visa* visa = new Visa(s);
        payment = new VisaAdapter(visa);

        cout<<"Inserire l'importo: ";
        cin>>i;

        payment->processPayment(i);
    }
    else{
        cout<<"Circuito non riconosciuto"<<endl;
    }

    return 0;
}