#include <iostream>

using namespace std;

/*
    Si vuole creare un' applicazione che decori gli istogrammi ASCII
    usando il pattern del Decoratore (Decorator)
*/

/*
    Componente
*/

class Histogram{
    public:
        virtual void display(const int v[], const int n) const = 0;
};

/*
    Componente concreto
*/

class StarHisogram: public Histogram{
    public:
        void display(const int v[], const int n) const override{
            for(int i = 0; i < n; i++){
                for(int j = 0; j < v[i]; j++)
                    cout<<"*";
                cout<<endl;
            }
        }
};

/*
    Componente concreto
*/

class AtHistogram: public Histogram{
    public:
        void display(const int v[], const int n) const override{
            for(int i = 0; i < n; i++){
                for(int j = 0; j < v[i]; j++)
                    cout<<"@";
                cout<<endl;
            }
        }    
};

/*
    Decoratore
*/

class HistogramDecorator: public Histogram{
    protected:
        Histogram* histogram;
    public:
        HistogramDecorator() {}
        
        HistogramDecorator(Histogram* h){
            histogram = h;
        }

        virtual void display(const int v[], const int n) const override{
            histogram->display(v, n);
        }
};


int trovaMassimo(const int v[], const int n){
    int massimo = v[0];
    for(int i = 1; i < n; i++)
        if(v[i] > massimo)
            massimo = v[i];

    return massimo;
}

/*
    Decoratore concreto
*/

class BorderDecorator: public HistogramDecorator{
    private:
        int width;
    public:
        BorderDecorator(Histogram* h, int w): HistogramDecorator(h), width(w) {}

        void display(const int v[], const int n){
            string border = "#";
            int m = trovaMassimo(v, n);

            for(int i = 0; i <= m; i++)
                border += "#";

            for(int i = 0; i < width; i++)
                cout<<border<<endl;

            histogram->display(v, n);

            for(int i = 0; i < width; i++)
                cout<<border<<endl;
        }
};  

int main(){
    int v[5] = {10, 4, 8, 3, 5};
 
    StarHisogram* starHistogram = new StarHisogram();
    AtHistogram* atHistogram = new AtHistogram();
    
    BorderDecorator* b1 = new BorderDecorator(starHistogram, 2);
    BorderDecorator* b2 = new BorderDecorator(atHistogram, 2);
    

    b1->display(v, 5);

    cout<<endl;

    b2->display(v, 5);

    delete starHistogram;
    delete atHistogram;
    delete b1;
    delete b2;
    return 0;
}