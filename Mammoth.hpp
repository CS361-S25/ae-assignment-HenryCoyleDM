#ifndef MAMMOTH
#define MAMMOTH

#include "emp/math/Random.hpp"
#include "emp/tools/string_utils.hpp"

#include "Organism.hpp"

class Mammoth : public Organism {

    public:
    Mammoth() : Organism() {
        
    }
    
    public:
    std::string GetColor() {
        return "rgb(255, 0, 0)";
    }

    public:
    std::string GetType() {
        return "Mammoth";
    }
};

#endif