#ifndef STREEGP_MUTATION_HPP_
#define STREEGP_MUTATION_HPP_

#include <random>
#include <stree/stree.hpp>
#include <streegp/init.hpp>
#include <streegp/random.hpp>

namespace streegp {

template<typename R, typename D>
stree::Tree mutate_headless(
    stree::Tree& tree,
    unsigned depth,
    float p_term,
    float p_term_grow,
    R& prng,
    D& value_dist);

template<typename R>
stree::Tree mutate_headless(
    stree::Tree& tree,
    unsigned depth,
    float p_term,
    float p_term_grow,
    R& prng);

}

#include "impl/mutation.ipp"

#endif
