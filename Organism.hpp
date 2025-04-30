#ifndef ORG_H
#define ORG_H

#include "emp/math/Random.hpp"
#include "emp/tools/string_utils.hpp"

/*
Base class for species of organisms in the population. Points is a common field for determining how ready the organism is for reproduction.
Most methods are virtual so that derived classes (species) can add unique functionality. Organism methods are frequently passed a Random by
the world for flexibility with derived classes.
*/
class Organism {

    public:
    double points = 0;
    int age = 0;
    // prevents organisms from moving twice in one generation
    bool has_moved_this_generation;

    public:
    Organism() : points(0), age(0) {}

    /*
    Default color for organisms is black, this shouldn't be visible in the GUI since subclasses override it
    */
    public:
    virtual std::string GetColor() {
        return "rgb(0, 0, 0)";
    }

    /*
    All organisms track their age and whether they moved this generation. Process is called for each organism at the beginning
    of the world update procedure
    */
    public:
    virtual void Process(emp::Random* random) {
        // std::cout << "Processed organism with " << std::to_string(points) << " points\n";
        age++;
        has_moved_this_generation = false;
    }

    /*
    Gets a string representing which species this organism is
    */
    public:
    virtual std::string GetType() {
        return "Organism";
    }

    /*
    Whether the organism is able to create an offspring in an adjacent cell currently occupied by organism_at_target
    */
    public:
    virtual bool CanReproduce(emp::Random* random, Organism* organism_at_target) {
        return false;
    }

    /*
    Get a new organism of the same type and pay reproduction costs
    */
    public:
    virtual Organism* Reproduce() {
        Organism* offspring = new Organism();
        return offspring;
    }

    /*
    Whether the organism can move to an adjacent cell currently occupied by organism_at_target. This is necessesary to
    allow mammoths to move to where grass is and eat it
    */
    public:
    virtual bool CanMoveToPlaceOfOrganism(Organism* organism_at_target, emp::Random* random) {
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