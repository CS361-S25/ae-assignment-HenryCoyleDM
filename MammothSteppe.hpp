#ifndef WORLD_H
#define WORLD_H

#include "emp/Evolve/World.hpp"
#include "emp/math/random_utils.hpp"
#include "emp/math/Random.hpp"

#include "Organism.hpp"

class MammothSteppe : public emp::World<Organism> {
    private:
    emp::Random* random;

    public:
    MammothSteppe(emp::Random* _random) : random(_random) {}
    
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

    private:
    void KillOrganismAt(int index) {
        RemoveOrgAt(index);
    }

    /*
    Process reproduction for all organisms. If an organism can reproduce, it tries to
    */
    private:
    void ReproduceAllOrganisms() {
        emp::vector<size_t> schedule = emp::GetPermutation(*random, GetSize());
        for (size_t i : schedule) {
            if (!IsOccupied(i)) {
                continue;
            }
            bool can_reproduce = pop[i]->CanReproduce();
            if (can_reproduce) {
                ReproduceOrganismAt(i);
            }
        }
    }

    /*
    Reproduce the organism at location index. Chooses a random adjacent cell, and if it is empty, creates an offspring and places it there
    */
    private:
    void ReproduceOrganismAt(int index) {
        emp::WorldPosition offspring_position = GetRandomNeighborPos(index);
        if (!IsOccupied(offspring_position)) {
            Organism* offspring = pop[index]->Reproduce();
            AddOrgAt(offspring, offspring_position);
        }
    }

    private:
    void MoveAllOrganisms() {
        emp::vector<size_t> schedule = emp::GetPermutation(*random, GetSize());
        for (size_t i : schedule) {
            if (!IsOccupied(i)) {
                continue;
            }
            std::cout << "Trying to move organism at " << std::to_string(i) << ".\n";
            emp::WorldPosition target_position = GetRandomNeighborPos(i);
            emp::Ptr<Organism> organism_at_target = GetOrgPtr(target_position.GetIndex());
            bool organism_is_moving = pop[i]->TryMoveToPlaceOfOrganism(organism_at_target);
            if (organism_is_moving) {
                MoveOrganism(i, target_position.GetIndex());
            }
        }
    }

    private:
    void MoveOrganism(int source_position, int target_position) {
        std::cout << "Moving organism from " << std::to_string(source_position) << " to " << std::to_string(target_position) << ".\n";
        emp::Ptr<Organism> organism_at_source = GetOrgPtr(source_position);
        // remove the organism without deleting it
        pop[source_position] = nullptr;
        RemoveOrgAt(target_position);
        organism_at_source->has_moved_this_generation = true;
        AddOrgAt(organism_at_source, target_position);
    }
};

#endif