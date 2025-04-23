#ifndef TREE
#define TREE

#include "emp/math/Random.hpp"
#include "emp/tools/string_utils.hpp"

#include "Organism.hpp"
#include "MammothSteppe.hpp"

class Tree : public Organism {

    public:
    Tree() : Organism() {
        
    }
    
    public:
    std::string GetColor() {
        return "rgb(27, 52, 101)";
    }

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

    public:
    bool CanReproduce(emp::Random* random, Organism* organism_at_target) {
        bool target_is_bulldozable = organism_at_target == nullptr || organism_at_target->GetType() == "Grass";
        return target_is_bulldozable && points > random->GetDouble(10, 20);
    }

    public:
    Organism* Reproduce() {
        Organism* offspring = new Tree();
        points -= 15;
        return offspring;
    }
};

#endif