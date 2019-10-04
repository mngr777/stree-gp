#include <stree/stree.hpp>

#include <random>
#include <streegp/init.hpp>
#include <streegp/random.hpp>

namespace streegp {

template<typename R>
stree::Subtree _random_subtree(stree::Tree& tree, R& prng, float p_term) {
    assert(tree.is_valid());
    auto desc = tree.describe();
    assert(desc.term_num > 0);
    // Choose terminal or non-terminal
    bool use_term = (desc.nonterm_num == 0) || _cointoss(prng, p_term);
    stree::NodeNum n_max = use_term ? desc.term_num - 1 : desc.nonterm_num - 1;
    // Select random subtree
    stree::NodeFilter filter;
    filter.is_terminal = use_term ? stree::IsTerminalYes : stree::IsTerminalNo;
    return tree.sub(UniformNodeNumDist{0, n_max}(prng), filter);
}

template<typename R, typename D>
stree::Tree mutate_subtree(
    stree::Tree tree,
    unsigned depth,
    float p_term,
    float p_term_grow,
    R& prng,
    D& value_dist)
{
    stree::Tree replacement = grow(*tree.env(), depth, p_term_grow, prng, value_dist);
    stree::Subtree subtree = _random_subtree(tree, prng, p_term);
    subtree.replace(replacement);
    return tree;
}

template<typename R>
stree::Tree mutate_subtree(
    stree::Tree tree,
    unsigned depth,
    float p_term,
    float p_term_grow,
    R& prng)
{
    NoValueDist value_dist;
    return mutate_subtree(tree, depth, p_term, p_term_grow, prng, value_dist);
}


template<typename R, typename D>
stree::Tree mutate_point( stree::Tree tree, float p_term, R& prng, D& value_dist)
{
    stree::Environment& env = *tree.env();
    stree::Subtree subtree = _random_subtree(tree, prng, p_term);
    const stree::Symbol* symbol = random_by_arity(
        env, subtree.arity(), prng, value_dist);
    if (symbol) {
        subtree.set(symbol);
    } else {
        assert(subtree.arity() == 0);
        subtree.set(value_dist(prng));
    }
    return tree;
}

template<typename R>
stree::Tree mutate_point(stree::Tree tree, float p_term, R& prng)
{
    NoValueDist value_dist;
    return mutate_point(tree, p_term, prng, value_dist);
}


template<typename R>
stree::Tree mutate_hoist(stree::Tree tree, float p_term, R& prng) {
    auto desc = tree.describe();
    if (desc.nonterm_num > 1) {
        // Get random subtree with nonterminal root (but not tree root)
        stree::NodeNum n_max = desc.nonterm_num - 1;
        stree::NodeFilter filter;
        filter.is_terminal = stree::IsTerminalNo;
        stree::Subtree subtree = tree.sub(UniformNodeNumDist{0, n_max}(prng), filter);
        // Cut subtree, store in separate tree
        stree::Tree slice(tree.env());
        subtree.swap(slice.sub(0));
        // Select random subtree in slice
        stree::Subtree slice_subtree = _random_subtree(slice, prng, p_term);
        // Swap with initial subtree
        subtree.swap(slice_subtree);
    }
    return tree;
}

}
