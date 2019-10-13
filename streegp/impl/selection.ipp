#include <cassert>
#include <numeric>
#include <random>

namespace stree { namespace gp {

template<typename P, typename R>
IndividualIndexGroup random_group(const P& population, unsigned size, R& prng) {
    assert(population.size() > size && size > 0);
    UniformIndividualIndexDist dist(0, population.size() - 1);
    IndividualIndexGroup group;
    while (group.size() < size) {
        IndividualIndex index = dist(prng);
        if (group.count(index) == 0)
            group.insert(index);
    }
    return group;
}

template<typename I, typename R>
I& selection_tournament(
    Population<I>& population,
    unsigned size,
    R& prng,
    Evaluator<I> evaluator)
{
    assert(size > 0 && population.size() >= size);
    IndividualIndexGroup group = random_group(population, size, prng);
    IndividualIndex winner_index = NoIndividualIndex;
    for (IndividualIndex index : group) {
        if (winner_index == NoIndividualIndex
            || (population[index].fitness(evaluator)
                < population[winner_index].fitness(evaluator)))
        {
            winner_index = index;
        }
    }
    assert(winner_index != NoIndividualIndex);
    return population[winner_index];
}

template<typename I, typename R>
I& selection_fitness_proportional(Population<I>& population, R& prng) {
    assert(population.size() > 0);
    // Calc. fitness sum
    Fitness total = std::accumulate(
        population.begin(), population.end(),
        0.0, std::plus<Fitness>());
    // Select random fitness value
    Fitness selected = std::uniform_real_distribution<Fitness>{0, total}(prng);
    // Return corresponding individual
    Fitness sum = 0.0;
    for (I& individual : population) {
        assert(individual.has_fitness() && "fitness not pre-calculated");
        sum += individual.fitness();
        if (sum >= selected)
            return individual;
    }
    assert(false);
}

}}
