#ifndef STREEGP_TESTS_INDIV_HPP_
#define STREEGP_TESTS_INDIV_HPP_

#include <stree/stree.hpp>

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

#endif
