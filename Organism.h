#ifndef ORG_H
#define ORG_H

#include "emp/math/Random.hpp"
#include "emp/tools/string_utils.hpp"

class Organism {

    public:
    virtual std::string GetColor() {
        std::cout << "GetColor of superclass called" << std::endl;
        return emp::ColorRGB(0, 0, 0);
    }
};

#endif