#ifndef STREEGP_RANDOM_HPP_
#define STREEGP_RANDOM_HPP_

#include <stree/stree.hpp>

namespace streegp {

using UniformNodeNumDist = std::uniform_int_distribution<stree::NodeNum>;
using UniformUnsignedDist = std::uniform_int_distribution<unsigned>;

class NoValueDist {
public:
    template<typename R>
    stree::Value operator()(R& prng) {
        return stree::Value();
    }
};

template<typename R>
bool _cointoss(R& prng, float p);

template<typename R>
stree::Subtree random_subtree(stree::Tree& tree, R& prng, float p_term);

// NOTE: returns nullptr if value should be generated
// TODO: refactoring
template<typename R, typename D>
const stree::Symbol* random_term(stree::Environment& env, R& prng, D& value_dist);

template<typename R>
const stree::Symbol* random_nonterm(stree::Environment& env, R& prng);

template<typename R, typename D>
const stree::Symbol* random_by_arity(
    stree::Environment& env,
    stree::Arity arity,
    R& prng,
    D& value_dist);

}

#include "impl/random.ipp"

#endif
