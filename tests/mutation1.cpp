#include <iostream>
#include <random>
#include <stree/stree.hpp>
#include <streegp/streegp.hpp>
#include "indiv.hpp"
#include "macros.hpp"

DEFUN_EMPTY(func);

int main() {
    static const unsigned PopulationSize = 10;
    static const unsigned InitMaxDepth = 5;
    static const float PTermGrow = 0.2;
    static const std::mt19937::result_type prng_seed = 1;
    static const unsigned mutation_subtree_depth = 3;
    static const float mutation_subtree_p_term = 0.2;
    static const float mutation_subtree_p_term_grow = 0.2;

    std::mt19937 prng(prng_seed);
    std::uniform_real_distribution<stree::Value> value_dist(-1, 1);

    stree::Environment env;
    env.add_function("+", 2, &::func);
    env.add_function("-", 2, &::func);
    env.add_function("*", 2, &::func);
    env.add_function("%", 2, &::func);
    env.add_positional("a", 0);
    env.add_positional("b", 1);
    env.add_positional("c", 2);

    // Create population
    Population pop_current = ramped_half_and_half(
        env, PopulationSize, InitMaxDepth, PTermGrow, prng, value_dist);

    // Create next population usin mutation only
    Population pop_next;
    while (pop_next.size() < pop_current.size()) {
        auto index = pop_next.size();
        pop_next.emplace_back(
            streegp::mutate_subtree(
                pop_current[index].tree(),
                mutation_subtree_depth,
                mutation_subtree_p_term,
                mutation_subtree_p_term_grow,
                prng,
                value_dist));
    }

    assert(pop_next.size() == pop_current.size());
    for (unsigned index = 0; index < pop_current.size(); ++index) {
        std::cout << "Original: " << pop_current[index].tree() << std::endl;
        std::cout << "Mutated : " << pop_next[index].tree() << std::endl;
        std::cout << std::endl;
    }
}
