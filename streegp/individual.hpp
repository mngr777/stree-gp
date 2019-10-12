#ifndef STREEGP_INDIVIDUAL_HPP_
#define STREEGP_INDIVIDUAL_HPP_

#include <functional>
#include <vector>
#include <stree/stree.hpp>

namespace stree { namespace gp {

using Fitness = float;

template<typename I>
using Population = std::vector<I>;

template<typename I>
using Group = std::vector<std::reference_wrapper<I>>;

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

    Individual(const Individual&) = delete;

    Individual(Individual&& other)
        : tree_(std::move(other.tree_)),
          fitness_(other.fitness_),
          has_fitness_(other.has_fitness_) {}

    virtual ~Individual() {}

    Individual& operator=(const Individual&) = delete;

    Individual& operator=(Individual&& other) {
        std::swap(tree_, other.tree_);
        fitness_ = other.fitness_;
        has_fitness_ = other.has_fitness_;
        return *this;
    }

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
