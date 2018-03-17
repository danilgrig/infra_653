#include <iostream>
#include <vector>

#include "animalfactory.h"
#include "animals/animal.h"

using namespace std;

int main() {
    vector<TAnimal*> zoo;
    auto& f = TAnimalFactory::GetFactory();
    zoo.push_back(f.GetAnimal("Cat"));
    zoo.push_back(f.GetAnimal("Dog"));
    zoo.push_back(f.GetAnimal("Cat"));

    for (const auto& a : zoo) {
        a->Say();
    }
}
