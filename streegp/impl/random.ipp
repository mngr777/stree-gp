#include <random>
#include <type_traits>
#include <stree/stree.hpp>

namespace stree { namespace gp {

template<typename R>
bool _cointoss(R& prng, float p) {
    return std::bernoulli_distribution{p}(prng);
}

template<typename R>
Subtree random_subtree(Tree& tree, R& prng, float p_term) {
    assert(tree.is_valid());
    auto desc = tree.describe();
    assert(desc.term_num > 0);
    // Choose terminal or non-terminal
    bool use_term = (desc.nonterm_num == 0) || _cointoss(prng, p_term);
    NodeNum n_max = use_term ? desc.term_num - 1 : desc.nonterm_num - 1;
    // Select random subtree
    NodeFilter filter;
    filter.is_terminal = use_term ? IsTerminalYes : IsTerminalNo;
    return tree.sub(UniformNodeNumDist{0, n_max}(prng), filter);
}

template<typename R, typename D>
const SymbolPtr random_term(Environment& env, R& prng, D& value_dist) {
    unsigned term_num = env.symbols().terminals().size();
    assert(term_num > 0);
    unsigned dist_max = std::is_same<D, NoValueDist>::value
        ? term_num - 1
        : term_num;
    UniformUnsignedDist dist(0, dist_max);
    unsigned index = dist(prng);
    return (index < term_num)
        ? env.symbols().terminals()[index]
        : nullptr;
}

template<typename R>
const SymbolPtr random_nonterm(Environment& env, R& prng) {
    unsigned nonterm_num = env.symbols().nonterminals().size();
    assert(nonterm_num > 0);
    UniformUnsignedDist dist(0, nonterm_num - 1);
    return env.symbols().nonterminals()[dist(prng)];
}

template<typename R, typename D>
const SymbolPtr random_by_arity(
    Environment& env,
    Arity arity,
    R& prng,
    D& value_dist)
{
    // TODO: oprimization, refactoring
    const SymbolPtrList& symbols = env.symbols().list_by_arity(arity);
    auto symbol_num = symbols.size();
    assert(symbol_num > 0);
    unsigned dist_max = (arity > 0 || std::is_same<D, NoValueDist>::value)
        ? symbol_num - 1
        : symbol_num;
    UniformUnsignedDist dist(0, dist_max);
    unsigned index = dist(prng);
    return (index < symbol_num)
        ? symbols[index]
        : SymbolPtr();
}

}}
