#include <iostream>
#include <string>

using namespace std;

/*
    Si vuole creare un' applicazione che permetta di scegliere di stampare un documento
    in bianco e nero o a colori utilizzando il pattern della Catena di Responsabilità
    (Chain of Responsibility)
*/

enum class AnsiCode {
    Black = 30,
    Red = 31,
    Green = 32,
    Yellow = 33,
    Blue = 34,
    Magenta = 35,
    Cyan = 36,
    White = 37,
    Default = 39,
};

string ansi(AnsiCode code) {
    return "\033[" + std::to_string(static_cast<int>(code)) + "m";
}

/*
    Gestore
*/

class Printer{
    public:
        virtual void setHandler(Printer* p) = 0;
        virtual void handle(const string& s) = 0;
};

/*
    Gestore concreto
*/

class BlackAndWhitePrinter: public Printer{
    private:
        Printer* next;
        bool usable;
        string me;

        void setUsable(bool b){
            usable = b;
        }
    public:
        BlackAndWhitePrinter(int c){
            next = NULL;
            me = "Bianco&Nero" + to_string(c);
        }

        void setHandler(Printer* p) override{
            next = p;
        }

        void handle(const string& s) override{
            if(next == NULL)
                cout<<ansi(AnsiCode::Default)<<"La stampante "<<me<<" stampa il messaggio in bianco e nero: "<<s<<endl;
            else
                next->handle(s);
        }
};

/*
    Gestore concreto
*/

class ColorPrinter: public Printer{
    private:
        Printer* next;
        string me;
        AnsiCode code;
    public:
        ColorPrinter(int c){
            next = NULL;
            me = "Colore" + to_string(c);
        }

        void setHandler(Printer* p) override{
            next = p;
        }

        void setColor(AnsiCode c){
            code = c;
        }

        void handle(const string& s) override{
            if(next == NULL){
                cout<<ansi(AnsiCode::Default)<<"La stampante "<<me<<" stampa il messaggio a colori: ";
                cout<<ansi(code)<<s<<endl;
            }
            else
                next->handle(s);
        }
};

int main(){
    ColorPrinter* color1 = new ColorPrinter(1);
    ColorPrinter* color2 = new ColorPrinter(2);

    color1->setColor(AnsiCode::Green);
    color2->setColor(AnsiCode::Red);

    color1->setHandler(color2);

    BlackAndWhitePrinter* bw1 = new BlackAndWhitePrinter(1);
    BlackAndWhitePrinter* bw2 = new BlackAndWhitePrinter(2);

    bw1->setHandler(bw2);

    string message = "Sto stampando";

    color1->handle(message);

    bw1->handle(message);

    delete color2;
    delete color1;
    delete bw2;
    delete bw1;
}
