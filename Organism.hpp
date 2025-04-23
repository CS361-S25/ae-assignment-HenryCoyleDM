#ifndef ORG_H
#define ORG_H

#include "emp/math/Random.hpp"
#include "emp/tools/string_utils.hpp"

class Organism {

    public:
    double points = 0;

    public:
    Organism() : points(0) {}

    public:
    virtual std::string GetColor() {
        return "rgb(0, 0, 0)";
    }

    // process this organism
    public:
    virtual void Process() {
        std::cout << "Processed organism with " << std::to_string(points) << " points\n";
    }

    public:
    virtual std::string GetType() {
        return "Organism";
    }
};

#endif