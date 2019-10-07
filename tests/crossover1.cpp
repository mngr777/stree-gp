#include <cmath>
#include <iostream>
#include <random>
#include <utility>
#include <stree/stree.hpp>
#include <streegp/streegp.hpp>
#include "macros.hpp"

template<typename I>
streegp::Fitness evaluate(I& individual) {
    stree::Value error = 0.0;
    for (stree::Value a = -10; a <= 10; ++a) {
        stree::Params params{a};
        stree::Value result = stree::eval(individual.tree(), params);
        stree::Value answer = a * a - 2 * a + 1; // a^2 - 2a + 1;
        error += std::fabs(result - answer);
    }
    individual.set_fitness(error);
    return error;
}

template<typename I>
streegp::Fitness get_fitness(I& individual) {
    if (!individual.has_fitness()) {
        evaluate(individual);
    }
    return individual.fitness();
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

    using Individual = streegp::Individual;
    using Population = streegp::Population<Individual>;

    Population pop_current = streegp::ramped_half_and_half<Individual>(
        env, PopulationSize, InitMaxDepth, PTermGrow, prng, value_dist);

    Population pop_next;
    while (pop_next.size() < pop_current.size()) {
        std::cout << "Tournament selection, one point crossover" << std::endl;
        // Select parents
        Individual& parent1 = streegp::selection_tournament(
            pop_current, TournamentSize, prng, &::get_fitness<Individual>);
        Individual& parent2 = streegp::selection_tournament(
            pop_current, TournamentSize, prng, &::get_fitness<Individual>);
        // Apply one-point crossover
        stree::Tree child = streegp::crossover_one_point(
            parent1.tree(),
            parent2.tree(),
            CrossoverOnePointPTerm,
            prng);

        // Pring parents and child
        std::cout << "Parent 1: " << parent1.tree() << std::endl;
        std::cout << "Parent 2: " << parent2.tree() << std::endl;
        std::cout << "Child     " << child << std::endl;
        std::cout << std::endl;

        // Emplace child
        pop_next.emplace_back(std::move(child));
    }

    return 0;
}
