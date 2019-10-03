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

    std::mt19937 prng(prng_seed);
    std::uniform_real_distribution<stree::Value> value_dist(-1, 1);

    stree::Environment env;
    env.add_function("+", 2, &func);
    env.add_function("-", 2, &func);
    env.add_function("*", 2, &func);
    env.add_function("%", 2, &func);
    env.add_positional("a", 0);
    env.add_positional("b", 1);
    env.add_positional("c", 2);

    // Create population using generated values
    Population population1 = ramped_half_and_half(
        env, PopulationSize, InitMaxDepth, PTermGrow, prng, value_dist);

    // Print population trees
    std::cout << "Population 1, using generated values" << std::endl;
    for (const auto indiv : population1) {
        std::cout << indiv.tree() << std::endl;
    }
    std::cout << std::endl;


    // Create population with no generated values
    Population population2 = ramped_half_and_half(
        env, PopulationSize, InitMaxDepth, PTermGrow, prng);

    // Print population trees
    std::cout << "Population 2, no generated values" << std::endl;
    for (const auto indiv : population2) {
        std::cout << indiv.tree() << std::endl;
    }
    std::cout << std::endl;

    return 0;
}
