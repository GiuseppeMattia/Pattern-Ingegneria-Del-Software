#include <iostream>
#include <string>

using namespace std;

/*
    Si vuole creare un' applicazione che permetta di configurare un albero di Natale
    con diverse decorazioni usando il pattern del Prototipo (Prototype)
*/

/*
    Prototipo
*/

class Decoration{
    public:
        virtual Decoration* clone() const = 0;

        virtual void display() const = 0;
};

/*
    Prototipo concreto
*/

class Lights: public Decoration{
    private:
        string color;
    public:
        Lights(const string& c): color(c) {}

        Decoration* clone() const override{
            return new Lights(*this);
        }

        void display() const override{
            cout<<"Colore delle luci: "<<color<<endl;
        }       
};

/*
    Prototipo concreto
*/

class Balls: public Decoration{
    private:
        string color;
    public:
        Balls(const string& c): color(c) {}

        Decoration* clone() const override{
            return new Balls(*this);
        }

        void display() const override{
            cout<<"Colore delle palline: "<<color<<endl;
        }
};

/*
    Fabbrica dei prototipi
*/

class TreeFactory{
    private:
        Decoration* lights;
        Decoration* balls;
    public:
        TreeFactory(Decoration* l, Decoration* b){
            lights = l;
            balls = b;
        }

        Decoration* createLights() const{
            return lights->clone();
        }

        Decoration* createBalls() const{
            return balls->clone();
        }   

        void displayTree() const{
            lights->display();
            balls->display();
        }
};


int main(){
    TreeFactory* treeFactory1 = new TreeFactory(new Lights("Gialle"), new Balls("Rosse"));
    treeFactory1->displayTree();

    cout<<endl;

    TreeFactory* treeFactory2 = new TreeFactory(treeFactory1->createLights(), new Balls("Blu"));
    treeFactory2->displayTree();

    delete treeFactory1;
    delete treeFactory2;
    return 0;
}