#include <iostream>

using namespace std;

class TAnimal {
public:
    int mass, x;
    TAnimal() {
        mass = 10;
    }
    void Say() {
        cout << GetValue() << " " << mass << endl;
    }
    bool IsEnoughScores() {
        return 1 > 2;
    }
    virtual string GetValue() const = 0;
};

class TCat : public TAnimal {
public:
    string GetValue() const override  {
        string s = "Cat";
        return s + s;
    }
};

class TDog : public TAnimal {
public:
    string GetValue() const override {
        return "Dog";
    }
};

class NoValue : public exception {
public:
    string what() {
        return "No such value";
    }
};

class UnknownAnimal : public exception {
public:
    string what() {
        return "UnknownAnimal";
    }
};

TAnimal* GetAnimal(const string& type) {
    if (type == "Cat") {
        return new TCat();
    } else if (type == "Dog") {
        return new TDog();
    } else {
        throw UnknownAnimal();
    }
}

int main() {
    TAnimal *zoo[10];
    zoo[0] = GetAnimal("Cat");
    zoo[1] = GetAnimal("Dog");

    for (int i = 0; i < 2; i++) {
        zoo[i]->Say();
    }
}