#ifndef STREEGP_INIT_HPP_
#define STREEGP_INIT_HPP_

#include <stree/stree.hpp>
#include <streegp/individual.hpp>
#include <streegp/random.hpp>

namespace stree { namespace gp {

template<typename I, typename P, typename D>
Population<I> ramped_half_and_half(
    Environment& env,
    unsigned size,
    unsigned max_depth,
    float p_term_grow,
    P& prng,
    D& value_dist);

template<typename I, typename P>
Population<I> ramped_half_and_half(
    Environment& env,
    unsigned size,
    unsigned max_depth,
    float p_term_grow,
    P& prng);

template<typename I, typename C>
Population<I> ramped_half_and_half(
    C& context,
    unsigned size,
    unsigned max_depth,
    float p_term_grow)
{
    ramped_half_and_half<I, typename C::PrngType, typename C::ValueDistType>(
        context.env,
        size,
        max_depth,
        p_term_grow,
        context.prng,
        context.value_dist);
}


template<typename R, typename D>
Tree grow(
    Environment& env,
    unsigned depth,
    float p_term,
    R& prng,
    D& value_dist);

template<typename R>
Tree grow(Environment& env, unsigned depth, float p_term, R& prng);

template<typename C>
Tree grow(C& context, unsigned depth, float p_term) {
    return grow<typename C::PrngType, typename C::ValueDistType>(
        context.env, depth, p_term, context.prng, context.value_dist);
}


template<typename R, typename D>
Tree full(
    Environment& env,
    unsigned depth,
    R& prng,
    D& value_dist);

template<typename R>
Tree full(Environment& env, unsigned depth, R& prng);

template<typename C>
Tree full(C& context, unsigned depth) {
    return full<typename C::PrngType, typename C::ValueDistType>(
        context.env, depth, context.prng, context.value_dist);
}

}}

#include "impl/init.ipp"

#endif
