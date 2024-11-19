#include <iostream>
#include <string>

using namespace std;

/*
    Si vuole creare un' applicazione che permetta di eseguire pagamenti contactless
    usando il pattern del Sostituto (Proxy)
*/

/*
    Soggetto
*/

class Payment{
    public:
        virtual void pay(const double d) = 0;
};

/*
    Soggetto reale
*/

class Bank: public Payment{
    private:
        double balance;
    public:
        Bank(double d): balance(d) {}

        void pay(const double d) override{
            if(balance >= d){
                balance -= d;
                cout<<"Pagati €"<<d<<endl;
            }
            else{
                cout<<"Credito insufficiente"<<endl;
            }
        }
};

/*
    Proxy
*/

class CreditCard: public Payment{
    private:
        Bank* bank;
    public:
        CreditCard(Bank* b): bank(new Bank(*b)) {}

        void pay(const double d) override{
            bank->pay(d);
        } 
};

int main(){
    Bank bank(200);

    CreditCard creditCard(&bank);

    cout<<"Acquisto un prodotto per 150 euro"<<endl;
    creditCard.pay(150);

    cout<<"Acquisto di nuovo lo stesso prodotto"<<endl;
    creditCard.pay(150);

    return 0;
}