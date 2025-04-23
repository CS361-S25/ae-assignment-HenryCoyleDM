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
        return "rgb(109, 41, 27)";
    }

    public:
    std::string GetType() {
        return "Mammoth";
    }

    public:
    bool CanReproduce(emp::Random* random, Organism* organism_at_target) {
        bool target_is_bulldozable = organism_at_target == nullptr || organism_at_target->GetType() == "Grass";
        return target_is_bulldozable && points > 10;
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
    bool TryMoveToPlaceOfOrganism(Organism* organism_at_target, emp::Random* random) {
        if (has_moved_this_generation) {
            return false;
        }
        // std::cout << "Mammoth is trying to move\n";
        if (organism_at_target == nullptr) {
            return true;
        } else {
            std::string organism_at_target_type = organism_at_target->GetType();
            if (organism_at_target_type == "Grass") {
                points += 1;
                return true;
            } else if (organism_at_target_type == "Tree") {
                if (random->GetDouble() < 0.2) {
                    if (points < 2) {
                        // sustain the mammoths for a bit longer while they're trampling forests
                        points += 0.1;
                    }
                    return true;
                } else {
                    return false;
                }
                return random->GetDouble() < 0.2;
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