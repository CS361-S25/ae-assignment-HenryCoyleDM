#ifndef GRASS
#define GRASS

#include "emp/math/Random.hpp"
#include "emp/tools/string_utils.hpp"

#include "Organism.hpp"
#include "MammothSteppe.hpp"

class Grass : public Organism {

    public:
    Grass() : Organism() {

    }
    
    public:
    std::string GetColor() {
        return "rgb(0, 255, 0)";
    }

    public:
    void Process() {
        Organism::Process();
        std::cout << "Grass is processed\n";
        points += 1;
    }

    public:
    std::string GetType() {
        return "Grass";
    }
};

#endif