#include <cmath>
#include <iostream>
#include <random>
#include <utility>
#include <stree/stree.hpp>
#include <streegp/streegp.hpp>
#include "macros.hpp"

template<typename I>
stree::gp::Fitness evaluate(I& individual) {
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
stree::gp::Fitness get_fitness(I& individual) {
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

    // One point crossover
    static const unsigned CrossoverOnePointNum = 10;
    static const float CrossoverOnePointPTerm = 0.2;

    // Random crossover
    static const unsigned CrossoverRandomNum = PopulationSize - CrossoverOnePointNum;
    static const float CrossoverRandomPTerm = 0.2;

    std::mt19937 prng(prng_seed);
    std::uniform_real_distribution<stree::Value> value_dist(-1, 1);

    stree::Environment env;
    env.add_function("+", 2, &::func);
    env.add_function("-", 2, &::func);
    env.add_function("*", 2, &::func);
    env.add_function("%", 2, &::func);
    env.add_positional("a", 0);

    using Individual = stree::gp::Individual;
    using Population = stree::gp::Population<Individual>;

    Population pop_current = stree::gp::ramped_half_and_half<Individual>(
        env, PopulationSize, InitMaxDepth, PTermGrow, prng, value_dist);

    Population pop_next;
    {
        Population::size_type index = 0;
        Population::size_type max_index = 0;

        // One point crossover
        std::cout << "Tournament selection, one point crossover" << std::endl;
        std::cout << std::endl;
        max_index += CrossoverOnePointNum;
        for(; index < max_index; ++index) {
            // Select parents
            Individual& parent1 = stree::gp::selection_tournament(
                pop_current, TournamentSize, prng, &::get_fitness<Individual>);
            Individual& parent2 = stree::gp::selection_tournament(
                pop_current, TournamentSize, prng, &::get_fitness<Individual>);
            // Apply one-point crossover
            stree::Tree child = stree::gp::crossover_one_point(
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

        std::cout << std::endl;

        // Random crossover
        std::cout << "Tournament selection, random crossover" << std::endl;
        std::cout << std::endl;
        max_index += CrossoverRandomNum;
        assert(max_index == pop_current.size());
        for(; index < max_index; ++index) {
            // Select parents
            Individual& parent1 = stree::gp::selection_tournament(
                pop_current, TournamentSize, prng, &::get_fitness<Individual>);
            Individual& parent2 = stree::gp::selection_tournament(
                pop_current, TournamentSize, prng, &::get_fitness<Individual>);
            // Apply one-point crossover
            stree::Tree child = stree::gp::crossover_random(
                parent1.tree(),
                parent2.tree(),
                CrossoverRandomPTerm,
                prng);

            // Pring parents and child
            std::cout << "Parent 1: " << parent1.tree() << std::endl;
            std::cout << "Parent 2: " << parent2.tree() << std::endl;
            std::cout << "Child     " << child << std::endl;
            std::cout << std::endl;

            // Emplace child
            pop_next.emplace_back(std::move(child));
        }
    }

    assert(pop_next.size() == pop_current.size());
    return 0;
}
