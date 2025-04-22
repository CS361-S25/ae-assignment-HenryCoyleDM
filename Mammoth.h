#ifndef MAMMOTH
#define MAMMOTH

#include "emp/math/Random.hpp"
#include "emp/tools/string_utils.hpp"

#include "Organism.h"

class Mammoth : public Organism {

    public:
    Mammoth(MammothSteppe* _world, size_t _position, emp::Random* _random) : Organism(_world, _position, _random) {
        
    }
    
    public:
    std::string GetColor() {
        return emp::ColorRGB(255, 0, 0);
    }
};

#endif