#include "Organism.h"
#include "MammothSteppe.h"
#include "emp/math/Random.hpp"
#include "emp/tools/string_utils.hpp"
#include "color_map.hpp"

Organism::Organism(MammothSteppe* _world, size_t _position, emp::Random* _random) : world(_world), position(_position), random(_random) {}

std::string Organism::GetColor() {
    return emp::ColorRGB(0, 0, 0);
}

void Organism::Process() {
    std::cout << "Processed organism with " << std::to_string(points) << " points\n";
    if (points < 0) {
        Die();
    }
}

void Organism::Die() {
    std::cout << "Organism died\n";
    world->RemoveOrgAt(position);
}