#ifndef STREEGP_CONFIG_HPP_
#define STREEGP_CONFIG_HPP_

#include <stree/stree.hpp>
#include <streegp/random.hpp>

namespace stree { namespace gp {

template<typename R, typename D>
struct Context {
    using PrngType = R;
    using ValueDistType = D;

    Context(Environment& env, R& prng, const D& value_dist)
        : env(env), prng(prng), value_dist(value_dist) {}

    Environment& env;
    R& prng;
    D value_dist;
};


template<typename R, typename D>
Context<R, D> make_context(Environment& env, R& prng, const D& value_dist) {
    return Context<R, D>(env, prng, value_dist);
}

template<typename R>
Context<R, NoValueDist> make_context(Environment& env, R& prng) {
    make_context(env, prng, NoValueDist());
}

}}

#endif
