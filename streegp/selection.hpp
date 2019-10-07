#ifndef STREEGP_SELECTION_HPP_
#define STREEGP_SELECTION_HPP_

#include <cstddef>
#include <functional>
#include <random>
#include <set>
#include <streegp/individual.hpp>

namespace streegp {

using IndividualIndexGroup = std::set<IndividualIndex>;
using UniformIndividualIndexDist = std::uniform_int_distribution<IndividualIndex>;

template<typename P, typename R>
IndividualIndexGroup random_group(const P& population, unsigned size, R& prng);

// NOTE: we may actually prefer index for comparing parents to prevent self-crossover,
// although individuals should probably have unique IDs for tracing genealogy anyway
template<typename I, typename R>
I& tournament(
    Population<I>& population,
    unsigned size,
    Evaluator<I> evaluator,
    R& prng);

}

#include "impl/selection.ipp"

#endif
