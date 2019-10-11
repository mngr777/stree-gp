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


template<typename R, typename D>
Tree grow(
    Environment& env,
    unsigned depth,
    float p_term,
    R& prng,
    D& value_dist);

template<typename R>
Tree grow(Environment& env, unsigned depth, float p_term, R& prng);


template<typename R, typename D>
Tree full(
    Environment& env,
    unsigned depth,
    R& prng,
    D& value_dist);

template<typename R>
Tree full(Environment& env, unsigned depth, R& prng);

}}

#include "impl/init.ipp"

#endif
