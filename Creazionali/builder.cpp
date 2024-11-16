#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
    Si vuole creare un' applicazione che permetta di configuraer panini personalizzati
    usando il pattern del Costruttore (Builder)
*/

/*
    Prodotto
*/

class Sandwich{
    private:
        vector<string> ingredients;
    public:
        Sandwich(){}
        void addIngredient(const string& s){
            ingredients.push_back(s);
        }

        void display() const{
            cout<<"Ingredienti del panino: "<<endl;
            for(string s: ingredients)
                cout<<s<<endl;
        }
};

/*
    Builder
*/

class SandwichBuilder{
    public:
        virtual void addBreadLoaf() const = 0;
        virtual void addMeat(const string& s) const = 0;
        virtual void addCheese(const string& s) const = 0;
        virtual void addVegetable(const string& s) const = 0;
        virtual void addCondiment(const string& s) const = 0;
        virtual void getSandwich() const = 0;
};

/*
    Builder concreto
*/

class GlutenFreeSandwichBuilder: public SandwichBuilder{
    private:
        Sandwich* sandwich;
    public:
        GlutenFreeSandwichBuilder() {
            sandwich = new Sandwich();
        }
        
        void addBreadLoaf() const override{
            sandwich->addIngredient("Fetta di pane senza glutine");
        }

        void addMeat(const string& s) const override{
            sandwich->addIngredient(s);
        }

        void addCheese(const string& s) const override{
            sandwich->addIngredient(s);
        }

        void addVegetable(const string& s) const override{
            sandwich->addIngredient(s);
        }

        void addCondiment(const string& s) const override{
            sandwich->addIngredient(s);
        }

        void getSandwich() const override{
            sandwich->display();
        }
};


/*
    Builder concreto
*/

class GlutenSandwichBuilder: public SandwichBuilder{
    private:
        Sandwich* sandwich;
    public:
        GlutenSandwichBuilder(){
            sandwich = new Sandwich();
        }

        void addBreadLoaf() const override{
            sandwich->addIngredient("Fetta di pane");
        }

        void addMeat(const string& s) const override{
            sandwich->addIngredient(s);
        }

        void addCheese(const string& s) const override{
            sandwich->addIngredient(s);
        }

        void addVegetable(const string& s) const override{
            sandwich->addIngredient(s);
        }

        void addCondiment(const string& s) const override{
            sandwich->addIngredient(s);
        }

        void getSandwich() const override{
            sandwich->display();
        }
};

/*
    Direttore
*/

class Director{
    private:
        SandwichBuilder* builder;
    public:
        void setBuilder(SandwichBuilder* b){
            builder = b;
        }

        void buildSimpleSandwich(){
            builder->addBreadLoaf();
            builder->addMeat("Mortadella");
            builder->addBreadLoaf();
        }

        void buildCompleteSandwich(){
            builder->addBreadLoaf();
            builder->addMeat("Mortadella");
            builder->addCheese("Burrata");
            builder->addVegetable("Pomodori secchi");
            builder->addVegetable("Olive");
            builder->addBreadLoaf();
        }

        void getSandwich(){
            builder->getSandwich();
        }
};

int main(){
    Director d;
    int n;
    cout<<"Inserire 1 per fare panini per celiaci, 2 per fare panini con glutine: ";
    cin>>n;
    if(n == 1){
        d.setBuilder(new GlutenFreeSandwichBuilder);
        cout<<"Inserire 1 per un panino semplice, 2 per un panino completo: ";
        cin>>n;
        if(n == 1){
            d.buildSimpleSandwich();
            d.getSandwich();
        }
        else if(n == 2){
            d.buildCompleteSandwich();
            d.getSandwich();
        }
        else{
            cout<<"Opzione non riconosciuta"<<endl;
        }
    }
    else if(n == 2){
        d.setBuilder(new GlutenSandwichBuilder);
        cout<<"Inserire 1 per un panino semplice, 2 per un panino completo: ";
        cin>>n;
        if(n == 1){
            d.buildSimpleSandwich();
            d.getSandwich();
        }
        else if(n == 2){
            d.buildCompleteSandwich();
            d.getSandwich();
        }
        else{
            cout<<"Opzione non riconosciuta"<<endl;
        }
    }
    else{
        cout<<"Opzione non riconosciuta"<<endl;
    }

    return 0;
}