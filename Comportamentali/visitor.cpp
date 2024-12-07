#include <iostream>
#include <vector>

using namespace std;

/*
    Si vuole creare un' applicazione che permetta di implementare operazioni su delle
    forme geometriche usando il pattern del Visiatore (Visitor)
*/

class Circle;
class Square;

/*
    Visitatore
*/

class Visitor{
    public:
        virtual void visit(Circle* c) const = 0;
        virtual void visit(Square* s) const = 0;
};

/*
    Elemento
*/

class Shape{
    public:
        virtual void accept(Visitor* v) = 0;
};

/*
    Elemento concreto
*/

class Circle: public Shape{
    private:
        double radius;
    public:
        Circle(double d){
            radius = d;
        }

        double getRadius() const{
            return radius;
        }
        
        void accept(Visitor* v) override{
            v->visit(this);
        }
};

/*
    Elemento concreto
*/

class Square: public Shape{
    private:
        double side;
    public:
        Square(double d){
            side = d;
        }

        double getSide() const{
            return side;
        }
        void accept(Visitor* v) override{
            v->visit(this);
        }
};

/*
    Visitatore concreto
*/

class AreaVisitor: public Visitor{
    public:
        void visit(Circle* c) const override{
            double r = c->getRadius();
            cout<<"Area del cerchio: "<<3.1415 * r * r<<endl;
        }

        void visit(Square* s) const override{
            double r = s->getSide();
            cout<<"Area del quadrato: "<<r * r<<endl;
        }
};

/*
    Visitatore concreto
*/

class SideVisitor: public Visitor{
    public:
        void visit(Circle* c) const override{
            double r = c->getRadius();
            cout<<"Raggio del cerchio: "<<r<<endl;
        }

        void visit(Square* s) const override{
            double r = s->getSide();
            cout<<"Lato del quadrato: "<<r<<endl;
        }
};

/*
    Struttura dell'oggetto
*/

class ShapeCollection{
    private:
        vector<Shape*> shapes;
    public:
        void addShape(Shape* s) {
            shapes.push_back(s);
        }

        void visit(Visitor* v){
            for(Shape* s: shapes)
                s->accept(v);
        }
};

int main(){
    ShapeCollection* shapeCollection = new ShapeCollection();

    shapeCollection->addShape(new Circle(5));
    shapeCollection->addShape(new Square(4));

    AreaVisitor* areaVisitor = new AreaVisitor();
    SideVisitor* sideVisitor = new SideVisitor();

    shapeCollection->visit(areaVisitor);

    cout<<endl;

    shapeCollection->visit(sideVisitor);

    delete sideVisitor;
    delete areaVisitor;
    delete shapeCollection;
    return 0;
}