#include <stree/stree.hpp>

#include <random>
#include <streegp/init.hpp>
#include <streegp/random.hpp>

namespace stree { namespace gp {

template<typename R, typename D>
Tree mutate_subtree(
    Tree tree,
    unsigned depth,
    float p_term,
    float p_term_grow,
    R& prng,
    D& value_dist)
{
    Tree replacement = grow(*tree.env(), depth, p_term_grow, prng, value_dist);
    Subtree subtree = random_subtree(tree, prng, p_term);
    subtree.replace(replacement);
    assert(tree.is_valid());
    return tree;
}

template<typename R>
Tree mutate_subtree(
    Tree tree,
    unsigned depth,
    float p_term,
    float p_term_grow,
    R& prng)
{
    NoValueDist value_dist;
    return mutate_subtree(tree, depth, p_term, p_term_grow, prng, value_dist);
}


template<typename R, typename D>
Tree mutate_point(Tree tree, float p_term, R& prng, D& value_dist)
{
    Environment& env = *tree.env();
    Subtree subtree = random_subtree(tree, prng, p_term);
    const SymbolPtr symbol = random_by_arity(
        env, subtree.arity(), prng, value_dist);
    if (symbol) {
        subtree.set(symbol);
    } else {
        assert(subtree.arity() == 0);
        subtree.set(value_dist(prng));
    }
    assert(tree.is_valid());
    return tree;
}

template<typename R>
Tree mutate_point(Tree tree, float p_term, R& prng)
{
    NoValueDist value_dist;
    return mutate_point(tree, p_term, prng, value_dist);
}


template<typename R>
Tree mutate_hoist(Tree tree, float p_term, R& prng) {
    auto desc = tree.describe();
    if (desc.nonterm_num > 1) {
        // Get random subtree with nonterminal root (but not tree root)
        NodeNum n_max = desc.nonterm_num - 1;
        NodeFilter filter;
        filter.is_terminal = IsTerminalNo;
        Subtree subtree = tree.sub(UniformNodeNumDist{0, n_max}(prng), filter);
        // Cut subtree, store in separate tree
        Tree slice(tree.env());
        subtree.swap(slice.sub(0));
        // Select random subtree in slice
        Subtree slice_subtree = random_subtree(slice, prng, p_term);
        // Swap with initial subtree
        subtree.swap(slice_subtree);
    }
    assert(tree.is_valid());
    return tree;
}

}}
