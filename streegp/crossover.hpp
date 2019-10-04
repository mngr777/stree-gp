#ifndef STREEGP_CROSSOVER_HPP_
#define STREEGP_CROSSOVER_HPP_

#include <random>
#include <stree/stree.hpp>
#include <streegp/random.hpp>

namespace streegp {

using TreeList = std::vector<stree::Tree>;

template<typename R>
TreeList crossover_one_point(
    stree::Tree tree1,
    stree::Tree tree2,
    R& prng,
    float p_term = 0.2,
    bool *success = nullptr);

}

#endif
