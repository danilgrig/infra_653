#include <iostream>
#include <string>
#include "animal.h"
#include "../animalfactory.h"

class TCat : public TAnimal {
public:
    TCat() {}
    TAnimal* Clone() {
        return new TCat;
    }
    void Say() const override {
        std::cout << "Meaw" << std::endl;
    }
};

REGISTER_ANIMAL("Cat", TCat);


