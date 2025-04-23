#ifndef ORG_H
#define ORG_H

#include "emp/math/Random.hpp"
#include "emp/tools/string_utils.hpp"

class Organism {

    public:
    double points = 0;
    int age = 0;
    // prevents organisms from moving twice in one generation
    bool has_moved_this_generation;

    public:
    Organism() : points(0), age(0) {}

    public:
    virtual std::string GetColor() {
        return "rgb(0, 0, 0)";
    }

    // process this organism
    public:
    virtual void Process(emp::Random* random) {
        std::cout << "Processed organism with " << std::to_string(points) << " points\n";
        age++;
        has_moved_this_generation = false;
    }

    public:
    virtual std::string GetType() {
        return "Organism";
    }

    public:
    virtual bool CanReproduce(emp::Random* random, Organism* organism_at_target) {
        return false;
    }

    public:
    virtual Organism* Reproduce() {
        Organism* offspring = new Organism();
        return offspring;
    }

    /*
    Input: pointer to an organism that neighbors this one
    Output: whether this organism moves to that position
    */
    public:
    virtual bool TryMoveToPlaceOfOrganism(Organism* organism_at_target, emp::Random* random) {
        return false;
    }

    /*
    Whether the organism should die this frame
    */
    public:
    virtual bool IsDead() {
        return false;
    }
};

#endif