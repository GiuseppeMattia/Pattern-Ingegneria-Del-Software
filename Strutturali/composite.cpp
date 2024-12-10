#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
    Si vuole creare un' applicazione che permetta di configurare un albero
    di natale usando il pattern del Composito (Composite)
*/

/*
    Componente base
*/

class Decoration {
public:
    virtual ~Decoration() = default;

    virtual void display(int level = 0) const = 0;
    virtual void addComponent(Decoration* d) = 0;       //  Da scrivere nell'interfaccia, i nodi foglia ovviamente non lo useranno
    virtual void removeComponent(Decoration* d) = 0;    //  Da scrivere nell'interfaccia, i nodi foglia ovviamente non lo useranno
};

/*
    Foglia
*/

class FullBall : public Decoration {
private:
    const string color;

public:
    FullBall(const string& s) : color(s) {}

    void addComponent(Decoration* d) override{
        cout<<"Impossibile aggiungere componenti in un nodo foglia"<<endl;
    }

    void removeComponent(Decoration* d) override{
        cout<<"Impossibile rimuovere componenti in un nodo foglia"<<endl;
    }

    void display(int level = 0) const override {
        cout << string(level * 4, ' ') << "- Pallina piena, colore: " << color << endl;
    }
};

/*
    Composito
*/

class HollowBall : public Decoration {
private:
    vector<Decoration*> components;
    const string color;

public:
    HollowBall(const string& s) : color(s) {}

    void addComponent(Decoration* d) override{
        components.push_back(d);
    }

    void removeComponent(Decoration* d) override{
        auto it = find(components.begin(), components.end(), d);
        if (it != components.end()) {
            components.erase(it);
        }
    }

    void display(int level = 0) const override {
        cout << string(level * 4, ' ') << "+ Pallina cava, colore: " << color << endl;

        for (Decoration* component : components) {
            component->display(level + 1);
        }
    }
};

int main(){
    HollowBall* hollowball = new HollowBall("Rossa");

    HollowBall* hollow1 = new HollowBall("Blu");

    FullBall* b1 = new FullBall("Verde");
    
    FullBall* b2 = new FullBall("Gialla");

    b1->addComponent(b2);
    b1->removeComponent(b2);

    cout<<endl;

    hollowball->addComponent(hollow1);
    hollowball->addComponent(b1);

    hollow1->addComponent(b2);

    hollowball->display();


    delete b2;
    delete b1;
    delete hollow1;
    delete hollowball;
    return 0;
}
