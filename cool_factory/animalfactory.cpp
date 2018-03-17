#include "animalfactory.h"

bool TAnimalFactory::RegisterAnimal(const string& type, TAnimal* animal) {
    animals[type] = animal;
    return true;
}

TAnimal* TAnimalFactory::GetAnimal(const string& type) {
    return animals[type]->Clone();
}
