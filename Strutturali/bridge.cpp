#include <iostream>
#include <fstream>

using namespace std;

/*
    Si vuole creare un' applicazione che crei diversi tipi di istogrammi
    stampati sul terminale e in un file usando il pattern del Ponte (Bridge)
*/

/*
    Implementatore
*/

class Writer{
    public:
        virtual void write(const char c) const = 0;
};

/*
    Implementatore concreto
*/

class ShellWriter: public Writer{
    public:
        void write(const char c) const override{
            cout<<c;
        }
};

/*
    Implementatore concreto
*/

class FileWriter: public Writer{
    public:
        void write(const char c) const override{
            ofstream file("bridge.txt", ios::app);

            if(file.is_open()){
                file<<c;
                file.close();
            }
            else{
                cout<<"Errore nell'aprire il file";
            }
        }
};

/*
    Astrazione
*/

class Histogram{
    public:
        virtual void display(const int v[], const int n) const = 0;
};

/*
    Astrazione ridefinita
*/

class AtHistogram: public Histogram{
    private:
        Writer* writer;
    public:
        AtHistogram(Writer* w): writer(w) {}

        void display(const int v[], const int n) const override{
            for(int i = 0; i < n; i++){
                for(int j = 0; j < v[i]; j++){
                    writer->write('@');
                }
                writer->write('\n');
            }
            writer->write('\n');
        }
};

/*
    Astrazione ridefinita
*/

class StarHistogram: public Histogram{
    private:
        Writer* writer;
    public:
        StarHistogram(Writer* w): writer(w) {}

        void display(const int v[], const int n) const override{
            for(int i = 0; i < n; i++){
                for(int j = 0; j < v[i]; j++){
                    writer->write('*');
                }
                writer->write('\n');
            }
        }
};

int main(){
    int v[5] = {10, 4, 8, 3, 5};

    ShellWriter* shellWriter = new ShellWriter();
    FileWriter* fileWriter = new FileWriter();

    AtHistogram* atHistogram;
    StarHistogram* starHistogram;

    // Shell
    atHistogram = new AtHistogram(shellWriter);
    starHistogram = new StarHistogram(shellWriter);

    atHistogram->display(v, 5);
    starHistogram->display(v , 5);

    //File
    atHistogram = new AtHistogram(fileWriter);
    starHistogram = new StarHistogram(fileWriter);

    atHistogram->display(v, 5);
    starHistogram->display(v , 5);

    return 0;
}