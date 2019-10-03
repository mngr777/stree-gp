#include <streegp/random.hpp>

namespace streegp {

void _check_environment(stree::Environment& env) {
    if (env.nonterminal_num() == 0) {
        throw std::runtime_error("Cannot generate a tree without terminals");
    }
}

template<typename R, typename D>
void _grow(
    stree::Builder& builder,
    unsigned depth,
    float p_term,
    R& prng,
    D& value_dist)
{
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
            _grow(builder,  depth - 1, p_term, prng, value_dist);
            builder.up();
        }
    } else {
        // Set random terminal
        const stree::Symbol* symbol = random_term(builder.env(), prng, value_dist);
        if (symbol) {
            // Use terminal symbol
            builder.set(symbol);
        } else {
            // Generate value
            builder.set(value_dist(prng));
        }
    }
}

template<typename R, typename D>
void _full(
    stree::Builder& builder,
    unsigned depth,
    R& prng,
    D& value_dist)
{
    unsigned nonterm_num = builder.env().nonterminal_num();
    if (depth > 1 && nonterm_num > 1) {
        // Set random nonterminal
        const stree::Symbol* symbol = random_nonterm(builder.env(), prng);
        assert(symbol);
        builder.set(symbol);
        // Build children
        for (unsigned n = 0; n < symbol->arity(); ++n) {
            builder.down(n);
            _full(builder, depth - 1, prng, value_dist);
            builder.up();
        }
    } else {
        // Set random terminal
        const stree::Symbol* symbol = random_term(builder.env(), prng, value_dist);
        if (symbol) {
            // Use terminal symbol
            builder.set(symbol);
        } else {
            // Generate value
            builder.set(value_dist(prng));
        }
    }
}


template<typename R, typename D>
stree::Tree grow(
    stree::Environment& env,
    unsigned depth,
    float p_term,
    R& prng,
    D& value_dist)
{
    _check_environment(env);
    stree::Builder builder(env);
    _grow(builder, depth, p_term, prng, value_dist);
    assert(builder.is_valid());
    return stree::Tree(&builder.env(), builder.root());
}

template<typename R>
stree::Tree grow(stree::Environment& env, unsigned depth, float p_term, R& prng) {
    NoValueDist value_dist;
    return grow(env, depth, p_term, prng, value_dist);
}


template<typename R, typename D>
stree::Tree full(
    stree::Environment& env,
    unsigned depth,
    R& prng,
    D& value_dist)
{
    _check_environment(env);
    stree::Builder builder(env);
    _full(builder, depth, prng, value_dist);
    assert(builder.is_valid());
    return stree::Tree(&builder.env(), builder.root());
}

template<typename R>
stree::Tree full(stree::Environment& env, unsigned depth, R& prng) {
    NoValueDist value_dist;
    return full(env, depth, prng, value_dist);
}

}
