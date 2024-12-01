#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
    Si vuole creare un' applicazione che permetta di configurare un albero di Natale
    e che permetta di ripristinare qualche modifica fatta a questo usando il pattern
    del Ricordo (Memento)
*/

/*
    Memento
*/

class Memento{
    private:
        string lightsMemento;
        string ballsMemento;
    public:
        Memento(string l, string b): lightsMemento(l), ballsMemento(b) {}

        string getLightsState() const {
            return lightsMemento;
        }

        string getBallsState() const{
            return ballsMemento;
        }
};

/*
    Ideatore 
*/

class TreeOriginator{
    private:
        string lights;
        string balls;
    public:
        TreeOriginator(string l, string b): lights(l), balls(b) {}

        void setLights(string s){
            lights = s;
        }

        void setBalls(string s){
            balls = s;
        }

        void display() const {
            cout<<"Colore delle luci: "<<lights<<endl;
            cout<<"Colore delle palline: "<<balls<<endl;
        }

        Memento* save() const {
            return new Memento(lights, balls);
        }

        void restore(Memento* m) {
            lights = m->getLightsState();
            balls = m->getBallsState();
        }
};

/*
    Custode
*/

class TreeCareTaker{
    private:
        vector<Memento*> mementi;
        TreeOriginator* tree;
    public:
        TreeCareTaker(TreeOriginator* t): tree(t) {}

        void saveState() {
            cout<<"Salvo lo stato..."<<endl;
            mementi.push_back(tree->save());
        }

        void undo(){
            if(mementi.size() == 0){
                cout<<"Nessuna modifica effettuata"<<endl;
                return;
            }
            
            cout<<"Facendo l'undo..."<<endl;
            tree->restore(mementi.at(mementi.size() - 2));
            mementi.pop_back();
        }
};

int main(){
    TreeOriginator* tree = new TreeOriginator("Gialle", "Rosse");
    TreeCareTaker* treeCaretaker = new TreeCareTaker(tree);

    treeCaretaker->undo();
    cout<<endl;

    treeCaretaker->saveState();
    tree->display();
    cout<<endl;

    tree->setLights("Blu");
    treeCaretaker->saveState();
    tree->display();
    cout<<endl;

    tree->setBalls("Verdi");
    treeCaretaker->saveState();
    tree->display();
    cout<<endl;

    treeCaretaker->undo();
    tree->display();
    cout<<endl;

    delete treeCaretaker;
    delete tree;
    return 0;
}
