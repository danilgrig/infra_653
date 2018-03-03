#include <iostream>

using namespace std;

class TAnimal {
public:
    void Say() {
        cout << GetValue() << endl;
    }
    virtual string GetValue() = 0;
};

class TCat : public TAnimal {
public:
    string GetValue() override {
        return "Cat";
    }
};

class TDog : public TAnimal {
public:
    string GetValue() override {
        return "Dog";
    }
};

int main() {
    int *x = new int;
    free(x);
    free(x);
    TCat c;
    c.Say();
}