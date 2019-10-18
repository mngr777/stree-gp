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

template<typename C>
Tree crossover_one_point(
    C& context,
    Tree tree1,
    Tree& tree2,
    float p_term)
{
    return crossover_one_point<C::PrngType>(tree1, tree2, p_term, context.prng);
}


template<typename R>
Tree crossover_random(
    Tree tree1,
    Tree& tree2,
    float p_term,
    R& prng);

template<typename C>
Tree crossover_random(
    C& context,
    Tree tree1,
    Tree& tree2,
    float p_term)
{
    return crossover_random<C::PrngType>(tree1, tree2, p_term, context.prng);
}

}}

#include "impl/crossover.ipp"

#endif
