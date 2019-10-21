#ifndef STREEGP_CROSSOVER_HPP_
#define STREEGP_CROSSOVER_HPP_

#include <random>
#include <stree/stree.hpp>
#include <streegp/config.hpp>
#include <streegp/context.hpp>
#include <streegp/random.hpp>

namespace stree { namespace gp {

using TreeList = std::vector<Tree>;


template<typename R>
Tree crossover_one_point(
    Tree tree1, const Tree& tree2,
    float p_term,
    R& prng);

template<typename C>
Tree crossover_one_point(
    C& context,
    const Tree& tree1, const Tree& tree2,
    float p_term)
{
    return crossover_one_point<typename C::PrngType>(tree1, tree2, p_term, context.prng);
}

template<typename C>
Tree crossover_one_point(C& context, const Tree& tree1, const Tree& tree2) {
    const Config& config = context.config;
    return crossover_one_point<C>(
        context,
        tree1, tree2,
        config.get<float>(conf::CrossoverOnePointPTerm));
}

template<typename C>
typename C::IndividualType crossover_one_point(
    C& context,
    const typename C::IndividualType& parent1,
    const typename C::IndividualType& parent2)
{
    return typename C::IndividualType(
        crossover_one_point<C>(context, parent1.tree(), parent2.tree()));
}


template<typename R>
Tree crossover_random(
    Tree tree1, const Tree& tree2,
    float p_term,
    R& prng);

template<typename C>
Tree crossover_random(
    C& context,
    const Tree& tree1, const Tree& tree2,
    float p_term)
{
    return crossover_random<typename C::PrngType>(tree1, tree2, p_term, context.prng);
}

template<typename C>
Tree crossover_random(
    C& context,
    const Tree& tree1, const Tree& tree2)
{
    const Config& config = context.config;
    return crossover_random<C>(
        context,
        tree1, tree2,
        config.get<float>(conf::CrossoverRandomPTerm));
}

template<typename C>
typename C::IndividualType crossover_random(
    C& context,
    const typename C::IndividualType& parent1,
    const typename C::IndividualType& parent2)
{
    return typename C::IndividualType(
        crossover_random<C>(context, parent1.tree(), parent2.tree()));
}

}}

#include "impl/crossover.ipp"

#endif
