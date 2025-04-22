#ifndef ORG_H
#define ORG_H

#include "emp/math/Random.hpp"
#include "emp/tools/string_utils.hpp"

// forward declaration
class MammothSteppe;

class Organism {

    public:
    double points = 0;
    emp::Random* random;
    size_t position;

    public:
    MammothSteppe* world;

    public:
    Organism(MammothSteppe* _world, size_t _position, emp::Random* _random);

    public:
    virtual std::string GetColor();

    // process this organism
    public:
    virtual void Process();

    // kill this organism
    public:
    void Die();
};

#endif