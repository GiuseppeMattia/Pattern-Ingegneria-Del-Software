#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*
    Si vuole creare un' applicazione che ordini un vettore in diversi modi
    usando il pattern del Metodo Template (Template Method)
*/

/*
    Classe astratta
*/

template <class T>
class Sort{
    protected:
        virtual bool compare(const T& a, const T& b) const = 0;
    public:
        void sort(vector<T>& v) const {
            for(int i = 0; i < v.size(); i++){
                for(int j = 0; j < v.size() - i - 1; j++){
                    if(!compare(v[j], v[j + 1]))
                        swap(v[j], v[j + 1]);
                }
            }
        }
};

/*
    Classe concreta
*/

class NumberSort: public Sort<int>{
    protected:
        bool compare(const int& a, const int& b) const override{
            return a < b;
        }
};

/*
    Classe concreta
*/

class StringSort: public Sort<string>{
    protected:
        bool compare(const string& a, const string& b) const override{
            if(a.length() == b.length())
                return a < b;
            return a.length() < b.length();
        }
};



template <class T>
void print(const vector<T> v){
    for(int i = 0; i < v.size(); i++){
        cout<<v[i];
        if(i != v.size() - 1){
            cout<<", ";
        }
    }
    cout<<endl;
}



int main(){
    vector<int> v1 = {5, 2, 3, 1, 3};
    vector<string> v2 = {"alpha", "no", "ape", "a", "boa"};

    cout<<"Prima dell'ordinamento: "<<endl;

    cout<<"v1: ";
    print(v1);

    cout<<"v2: ";
    print(v2);

    NumberSort s1;
    StringSort s2;

    s1.sort(v1);
    s2.sort(v2);

    cout<<"Dopo l'ordinamento: "<<endl;
    
    cout<<"v1: ";
    print(v1);

    cout<<"v2: ";
    print(v2);

    return 0;
}
