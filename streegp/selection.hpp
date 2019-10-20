#ifndef STREEGP_SELECTION_HPP_
#define STREEGP_SELECTION_HPP_

#include <cstddef>
#include <functional>
#include <random>
#include <set>
#include <streegp/config.hpp>
#include <streegp/context.hpp>
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

template<typename C>
typename C::IndividualType& selection_tournament(
    C& context,
    Population<typename C::IndividualType>& population,
    unsigned size)
{
    return selection_tournament<typename C::IndividualType, typename C::PrngType>(
        population, size, context.prng, context.evaluator);
}

template<typename C>
typename C::IndividualType& selection_tournament(
    C& context,
    Population<typename C::IndividualType>& population)
{
    const Config& config = context.config;
    return selection_tournament<C>(
        context,
        population,
        config.get<unsigned>(conf::SelectionTournamentSize));
}


// TODO: add evaluator parameter
template<typename I, typename R>
I& selection_fitness_proportional(Population<I>& population, R& prng);

template<typename C>
typename C::IndividualType& selection_fitness_proportional(
    C& context,
    Population<typename C::IndividualType>& population)
{
    return selection_fitness_proportional<typename C::IndividualType, typename C::PrngType>(
        population, context.prng);
}

}}

#include "impl/selection.ipp"

#endif
