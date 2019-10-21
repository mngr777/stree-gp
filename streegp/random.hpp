#ifndef STREEGP_RANDOM_HPP_
#define STREEGP_RANDOM_HPP_

#include <stree/stree.hpp>

namespace stree { namespace gp {

using UniformNodeNumDist = std::uniform_int_distribution<NodeNum>;
using UniformUnsignedDist = std::uniform_int_distribution<unsigned>;

class NoValueDist {
public:
    template<typename R>
    Value operator()(R& prng) {
        return Value();
    }
};

template<typename R>
bool _cointoss(R& prng, float p);


template<typename R>
const Subtree random_subtree(const Tree& tree, R& prng, float p_term);

template<typename R>
Subtree random_subtree(Tree& tree, R& prng, float p_term);


// NOTE: returns nullptr if value should be generated
// TODO: refactoring
template<typename R, typename D>
const SymbolPtr random_term(Environment& env, R& prng, D& value_dist);

template<typename R>
const SymbolPtr random_nonterm(Environment& env, R& prng);

template<typename R, typename D>
const SymbolPtr random_by_arity(
    Environment& env,
    Arity arity,
    R& prng,
    D& value_dist);

}}

#include "impl/random.ipp"

#endif
