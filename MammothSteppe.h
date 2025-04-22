#ifndef WORLD_H
#define WORLD_H

#include "emp/Evolve/World.hpp"
#include "emp/math/random_utils.hpp"
#include "emp/math/Random.hpp"

class Organism;

class MammothSteppe : public emp::World<Organism> {
    private:
    emp::Random* random;

    public:
    MammothSteppe(emp::Random* _random);
    
    public:
    void Update();
};

#endif