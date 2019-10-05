#include <cmath>
#include <iostream>
#include <random>
#include <utility>
#include <stree/stree.hpp>
#include <streegp/streegp.hpp>
#include "indiv.hpp"
#include "macros.hpp"

template<typename I>
streegp::Fitness evaluate(I& indiv) {
    stree::Value error = 0.0;
    for (stree::Value a = -10; a <= 10; ++a) {
        stree::Params params{a};
        stree::Value result = stree::eval(indiv.tree(), params);
        stree::Value answer = a * a - 2 * a + 1; // a^2 - 2a + 1;
        error += std::fabs(result - answer);
    }
    return error;
}

template<typename I>
streegp::Fitness fitness(I& indiv) {
    if (!indiv.has_fitness()) {
        indiv.set_fitness(evaluate(indiv));
    }
    return indiv.fitness();
}

DEFUN_EMPTY(func)

int main() {
    static const unsigned PopulationSize = 20;
    static const unsigned InitMaxDepth = 5;
    static const float PTermGrow = 0.2;
    static const std::mt19937::result_type prng_seed = 1;

    static const unsigned TournamentSize = 5;
    static const float CrossoverOnePointPTerm = 0.2;

    std::mt19937 prng(prng_seed);
    std::uniform_real_distribution<stree::Value> value_dist(-1, 1);

    stree::Environment env;
    env.add_function("+", 2, &::func);
    env.add_function("-", 2, &::func);
    env.add_function("*", 2, &::func);
    env.add_function("%", 2, &::func);
    env.add_positional("a", 0);

    Population pop_current = ramped_half_and_half(
        env, PopulationSize, InitMaxDepth, PTermGrow, prng, value_dist);

    Population pop_next;
    while (pop_next.size() < pop_current.size()) {
        streegp::IndivIndex parent1_idx = streegp::tournament(
            pop_current, TournamentSize, &::fitness<Individual>, prng);
        streegp::IndivIndex parent2_idx = streegp::tournament(
            pop_current, TournamentSize, &::fitness<Individual>, prng);
        streegp::TreeList children = streegp::crossover_one_point(
            pop_current[parent1_idx].tree(),
            pop_current[parent2_idx].tree(),
            CrossoverOnePointPTerm,
            prng);

        std::cout << "Parent 1: " << pop_current[parent1_idx].tree() << std::endl;
        std::cout << "Parent 2: " << pop_current[parent2_idx].tree() << std::endl;
        assert(children.size() == 2);
        std::cout << "Child 1   " << children[0] << std::endl;
        std::cout << "Child 2   " << children[1] << std::endl;
        std::cout << std::endl;

        for (auto tree : children)
            pop_next.emplace_back(std::move(tree));
    }

    return 0;
}
