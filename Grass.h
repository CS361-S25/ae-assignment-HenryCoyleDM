#ifndef GRASS
#define GRASS

#include "emp/math/Random.hpp"
#include "emp/tools/string_utils.hpp"

#include "Organism.h"

class Grass : public Organism {

    public:
    Grass(MammothSteppe* _world, size_t _position, emp::Random* _random) : Organism(_world, _position, _random) {

    }
    
    public:
    std::string GetColor() {
        return emp::ColorRGB(0, 255, 0);
    }

    public:
    void Process() {
        Organism::Process();
        std::cout << "Grass is processed";
        points += random->GetDouble(0, 1);
    }
};

#endif