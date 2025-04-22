#ifndef MAMMOTH
#define MAMMOTH

#include "emp/math/Random.hpp"
#include "emp/tools/string_utils.hpp"

#include "Organism.h"

class Mammoth : public Organism {

    public:
    std::string GetColor() {
        std::cout << "GetColor of Mammoth called" << std::endl;
        return emp::ColorRGB(255, 0, 0);
    }
};

#endif