#ifndef TREE
#define TREE

#include "emp/math/Random.hpp"
#include "emp/tools/string_utils.hpp"

#include "Organism.hpp"
#include "MammothSteppe.hpp"

/*
Trees are a species of organism in the mammoth steppe. They reproduce slowly but don't die naturally. They provide no energy to
mammoths and take over land that grass could have used. Thankfully, mammoths can trample them.
*/
class Tree : public Organism {

    public:
    Tree() : Organism() {
        
    }
    
    /*
    Trees are a dark greenish blue
    */
    public:
    std::string GetColor() {
        return "rgb(27, 52, 101)";
    }

    /*
    Trees accumulate a random amount of points each frame
    */
    public:
    void Process(emp::Random* random) {
        Organism::Process(random);
        // std::cout << "Tree is processed\n";
        points += random->GetDouble();
    }

    public:
    std::string GetType() {
        return "Tree";
    }

    /*
    Trees are allowed to reproduce to where a grass already is, taking it over. They start with a low
    chance of reproducing when they have 10 points (about 20 frames), increasing to a certain chance when
    they have 20 points (about 40 frames)
    */
    public:
    bool CanReproduce(emp::Random* random, Organism* organism_at_target) {
        bool target_is_bulldozable = organism_at_target == nullptr || organism_at_target->GetType() == "Grass";
        return target_is_bulldozable && points > random->GetDouble(10, 20);
    }

    /*
    Creates a new tree and pays reproduction costs
    */
    public:
    Organism* Reproduce() {
        Organism* offspring = new Tree();
        points -= 15;
        return offspring;
    }
};

#endif