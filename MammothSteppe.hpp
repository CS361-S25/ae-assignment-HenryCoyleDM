#ifndef WORLD_H
#define WORLD_H

#include "emp/Evolve/World.hpp"
#include "emp/math/random_utils.hpp"
#include "emp/math/Random.hpp"

#include "Organism.hpp"

class MammothSteppe : public emp::World<Organism> {
    private:
    emp::Random* random;

    public:
    MammothSteppe(emp::Random* _random) : random(_random) {}
    
    public:
    void Update() {
        emp::World<Organism>::Update();
        // process organisms
        emp::vector<size_t> schedule = emp::GetPermutation(*random, GetSize());
        for (size_t i : schedule) {
            if (!IsOccupied(i)) {
                continue;
            }
            pop[i]->Process();
        }
    }
};

#endif