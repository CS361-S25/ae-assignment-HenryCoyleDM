#ifndef GRASS
#define GRASS

#include "emp/math/Random.hpp"
#include "emp/tools/string_utils.hpp"

#include "Organism.hpp"
#include "MammothSteppe.hpp"

/*
Grass is a type of organism in the MammothSteppe. It does not move and reproduces quickly next to old grass. It is eaten by mammoths
and can be taken over by trees
*/
class Grass : public Organism {

    public:
    Grass() : Organism() {

    }
    
    /*
    Grass is green
    */
    public:
    std::string GetColor() {
        return "rgb(0, 255, 0)";
    }

    /*
    Points correspond to how close the grass is to reproducing, it accumulates points at a random rate each frame
    */
    public:
    void Process(emp::Random* random) {
        Organism::Process(random);
        // std::cout << "Grass is processed\n";
        points += random->GetDouble();
    }

    public:
    std::string GetType() {
        return "Grass";
    }

    /*
    Grass can reproduce into an empty square if it has accumulated over 1.5 points (about 3 frames)
    */
    public:
    bool CanReproduce(emp::Random* random, Organism* organism_at_target) {
        return organism_at_target == nullptr && points > 1.5;
    }

    /*
    Creates a new grass object as offspring with 0 points, spends this grass's points as a reproduction cost
    */
    public:
    Organism* Reproduce() {
        Organism* offspring = new Grass();
        points -= 1.5;
        return offspring;
    }
};

#endif