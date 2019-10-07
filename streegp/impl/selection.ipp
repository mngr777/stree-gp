#include <random>
#include <cassert>

namespace streegp {

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
I& tournament(
    Population<I>& population,
    unsigned size,
    Evaluator<I> evaluator,
    R& prng)
{
    assert(size > 0);
    IndividualIndexGroup group = random_group(population, size, prng);
    IndividualIndex winner_index = NoIndividualIndex;
    for (IndividualIndex index : group) {
        if (winner_index == NoIndividualIndex
            || get_fitness(population[index], evaluator) < get_fitness(population[winner_index], evaluator))
        {
            winner_index = index;
        }
    }
    assert(winner_index != NoIndividualIndex);
    return population[winner_index];
}

}
