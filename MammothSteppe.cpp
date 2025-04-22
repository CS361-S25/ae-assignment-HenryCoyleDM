#include "Organism.h"
#include "MammothSteppe.h"
#include "emp/math/Random.hpp"
#include "emp/tools/string_utils.hpp"

MammothSteppe::MammothSteppe(emp::Random* _random) : random(_random) {}

void MammothSteppe::Update() {
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