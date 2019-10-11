#ifndef STREEGP_CROSSOVER_HPP_
#define STREEGP_CROSSOVER_HPP_

#include <random>
#include <stree/stree.hpp>
#include <streegp/random.hpp>

namespace stree { namespace gp {

using TreeList = std::vector<Tree>;


template<typename R>
Tree crossover_one_point(
    Tree tree1,
    Tree& tree2,
    float p_term,
    R& prng);

template<typename R>
Tree crossover_random(
    Tree tree1,
    Tree& tree2,
    float p_term,
    R& prng);

}}

#include "impl/crossover.ipp"

#endif
