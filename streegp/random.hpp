#ifndef STREEGP_RANDOM_HPP_
#define STREEGP_RANDOM_HPP_

#include <random>
#include <stree/stree.hpp>

namespace streegp {

using UniformNodeNumDist = std::uniform_int_distribution<stree::NodeNum>;
using UniformUnsignedDist = std::uniform_int_distribution<unsigned>;

template<typename R>
bool _cointoss(R& prng, float p_true) {
    return std::bernoulli_distribution{p_true}(prng);
}

template<typename R>
const stree::Symbol* random_term(stree::Environment& env, R& prng) {
    unsigned term_num = env.terminal_num();
    assert(term_num > 1);
    UniformUnsignedDist dist(0, term_num - 1);
    return env.terminal(dist(prng));
}

template<typename R>
const stree::Symbol* random_nonterm(stree::Environment& env, R& prng) {
    unsigned nonterm_num = env.nonterminal_num();
    assert(nonterm_num > 1);
    UniformUnsignedDist dist(0, nonterm_num - 1);
    return env.nonterminal(dist(prng));
}

}

#endif
