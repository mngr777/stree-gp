#ifndef STREEGP_CONTEXT_HPP_
#define STREEGP_CONTEXT_HPP_

#include <stree/stree.hpp>
#include <streegp/config.hpp>
#include <streegp/individual.hpp>
#include <streegp/random.hpp>

namespace stree { namespace gp {

template<typename I, typename R, typename D>
struct Context {
    using IndividualType = I;
    using PrngType = R;
    using ValueDistType = D;

    Context(
        const Config& config,
        Environment& env,
        const Evaluator<I>& evaluator,
        R& prng,
        const D& value_dist)
        : config(config),
          env(env),
          evaluator(evaluator),
          prng(prng),
          value_dist(value_dist) {}

    Config config;
    Environment& env;
    Evaluator<I> evaluator;
    R& prng;
    D value_dist;
};


template<typename I, typename R, typename D>
Context<I, R, D> make_context(
    const Config& config,
    Environment& env,
    const Evaluator<I>& evaluator,
    R& prng,
    const D& value_dist)
{
    return Context<I, R, D>(config, env, evaluator, prng, value_dist);
}

template<typename I, typename R>
Context<I, R, NoValueDist> make_context(
    const Config& config,
    Environment& env,
    const Evaluator<I>& evaluator,
    R& prng) {
    make_context(config, env, evaluator, prng, NoValueDist());
}

}}

#endif
