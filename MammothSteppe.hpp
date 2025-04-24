#ifndef WORLD_H
#define WORLD_H

#include "emp/Evolve/World.hpp"
#include "emp/math/random_utils.hpp"
#include "emp/math/Random.hpp"

#include "Organism.hpp"

/*
MammothSteppe is an ecosystem simulation that inherits from Empirical's World. It contains mammoths, grass, and trees. Each time it is
updated, it processes all organisms in the world to handle energy, death, movement, and reproduction
*/
class MammothSteppe : public emp::World<Organism> {
    // a random number generator to pass to organisms
    private:
    emp::Random* random;

    public:
    MammothSteppe(emp::Random* _random) : random(_random) {}
    
    /*
    A frame consists of 4 steps: processing organisms, killing organisms that died, reproducing organisms, and moving organisms
    */
    public:
    void Update() {
        emp::World<Organism>::Update();
        ProcessAllOrganisms();
        KillAllOrganisms();
        ReproduceAllOrganisms();
        MoveAllOrganisms();
    }

    /*
    Run the Process method off all organisms in the population
    */
    private:
    void ProcessAllOrganisms() {
        emp::vector<size_t> schedule = emp::GetPermutation(*random, GetSize());
        for (size_t i : schedule) {
            if (!IsOccupied(i)) {
                continue;
            }
            pop[i]->Process(random);
        }
    }

    /*
    Determine if each organism is dead this frame using its IsDead method. Kill those organisms.
    */
    private:
    void KillAllOrganisms() {
        emp::vector<size_t> schedule = emp::GetPermutation(*random, GetSize());
        for (size_t i : schedule) {
            if (!IsOccupied(i)) {
                continue;
            }
            bool organism_is_dead = pop[i]->IsDead();
            if (organism_is_dead) {
                KillOrganismAt(i);
            }
        }
    }

    /*
    Removes the organism from the location index
    */
    private:
    void KillOrganismAt(int index) {
        RemoveOrgAt(index);
    }

    /*
    Tries to reproduce each organism
    */
    private:
    void ReproduceAllOrganisms() {
        emp::vector<size_t> schedule = emp::GetPermutation(*random, GetSize());
        for (size_t i : schedule) {
            if (!IsOccupied(i)) {
                continue;
            }
            TryReproduceOrganismAt(i);
        }
    }

    /*
    Reproduce the organism at location index. It chooses a random adjacent cell and asks the Organism if it is allowed to reproduce
    an offspring into that cell. If it does, it creates that offspring and puts it in that cell
    */
    private:
    void TryReproduceOrganismAt(int index) {
        emp::WorldPosition offspring_position = GetRandomNeighborPos(index);
        emp::Ptr<Organism> organism_at_target = GetOrgPtr(offspring_position.GetIndex());
        bool can_reproduce = pop[index]->CanReproduce(random, organism_at_target);
        if (can_reproduce) {
            ReproduceOrganismTo(index, offspring_position.GetIndex());
        }
    }

    /*
    Assuming the organism can reproduce, gets an offspring of the organism at source_position and puts it in
    target_position, overwriting the organism there
    */
    private:
    void ReproduceOrganismTo(int source_position, int target_position) {
        emp::Ptr<Organism> organism_at_source = GetOrgPtr(source_position);
        Organism* offspring = organism_at_source->Reproduce();
        RemoveOrgAt(target_position);
        AddOrgAt(offspring, target_position);
    }

    /*
    For each organism, gets an adjacent cell that is can try to move to this frame. It asks the organism if it is allowed to move to
    that cell, and if it is, it moves it
    */
    private:
    void MoveAllOrganisms() {
        emp::vector<size_t> schedule = emp::GetPermutation(*random, GetSize());
        for (size_t i : schedule) {
            if (!IsOccupied(i)) {
                continue;
            }
            emp::WorldPosition target_position = GetRandomNeighborPos(i);
            emp::Ptr<Organism> organism_at_target = GetOrgPtr(target_position.GetIndex());
            bool organism_is_moving = pop[i]->CanMoveToPlaceOfOrganism(organism_at_target, random);
            if (organism_is_moving) {
                MoveOrganism(i, target_position.GetIndex());
            }
        }
    }

    /*
    Moves the organism from source_position to target_position, leaving a nullptr behind and removing the organism previously at the destination
    */
    private:
    void MoveOrganism(int source_position, int target_position) {
        // std::cout << "Moving organism from " << std::to_string(source_position) << " to " << std::to_string(target_position) << ".\n";
        emp::Ptr<Organism> organism_at_source = GetOrgPtr(source_position);
        // remove the organism without deleting it
        pop[source_position] = nullptr;
        RemoveOrgAt(target_position);
        organism_at_source->has_moved_this_generation = true;
        AddOrgAt(organism_at_source, target_position);
    }
};

#endif