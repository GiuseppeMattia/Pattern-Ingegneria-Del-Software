#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

/*
    Si vuole creare un' applicazione che permetta di configurare un' albero di Natale
    con diverse decorazioni usando il pattern del Peso Mosca (Flyweight)
*/

/*
    Flyweight
*/

class Decoration{
    public:
        virtual void display(const int x, const int y) const = 0;
};

/*
    Flyweight concreto
*/

class Ball: public Decoration{
    private:
        string color;
    public:
        Ball(string s): color(s) {}

        void display(const int x, const int y) const override{
            cout<<"Posizione: "<<x<<", "<<y<<"\t\t";
            cout<<"Colore della pallina: "<<color<<endl;
        }
};


/*
    Fabbrica di flyweight
*/

class DecorationFactory{
    private:
        unordered_map<string, Decoration*> decorations;
    public:
        Decoration* getDecoration(const string s){
            if(decorations.find(s) == decorations.end()){
                decorations[s] = new Ball(s);
            }
            
            return decorations[s];
        }
};

struct DecPos{
    Decoration* d;
    int x;
    int y;
};

class ChristmasTree{
    private:
        vector<DecPos*> decorationPos;
    public:
        void addDecoration(Decoration* d, int x, int y){
            DecPos* decPos = new DecPos;
            decPos->d = d;
            decPos->x = x;
            decPos->y = y;

            decorationPos.push_back(decPos);
        }     

        void display() const{
            cout<<"Le decorazioni sono: "<<endl;
            for(DecPos* d: decorationPos)
                d->d->display(d->x, d->y);
        }
};  

int main(){
    DecorationFactory* factory = new DecorationFactory();
    ChristmasTree* tree = new ChristmasTree();

    tree->addDecoration(factory->getDecoration("Rossa"), 1, 2);
    tree->addDecoration(factory->getDecoration("Gialla"), 3, 4);
    tree->addDecoration(factory->getDecoration("Blu"), 3, 5);
    tree->addDecoration(factory->getDecoration("Rossa"), 4, 5);

    tree->display();

    delete factory;
    delete tree;
    return 0;
}