#pragma once

class TAnimal {
public:
    virtual TAnimal* Clone() = 0;
    virtual void Say() const = 0;
};