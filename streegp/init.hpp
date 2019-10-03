#ifndef STREEGP_INIT_HPP_
#define STREEGP_INIT_HPP_

#include <stree/stree.hpp>
#include <streegp/random.hpp>

namespace streegp {

template<typename R, typename D>
stree::Tree grow(
    stree::Environment& env,
    unsigned depth,
    float p_term,
    R& prng,
    D& value_dist);

template<typename R>
stree::Tree grow(stree::Environment& env, unsigned depth, float p_term, R& prng);


template<typename R, typename D>
stree::Tree full(
    stree::Environment& env,
    unsigned depth,
    R& prng,
    D& value_dist);

template<typename R>
stree::Tree full(stree::Environment& env, unsigned depth, R& prng);

}

#include "impl/init.ipp"

#endif
