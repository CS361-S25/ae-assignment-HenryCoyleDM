#ifndef GRASS
#define GRASS

#include "emp/math/Random.hpp"
#include "emp/tools/string_utils.hpp"

#include "Organism.h"

class Grass : public Organism {

    public:
    std::string GetColor() {
        std::cout << "GetColor of Grass called" << std::endl;
        return emp::ColorRGB(0, 255, 0);
    }
};

#endif