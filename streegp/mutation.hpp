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

template<typename C>
Tree mutate_subtree(
    C& context,
    Tree tree,
    unsigned depth,
    float p_term,
    float p_term_grow)
{
    return mutate_subtree<typename C::PrngType, typename C::ValueDistType>(
        tree, depth, p_term, p_term_grow, context.prng, context.value_dist);
}


// Point mutation

template<typename R, typename D>
Tree mutate_point(Tree tree, float p_term, R& prng, D& value_dist);

template<typename R>
Tree mutate_point(Tree tree, float p_term, R& prng);

template<typename C>
Tree mutate_point(C& context, Tree tree, float p_term) {
    return mutate_point<typename C::PrngType, typename C::ValueDistType>(
        tree, p_term, context.prng, context.value_dist);
}


// Hoist mutation

template<typename R>
Tree mutate_hoist(Tree tree, float p_term, R& prng);

template<typename C>
Tree mutate_hoist(C& context, Tree tree, float p_term) {
    return mutate_hoist<typename C::PrngType>(tree, p_term, context.prng);
}

}}

#include "impl/mutation.ipp"

#endif
