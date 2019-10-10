#ifndef STREEGP_CROSSOVER_HPP_
#define STREEGP_CROSSOVER_HPP_

#include <random>
#include <stree/stree.hpp>
#include <streegp/random.hpp>

namespace streegp {

using TreeList = std::vector<stree::Tree>;


template<typename R>
stree::Tree crossover_one_point(
    stree::Tree tree1,
    stree::Tree& tree2,
    float p_term,
    R& prng);

template<typename R>
stree::Tree crossover_random(
    stree::Tree tree1,
    stree::Tree& tree2,
    float p_term,
    R& prng);

}

#include "impl/crossover.ipp"

#endif
