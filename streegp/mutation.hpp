#ifndef STREEGP_MUTATION_HPP_
#define STREEGP_MUTATION_HPP_

#include <random>
#include <stree/stree.hpp>
#include <streegp/init.hpp>
#include <streegp/random.hpp>

namespace streegp {

template<typename R>
stree::Subtree _random_subtree(stree::Tree& tree, R& prng, float p_term) {
    assert(tree.is_valid());
    auto desc = tree.describe();
    assert(desc.term_num > 0);
    // Choose terminal or non-terminal
    bool use_term = (desc.nonterm_num == 0) || cointoss(prng, p_term);
    stree::NodeNum n_max = use_term ? desc.term_num - 1 : desc.nonterm_num - 1;
    // Select random subtree
    stree::NodeFilter filter;
    filter.is_terminal = use_term ? stree::IsTerminalYes : stree::IsTerminalNo;
    return tree.sub(UniformNodeNumDist{0, n_max}(prng), filter);
}

template<typename R, typename D>
void mutate_headless(
    stree::Tree& tree,
    unsigned depth,
    float p_term,
    float p_term_grow,
    R& prng,
    D& value_dist)
{
    stree::Tree chicken = grow(*tree.env(), depth, p_term_grow, prng, value_dist);
    stree::Subtree subtree = _random_subtree(tree, prng, p_term);
    subtree.replace(chicken);
}

template<typename R>
void mutate_headless(
    stree::Tree& tree,
    unsigned depth,
    float p_term,
    float p_term_grow,
    R& prng)
{
    NoValueDist value_dist;
    mutate_headless(tree, depth, p_term, p_term_grow, prng, value_dist);
}

}

#endif
