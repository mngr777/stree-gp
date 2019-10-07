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


template<typename P, typename R>
IndividualIndex tournament(
    P& population,
    unsigned size,
    std::function<Fitness(typename P::value_type&)> fitness,
    R& prng);

}

#include "impl/selection.ipp"

#endif
