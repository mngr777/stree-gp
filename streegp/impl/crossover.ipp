#include <stree/stree.hpp>

namespace streegp {

void _common_region_point_swap(
    stree::Environment& env, 
    stree::CommonRegion::Item& point,
    bool *success)
{
    // Swap if not root node
    if (point.n != 0) {
        stree::Subtree subtree1(&env, nullptr, point.node1);
        stree::Subtree subtree2(&env, nullptr, point.node2);
        subtree1.swap(subtree2);
        if (success)
            *success = true;
    }
}

template<typename R>
TreeList crossover_one_point(
    stree::Tree tree1,
    stree::Tree tree2,
    R& prng,
    float p_term = 0.2,
    bool *success = nullptr)
{
    if (success)
        *success = false;

    stree::Environment* env = tree1.env();
    assert(tree2.env() == env);
    stree::CommonRegion common_region = stree::common_region(
        env,
        tree1.root(),
        tree2.root(),
        stree::NodeCompare(env));
    if (common_region.size() > 0) {
        // Swap subtrees in common region
        stree::NodeNum term_num = common_region.terminal_num();
        stree::NodeNum nonterm_num = common_region.nonterminal_num();
        if (term_num > 0 || nonterm_num > 0) {
            // crossover point index in common region
            if (term_num == 0 || (nonterm_num > 0 && !_cointoss(prng, p_term))) {
                // Crossover point is non-terminal
                assert(nonterm_num > 0);
                UniformNodeNumDist dist(0, nonterm_num - 1);
                auto point = common_region.nth_nonterminal(dist(prng));
                _common_region_point_swap(*env, point, success);

            } else {
                // Crossover point is terminal
                assert(term_num > 0);
                UniformNodeNumDist dist(0, term_num - 1);
                auto point = common_region.nth_terminal(dist(prng));
                _common_region_point_swap(*env, point, success);
            }
        }
    }
    return TreeList(std::move(tree1), std::move(tree2));
}

}
