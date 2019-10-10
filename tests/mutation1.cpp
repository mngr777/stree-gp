#include <cassert>
#include <iostream>
#include <random>
#include <stree/stree.hpp>
#include <streegp/streegp.hpp>
#include "macros.hpp"

DEFUN_EMPTY(func);

int main() {
    // Initialization
    const unsigned PopulationSize = 30;
    const unsigned InitMaxDepth = 5;
    const float PTermGrow = 0.2;
    const std::mt19937::result_type prng_seed = 1;

    // Subtree mutation
    const unsigned MutationSubtreeNum = PopulationSize / 3;
    const unsigned MutationSubtreeDepth = 3;
    const float MutationSubtreePTerm = 0.2;
    const float MutationSubtreePTermGrow = 0.2;

    // Point mutation
    const unsigned MutationPointNum = PopulationSize / 3;
    const unsigned MutationPointPTerm = 0.2;

    // Hoist mutation
    const unsigned MutationHoistNum = PopulationSize
        - (MutationSubtreeNum + MutationPointNum);
    const unsigned MutationHoistPTerm = 0.2;

    // PRNG
    std::mt19937 prng(prng_seed);
    std::uniform_real_distribution<stree::Value> value_dist(-1, 1);

    // Init environment
    stree::Environment env;
    env.add_function("+", 2, &::func);
    env.add_function("-", 2, &::func);
    env.add_function("*", 2, &::func);
    env.add_function("%", 2, &::func);
    env.add_positional("a", 0);
    env.add_positional("b", 1);
    env.add_positional("c", 2);

    using Individual = streegp::Individual;
    using Population = streegp::Population<Individual>;

    // Create population
    Population pop_current = streegp::ramped_half_and_half<Individual>(
        env, PopulationSize, InitMaxDepth, PTermGrow, prng, value_dist);

    // Create next population using mutation only
    Population pop_next;
    {
        Population::size_type index = 0;
        Population::size_type max_index = 0;

        // Subtree mutation
        max_index += MutationSubtreeNum;
        for (; index < max_index; ++index) {
            pop_next.emplace_back(
                streegp::mutate_subtree(
                    pop_current[index].tree(),
                    MutationSubtreeDepth,
                    MutationSubtreePTerm,
                    MutationSubtreePTermGrow,
                    prng,
                    value_dist));

            // Print trees
            std::cout << "Original:          "
                      << pop_current[index].tree()
                      << std::endl;
            std::cout << "Mutated (subtree): "
                      << pop_next[index].tree()
                      << std::endl;
        }

        // Point mutation
        max_index += MutationPointNum;
        for (; index < max_index; ++index) {
            pop_next.emplace_back(
                streegp::mutate_point(
                    pop_current[index].tree(),
                    MutationPointPTerm,
                    prng,
                    value_dist));

            // Print trees
            std::cout << "Original:          "
                      << pop_current[index].tree()
                      << std::endl;
            std::cout << "Mutated (point):   "
                      << pop_next[index].tree()
                      << std::endl;
        }

        // Hoist mutation
        max_index += MutationHoistNum;
        assert(max_index == pop_current.size());
        for (; index < max_index; ++index) {
            pop_next.emplace_back(
                streegp::mutate_hoist(
                    pop_current[index].tree(),
                    MutationHoistPTerm,
                    prng));

            // Print trees
            std::cout << "Original:          "
                      << pop_current[index].tree()
                      << std::endl;
            std::cout << "Mutated (hoist):   "
                      << pop_next[index].tree()
                      << std::endl;
        }
    }

    assert(pop_next.size() == pop_current.size());
    return 0;
}
