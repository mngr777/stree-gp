#ifndef STREEGP_TESTS_INDIV_HPP_
#define STREEGP_TESTS_INDIV_HPP_

#include <stree/stree.hpp>
#include <streegp/streegp.hpp>

class Individual;
using Population = std::vector<Individual>;
using Fitness = float;

class Individual {
public:
    Individual(stree::Tree&& tree)
        : tree_(std::move(tree)),
         fitness_(0.0),
         has_fitness_(false) {}

    stree::Tree& tree() {
        return tree_;
    }

    const stree::Tree& tree() const {
        return tree_;
    }

    void set_fitness(float fitness) {
        fitness_ = fitness;
        has_fitness_ = true;
    }

    Fitness fitness() const {
        return fitness_;
    }

    bool has_fitness() const {
        return has_fitness_;
    }

protected:
    stree::Tree tree_;
    Fitness fitness_;
    bool has_fitness_;
};

template<typename P, typename D>
Population ramped_half_and_half(
    stree::Environment& env,
    unsigned size,
    unsigned max_depth,
    float p_term_grow,
    P& prng,
    D& value_dist)
{
    Population population;

    unsigned i = 0;
    // grow
    for (; i < size / 2; ++i)
        population.emplace_back(
            streegp::grow(env, max_depth, p_term_grow, prng, value_dist));
    // full
    for (; i < size; ++i)
        population.emplace_back(
            streegp::full(env, max_depth, prng, value_dist));

    return population;
}

template<typename P>
Population ramped_half_and_half(
    stree::Environment& env,
    unsigned size,
    unsigned max_depth,
    float p_term_grow,
    P& prng)
{
    streegp::NoValueDist value_dist;
    return ramped_half_and_half(env, size, max_depth, p_term_grow, prng, value_dist);
}

#endif
