#include <iostream>

using namespace std;

/*
На подобии архитектуры классов Animal, Cat, Dog придумать и реализовать классы Department, FMBF, FOPF, итп.
Продумать какой может быть интерфейс у Department, какие функции могут быть переопределены у наследников.
Программа принимает на вход 3 числа, баллы его по трем предметам.
Создает по экземпляру класса каждого из факультетов, по очереди опрашивает факультеты, хотят ли они принять абитуриента с такими баллами.
*/

class TAnimal {
public:
    int mass, x;
    TAnimal() {
        mass = 10;
    }
    void Say() {
        cout << GetValue() << " " << mass << endl;
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
