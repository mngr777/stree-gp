#include <random>
#include <type_traits>
#include <stree/stree.hpp>

namespace streegp {

template<typename R>
bool _cointoss(R& prng, float p) {
    return std::bernoulli_distribution{p}(prng);
}

template<typename R, typename D>
const stree::Symbol* random_term(stree::Environment& env, R& prng, D& value_dist) {
    unsigned term_num = env.terminal_num();
    assert(term_num > 1);
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
    assert(nonterm_num > 1);
    UniformUnsignedDist dist(0, nonterm_num - 1);
    return env.nonterminal(dist(prng));
}

}
