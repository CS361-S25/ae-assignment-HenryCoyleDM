#ifndef WORLD_H
#define WORLD_H

#include "emp/Evolve/World.hpp"
#include "emp/math/random_utils.hpp"
#include "emp/math/Random.hpp"

#include "Organism.h"

class MammothSteppe : public emp::World<Organism> {
    private:
    emp::Random* random;

    public:
    MammothSteppe(emp::Random* _random) : random(_random) {}
    
    public:
    void Update() {

    }
};

#endif