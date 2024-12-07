#include <iostream>
#include <vector>

using namespace std;

/*
    Iteratore
*/

template <class T>
class Iterator {
public:
    virtual T First() = 0;
    virtual void Next() = 0;
    virtual bool isDone() = 0;
    virtual T current() = 0;
};

/*
    Aggregato
*/

template <class T>
class Aggregate {
public:
    virtual vector<T> getAggregate() const = 0;
    virtual void push(T el) = 0;
    virtual Iterator<T>* createIterator() = 0;
};

/*
    Iteratore concreto
*/

template <class T>
class ConcreteIterator : public Iterator<T> {
private:
    const Aggregate<T>& aggregate;
    int pos;

public:
    ConcreteIterator(const Aggregate<T>& agg) : aggregate(agg), pos(0) {}

    T First() override {
        return aggregate.getAggregate()[0];
    }

    void Next() override {
        if (pos < aggregate.getAggregate().size()) {
            pos++;
        }
    }

    bool isDone() override {
        return pos >= aggregate.getAggregate().size();
    }

    T current() override {
        if (!isDone()) {
            return aggregate.getAggregate()[pos];
        } else {
            throw out_of_range("Posizione non valida");
        }
    }
};

/*
    Aggregato concreto
*/

template <class T>
class ConcreteAggregate : public Aggregate<T> {
private:
    vector<T> v;

public:
    vector<T> getAggregate() const override {
        return v;
    }

    void push(T el) override {
        v.push_back(el);
    }

    Iterator<T>* createIterator() override {
        return new ConcreteIterator<T>(*this);
    }
};

int main() {
    ConcreteAggregate<int> v;

    v.push(5);
    v.push(4);

    Iterator<int>* it = v.createIterator();

    while (!it->isDone()) {
        cout<<it->current()<<endl;
        it->Next();
    }

    delete it;

    return 0;
}
