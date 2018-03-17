#pragma once

#include <map>
#include <string>
#include "animals/animal.h"

using namespace std;

#define REGISTER_ANIMAL(TYPE, CLASS)                  \
namespace {                                           \
    CLASS animal;                                     \
    TAnimalFactory& f = TAnimalFactory::GetFactory(); \
    bool b = f.RegisterAnimal(TYPE, &animal);         \
}

class TAnimalFactory {
private:
    map<string, TAnimal*> animals;
    TAnimalFactory() {};
    TAnimalFactory& operator=(const TAnimalFactory&) {};
public:
    static TAnimalFactory& GetFactory() {
        static TAnimalFactory factory;
        return factory;
    }
    bool RegisterAnimal(const string& type, TAnimal* animal);
    TAnimal* GetAnimal(const string& type);
};