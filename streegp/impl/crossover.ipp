#include <stree/stree.hpp>

namespace stree { namespace gp {

inline void _common_region_point_swap(
    Environment& env, 
    CommonRegion::Item& point)
{
    Subtree subtree1(&env, nullptr, point.node1);
    // Subtree subtree2(&env, nullptr, point.node2);
    Tree subtree2_copy = Subtree(&env, nullptr, point.node2).copy();
    subtree1.swap(subtree2_copy.sub(0));
}

template<typename R>
Tree crossover_one_point(
    Tree tree1,
    const Tree& tree2,
    float p_term,
    R& prng)
{
    Environment* env = tree1.env();
    assert(tree2.env() == env);
    CommonRegion common = common_region(
        env,
        tree1.root(),
        const_cast<Id&>(tree2.root()),
        NodeCompare(env));
    if (common.size() > 0) {
        // Swap subtrees in common region
        NodeNum term_num = common.terminal_num();
        NodeNum nonterm_num = common.nonterminal_num();
        if (term_num > 0 || nonterm_num > 0) {
            // crossover point index in common region
            if (term_num == 0 || (nonterm_num > 0 && !_cointoss(prng, p_term))) {
                // Crossover point is non-terminal
                assert(nonterm_num > 0);
                UniformNodeNumDist dist(0, nonterm_num - 1);
                auto point = common.nth_nonterminal(dist(prng));
                _common_region_point_swap(*env, point);

            } else {
                // Crossover point is terminal
                assert(term_num > 0);
                UniformNodeNumDist dist(0, term_num - 1);
                auto point = common.nth_terminal(dist(prng));
                _common_region_point_swap(*env, point);
            }
        }
    }
    return std::move(tree1);
}

template<typename R>
Tree crossover_random(
    Tree tree1, const Tree& tree2,
    float p_term,
    R& prng)
{
    Environment* env = tree1.env();
    assert(tree2.env() == env);
    Subtree subtree1 = random_subtree(tree1, prng, p_term);
    Subtree subtree2 = random_subtree(tree2, prng, p_term);
    subtree1.replace(subtree2.copy());
    return tree1;
}

}}
