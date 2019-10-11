#ifndef STREEGP_INDIVIDUAL_HPP_
#define STREEGP_INDIVIDUAL_HPP_

#include <vector>
#include <stree/stree.hpp>

namespace stree { namespace gp {

using Fitness = float;

template<typename I>
using Population = std::vector<I>;

using IndividualIndex = std::size_t;
const IndividualIndex NoIndividualIndex = -1;

template<typename I>
using FitnessGetter = std::function<Fitness(I&)>;

template<typename I>
Fitness get_fitness(I& individual) {
    return individual.fitness();
}

class Individual {
public:
    Individual(Tree&& tree)
        : tree_(std::move(tree)),
         fitness_(0.0),
         has_fitness_(false) {}

    virtual ~Individual() {}

    Tree& tree() {
        return tree_;
    }

    const Tree& tree() const {
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
    Tree tree_;
    Fitness fitness_;
    bool has_fitness_;
};

}}

#endif
