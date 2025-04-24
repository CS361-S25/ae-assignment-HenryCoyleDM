#ifndef MAMMOTH
#define MAMMOTH

#include "emp/math/Random.hpp"
#include "emp/tools/string_utils.hpp"

#include "Organism.hpp"

/*
Mammoths are an organism in the Mammoth Steppe ecosystem. They wander around, eating grass they stumble accross for energy.
They also trample trees. When they eat enough grass, they reproduce a new mammoth, and when they don't eat enough grass, they
die from starvation.
*/
class Mammoth : public Organism {

    /*
    Mammoths start with enough energy to survive for a bit in case there isn't grass nearby at the start
    */
    public:
    Mammoth() : Organism() {
        points = 2;
    }

    /*
    Spend 0.2 points per frame (0=death)
    */
    public:
    void Process(emp::Random* random) {
        Organism::Process(random);
        points -= 0.2;
    }
    
    /*
    Mammoths are a dark red color
    */
    public:
    std::string GetColor() {
        return "rgb(109, 41, 27)";
    }

    public:
    std::string GetType() {
        return "Mammoth";
    }

    /*
    Mammoths can reproduce into a square with grass or an empty square. They must accumulate at least 10 points
    */
    public:
    bool CanReproduce(emp::Random* random, Organism* organism_at_target) {
        bool target_is_bulldozable = organism_at_target == nullptr || organism_at_target->GetType() == "Grass";
        return target_is_bulldozable && points > 10;
    }

    /*
    Creates a new Mammoth as the offspring. Spends 10 points as a reproduction cost
    */
    public:
    Organism* Reproduce() {
        Organism* offspring = new Mammoth();
        points -= 10;
        return offspring;
    }

    /*
    A mammoth is allowed to move to the location of grass. If it does, it eats it and gets a point. 33% of the time, it is also allowed to
    move into an area with a tree, trampling it
    */
    public:
    bool CanMoveToPlaceOfOrganism(Organism* organism_at_target, emp::Random* random) {
        // don't allow mammoths to move twice in one frame
        if (has_moved_this_generation) {
            return false;
        }
        if (organism_at_target == nullptr) {
            // mammoths are allowed to move to an empty square
            return true;
        } else {
            std::string organism_at_target_type = organism_at_target->GetType();
            if (organism_at_target_type == "Grass") {
                // move to a square with grass and eat it
                points += 1;
                return true;
            } else if (organism_at_target_type == "Tree") {
                // there is a tree at the target location, 33% chance to successfully trample it
                return random->GetDouble() < 0.33;
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