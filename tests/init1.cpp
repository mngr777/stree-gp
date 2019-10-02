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

    stree::Environment env;
    env.add_function("+", 2, &func);
    env.add_function("-", 2, &func);
    env.add_function("*", 2, &func);
    env.add_function("%", 2, &func);
    env.add_positional("a", 0);
    env.add_positional("b", 1);
    env.add_positional("c", 2);

    Population population;
    {
        unsigned i = 0;
        // grow
        for (; i < PopulationSize / 2; ++i)
            population.emplace_back(
                streegp::grow(env, InitMaxDepth, prng, PTermGrow));
        // full
        for (; i < PopulationSize; ++i)
            population.emplace_back(
                streegp::full(env, InitMaxDepth, prng));
    }

    // Print population trees
    for (const auto indiv : population) {
        std::cout << indiv.tree() << std::endl;
    }

    return 0;
}
