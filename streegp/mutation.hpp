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
    R& prng,
    D& value_dist,
    float p_term = 0.2,
    float p_term_grow = 0.2)
{
    stree::Tree chicken = grow(*tree.env(), depth, prng, p_term_grow);
    stree::Subtree subtree = _random_subtree(tree, prng, p_term);
    subtree.replace(chicken);
}

}

#endif
