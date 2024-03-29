#include <utility>
#include <streegp/random.hpp>

namespace stree { namespace gp {

template<typename I, typename P, typename D>
void ramped_half_and_half(
    Environment& env,
    Population<I>& population,
    unsigned size,
    unsigned max_depth,
    float p_term_grow,
    P& prng,
    D& value_dist)
{
    if (population.size() >= size)
        return;

    unsigned num = size - population.size();
    unsigned i = 0;
    // grow
    for (; i < num / 2; ++i)
        population.emplace_back(
            grow(env, max_depth, p_term_grow, prng, value_dist));
    // full
    for (; i < num; ++i)
        population.emplace_back(
            full(env, max_depth, prng, value_dist));
}

template<typename I, typename P>
void ramped_half_and_half(
    Environment& env,
    Population<I> population,
    unsigned size,
    unsigned max_depth,
    float p_term_grow,
    P& prng)
{
    NoValueDist value_dist;
    return ramped_half_and_half<I>(env, population, size, max_depth, p_term_grow, prng, value_dist);
}


inline void _check_environment(Environment& env) {
    if (env.symbols().terminals().size() == 0) {
        throw std::runtime_error("Cannot generate a tree without terminals");
    }
}

template<typename R, typename D>
void _grow(
    Builder& builder,
    unsigned depth,
    float p_term,
    R& prng,
    D& value_dist)
{
    if (builder.env().symbols().nonterminals().size() == 0
        || (depth > 1 && !_cointoss(prng, p_term)))
    {
        // Set random nonterminal
        const SymbolPtr symbol = random_nonterm(builder.env(), prng);
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
        const SymbolPtr symbol = random_term(builder.env(), prng, value_dist);
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
    Builder& builder,
    unsigned depth,
    R& prng,
    D& value_dist)
{
    unsigned nonterm_num = builder.env().symbols().nonterminals().size();
    if (depth > 1 && nonterm_num > 1) {
        // Set random nonterminal
        const SymbolPtr symbol = random_nonterm(builder.env(), prng);
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
        const SymbolPtr symbol = random_term(builder.env(), prng, value_dist);
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
Tree grow(
    Environment& env,
    unsigned depth,
    float p_term,
    R& prng,
    D& value_dist)
{
    _check_environment(env);
    Builder builder(env);
    _grow(builder, depth, p_term, prng, value_dist);
    assert(builder.is_valid());
    return Tree(&builder.env(), builder.root());
}

template<typename R>
Tree grow(Environment& env, unsigned depth, float p_term, R& prng) {
    NoValueDist value_dist;
    return grow(env, depth, p_term, prng, value_dist);
}


template<typename R, typename D>
Tree full(
    Environment& env,
    unsigned depth,
    R& prng,
    D& value_dist)
{
    _check_environment(env);
    Builder builder(env);
    _full(builder, depth, prng, value_dist);
    assert(builder.is_valid());
    return Tree(&builder.env(), builder.root());
}

template<typename R>
Tree full(Environment& env, unsigned depth, R& prng) {
    NoValueDist value_dist;
    return full(env, depth, prng, value_dist);
}

}}
