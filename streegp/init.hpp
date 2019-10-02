#ifndef STREEGP_INIT_HPP_
#define STREEGP_INIT_HPP_

#include <stree/stree.hpp>
#include <streegp/random.hpp>

namespace streegp {

void _check_environment(stree::Environment& env) {
    if (env.nonterminal_num() == 0) {
        throw std::runtime_error("Cannot generate a tree without terminals");
    }
}

template<typename R>
void _grow(stree::Builder& builder, unsigned depth, R& prng, float p_term) {
    if (builder.env().nonterminal_num() == 0
        || (depth > 1 && !_cointoss(prng, p_term)))
    {
        // Set random nonterminal
        const stree::Symbol* symbol = random_nonterm(builder.env(), prng);
        assert(symbol);
        builder.set(symbol);
        // Grow argument subtrees
        for (unsigned n = 0; n < symbol->arity(); ++n) {
            builder.down(n);
            _grow(builder,  depth - 1, prng, p_term);
            builder.up();
        }
    } else {
        // Set random terminal
        builder.set(random_term(builder.env(), prng));
    }
}

template<typename R>
void _full(stree::Builder& builder, unsigned depth, R& prng) {
    unsigned nonterm_num = builder.env().nonterminal_num();
    if (depth > 1 && nonterm_num > 1) {
        // Set random nonterminal
        const stree::Symbol* symbol = random_nonterm(builder.env(), prng);
        assert(symbol);
        builder.set(symbol);
        // Build children
        for (unsigned n = 0; n < symbol->arity(); ++n) {
            builder.down(n);
            _full(builder, depth - 1, prng);
            builder.up();
        }
    } else {
        // Set random terminal
        builder.set(random_term(builder.env(), prng));
    }
}


template<typename R>
stree::Tree grow(
    stree::Environment& env,
    unsigned depth,
    R& prng,
    float p_term = 0.2)
{
    _check_environment(env);
    stree::Builder builder(env);
    _grow(builder, depth, prng, p_term);
    assert(builder.is_valid());
    return stree::Tree(&builder.env(), builder.root());
}

template<typename R>
stree::Tree full(stree::Environment& env, unsigned depth, R& prng) {
    _check_environment(env);
    stree::Builder builder(env);
    _full(builder, depth, prng);
    assert(builder.is_valid());
    return stree::Tree(&builder.env(), builder.root());
}

}

#endif

