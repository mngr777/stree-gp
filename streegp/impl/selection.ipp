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

template<typename P, typename R>
IndividualIndex tournament(
    P& population,
    unsigned size,
    std::function<Fitness(typename P::value_type&)> fitness,
    R& prng)
{
    assert(size > 0);
    IndividualIndexGroup group = random_group(population, size, prng);
    IndividualIndex winner_index = NoIndividualIndex;
    for (IndividualIndex index : group) {
        if (winner_index == NoIndividualIndex
            || fitness(population[index]) < fitness(population[winner_index]))
        {
            winner_index = index;
        }
    }
    assert(winner_index != NoIndividualIndex);
    return winner_index;
}

}
