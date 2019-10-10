#include <random>
#include <type_traits>
#include <stree/stree.hpp>

namespace streegp {

template<typename R>
bool _cointoss(R& prng, float p) {
    return std::bernoulli_distribution{p}(prng);
}

template<typename R>
stree::Subtree random_subtree(stree::Tree& tree, R& prng, float p_term) {
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
const stree::Symbol* random_term(stree::Environment& env, R& prng, D& value_dist) {
    unsigned term_num = env.terminal_num();
    assert(term_num > 0);
    unsigned dist_max = std::is_same<D, NoValueDist>::value
        ? term_num - 1
        : term_num;
    UniformUnsignedDist dist(0, dist_max);
    unsigned index = dist(prng);
    return (index < term_num)
        ? env.terminal(index)
        : nullptr;
}

template<typename R>
const stree::Symbol* random_nonterm(stree::Environment& env, R& prng) {
    unsigned nonterm_num = env.nonterminal_num();
    assert(nonterm_num > 0);
    UniformUnsignedDist dist(0, nonterm_num - 1);
    return env.nonterminal(dist(prng));
}

template<typename R, typename D>
const stree::Symbol* random_by_arity(
    stree::Environment& env,
    stree::Arity arity,
    R& prng,
    D& value_dist)
{
    // TODO: oprimization, refactoring
    unsigned symbol_num = env.symbol_by_arity_num(arity);
    assert(symbol_num > 0);
    unsigned dist_max = (arity > 0 || std::is_same<D, NoValueDist>::value)
        ? symbol_num - 1
        : symbol_num;
    UniformUnsignedDist dist(0, dist_max);
    unsigned index = dist(prng);
    return (index < symbol_num)
        ? env.symbol_by_arity(arity, index)
        : nullptr;
}

}
