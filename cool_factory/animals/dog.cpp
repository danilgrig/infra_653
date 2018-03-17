#include <iostream>
#include <string>
#include "animal.h"
#include "../animalfactory.h"

class TDog : public TAnimal {
public:
    TDog() {}
    TAnimal* Clone() {
        return new TDog;
    }
    void Say() const {
        std::cout << "Gaw" << std::endl;
    }
};

REGISTER_ANIMAL("Dog", TDog);