#ifndef STREEGP_MUTATION_HPP_
#define STREEGP_MUTATION_HPP_

#include <stree/stree.hpp>

namespace streegp {

template<typename R, typename D>
stree::Tree mutate_subtree(
    stree::Tree tree,
    unsigned depth,
    float p_term,
    float p_term_grow,
    R& prng,
    D& value_dist);

template<typename R>
stree::Tree mutate_subtree(
    stree::Tree tree,
    unsigned depth,
    float p_term,
    float p_term_grow,
    R& prng);


template<typename R, typename D>
stree::Tree mutate_point(
    stree::Tree tree,
    float p_term,
    R& prng,
    D& value_dist);

template<typename R>
stree::Tree mutate_point(
    stree::Tree tree,
    float p_term,
    R& prng);

}

#include "impl/mutation.ipp"

#endif
