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

    Population population = stree::gp::ramped_half_and_half(context);
    for (const auto& indiv : population) {
        std::cout << indiv.tree() << std::endl;
    }
    std::cout << std::endl;

    return 0;
}
