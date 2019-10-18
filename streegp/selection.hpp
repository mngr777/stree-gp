#ifndef STREEGP_SELECTION_HPP_
#define STREEGP_SELECTION_HPP_

#include <cstddef>
#include <functional>
#include <random>
#include <set>
#include <streegp/individual.hpp>

namespace stree { namespace gp {

using IndividualIndexGroup = std::set<IndividualIndex>;
using UniformIndividualIndexDist = std::uniform_int_distribution<IndividualIndex>;

template<typename P, typename R>
IndividualIndexGroup random_group(const P& population, unsigned size, R& prng);

// NOTE: we may actually prefer index for comparing parents to prevent self-crossover,
// although individuals should probably have unique IDs for tracing genealogy anyway
template<typename I, typename R>
I& selection_tournament(
    Population<I>& population,
    unsigned size,
    R& prng,
    Evaluator<I> evaluate);

template<typename C, typename I>
I& selection_tournament(
    C& context,
    Population<I>& population,
    unsigned size,
    Evaluator<I> evaluate)
{
    return selection_tournament<I, typename C::PrngType>(
        population, size, context.prng, evaluate);
}

// TODO: add evaluator parameter
template<typename I, typename R>
I& selection_fitness_proportional(Population<I>& population, R& prng);

template<typename C, typename I>
I& selection_fitness_proportional(C& context, Population<I>& population) {
    return selection_fitness_proportional<I, typename C::PrngType>(
        population, context.prng);
}

}}

#include "impl/selection.ipp"

#endif
