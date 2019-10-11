#ifndef STREEGP_MUTATION_HPP_
#define STREEGP_MUTATION_HPP_

#include <stree/stree.hpp>

namespace stree { namespace gp {

// Subtree mutation

template<typename R, typename D>
Tree mutate_subtree(
    Tree tree,
    unsigned depth,
    float p_term,
    float p_term_grow,
    R& prng,
    D& value_dist);

template<typename R>
Tree mutate_subtree(
    Tree tree,
    unsigned depth,
    float p_term,
    float p_term_grow,
    R& prng);


// Point mutation

template<typename R, typename D>
Tree mutate_point(Tree tree, float p_term, R& prng, D& value_dist);

template<typename R>
Tree mutate_point(Tree tree, float p_term, R& prng);


// Hoist mutation

template<typename R>
Tree mutate_hoist(Tree tree, float p_term, R& prng);

}}

#include "impl/mutation.ipp"

#endif
