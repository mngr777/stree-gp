#include <random>

namespace streegp {

template<typename P, typename R>
IndivIndexGroup random_group(const P& population, unsigned size, R& prng) {
    assert(population.size() > size && size > 0);
    UniformIndivIndexDist dist(0, population.size() - 1);
    IndivIndexGroup group;
    while (group.size() < size) {
        IndivIndex index = dist(prng);
        if (group.count(index) == 0)
            group.insert(index);
    }
    return group;
}

template<typename P, typename R>
IndivIndex tournament(
    P& population,
    unsigned size,
    std::function<Fitness(typename P::value_type&)> fitness,
    R& prng)
{
    assert(size > 0);
    IndivIndexGroup group = random_group(population, size, prng);
    IndivIndex winner_index = NoIndivIndex;
    for (IndivIndex index : group) {
        if (winner_index == NoIndivIndex
            || fitness(population[index]) < fitness(population[winner_index]))
        {
            winner_index = index;
        }
    }
    assert(winner_index != NoIndivIndex);
    return winner_index;
}

}
