#include <cassert>
#include <iostream>
#include <random>
#include <stree/stree.hpp>
#include <streegp/streegp.hpp>
#include "macros.hpp"

DEFUN_EMPTY(func);

int main() {
    using Individual = stree::gp::Individual;
    using Population = stree::gp::Population<Individual>;

    const std::mt19937::result_type prng_seed = 1;

    // Random
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

    // Context
    auto config = stree::gp::make_config();
    auto context = stree::gp::make_context<Individual>(
        config,
        env,
        [](Individual& individual) { return 0.0; },
        prng,
        value_dist);

    unsigned PopulationSize = config.get<unsigned>(stree::gp::conf::PopulationSize);
    // Subtree mutation
    unsigned MutationSubtreeNum = PopulationSize / 3;
    // Point mutation
    unsigned MutationPointNum = PopulationSize / 3;
    // Hoist mutation
    unsigned MutationHoistNum = PopulationSize
        - (MutationSubtreeNum + MutationPointNum);

    // Create population
    Population pop_current = stree::gp::ramped_half_and_half(context);

    // Create next population using mutation only
    Population pop_next;
    {
        Population::size_type index = 0;
        Population::size_type max_index = 0;

        // Subtree mutation
        max_index += MutationSubtreeNum;
        for (; index < max_index; ++index) {
            pop_next.emplace_back(
                stree::gp::mutate_subtree(context, pop_current[index]));

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
                stree::gp::mutate_point(context, pop_current[index]));

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
                stree::gp::mutate_hoist(context, pop_current[index]));

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
