#ifndef MAMMOTH
#define MAMMOTH

#include "emp/math/Random.hpp"
#include "emp/tools/string_utils.hpp"

#include "Organism.hpp"

class Mammoth : public Organism {

    public:
    Mammoth() : Organism() {
        points = 8;
    }

    public:
    void Process(emp::Random* random) {
        Organism::Process(random);
        points -= 0.2;
    }
    
    public:
    std::string GetColor() {
        return "rgb(255, 0, 0)";
    }

    public:
    std::string GetType() {
        return "Mammoth";
    }

    public:
    bool CanReproduce() {
        return points > 10;
    }

    public:
    Organism* Reproduce() {
        Organism* offspring = new Mammoth();
        points -= 10;
        return offspring;
    }

    /*
    A mammoth is allowed to move to the location of grass. If it does, it eats it and gets a point.
    */
    public:
    bool TryMoveToPlaceOfOrganism(Organism* organism_at_target) {
        std::cout << "Mammoth is trying to move\n";
        if (organism_at_target == nullptr) {
            return true;
        } else {
            bool is_grass = organism_at_target->GetType() == "Grass";
            if (is_grass) {
                points += 1;
                return true;
            } else {
                return false;
            }
        }
    }

    /*
    Mammoths die from starvation if their points drops below 0. Points drop by 0.2 every frame
    */
    public:
    bool IsDead() {
        return points < 0;
    }
};

#endif