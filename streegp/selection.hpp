#ifndef STREEGP_SELECTION_HPP_
#define STREEGP_SELECTION_HPP_

#include <cstddef>
#include <functional>
#include <random>
#include <set>

namespace streegp {

using Fitness = float;

using IndivIndex = std::size_t;
using IndivIndexGroup = std::set<IndivIndex>;
using UniformIndivIndexDist = std::uniform_int_distribution<IndivIndex>;

const IndivIndex NoIndivIndex = -1;

template<typename P, typename R>
IndivIndexGroup random_group(const P& population, unsigned size, R& prng);


template<typename P, typename R>
IndivIndex tournament(
    P& population,
    unsigned size,
    std::function<Fitness(typename P::value_type&)> fitness,
    R& prng);

}

#include "impl/selection.ipp"

#endif
