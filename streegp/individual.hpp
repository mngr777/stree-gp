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
using Evaluator = std::function<Fitness(I&)>;

class Individual;
void swap(Individual& individual1, Individual& individual2);

bool more_fit(Individual& individual1, Individual& individual2);
bool less_fit(Individual& individual1, Individual& individual2);


// TODO: refactoring: 

class Individual {
public:
    Individual(Tree&& tree)
        : tree_(std::move(tree)),
         fitness_(-1.0) {}

    Individual(const Individual&) = delete;

    Individual(Individual&& other)
        : tree_(std::move(other.tree_)),
          fitness_(other.fitness_) {}

    virtual ~Individual() {}

    Individual& operator=(const Individual&) = delete;

    Individual& operator=(Individual&& other) {
        swap(other);
        return *this;
    }

    void swap(Individual& other) {
        tree_.swap(other.tree_);
        std::swap(fitness_, other.fitness_);
    }

    Individual copy() const {
        return Individual(tree_.sub(0).copy());
    }

    Tree& tree() {
        return tree_;
    }

    const Tree& tree() const {
        return tree_;
    }

    void eval(Evaluator<Individual> evaluator, bool force = false) {
        if (!has_fitness() || force)
            fitness_ = evaluator(*this);
    }

    Fitness fitness() const {
        return fitness_;
    }

    bool has_fitness() const {
        return !(fitness_ < 0);
    }

    virtual Fitness fitness(Evaluator<Individual> evaluator) {
        eval(evaluator);
        return fitness_;
    }

protected:
    Tree tree_;
    Fitness fitness_;
};


void swap(Individual& individual1, Individual& individual2) {
    individual1.swap(individual2);
}

bool more_fit(Individual& individual1, Individual& individual2) {
    return individual1.fitness() < individual2.fitness();
}

bool less_fit(Individual& individual1, Individual& individual2) {
    return individual1.fitness() > individual2.fitness();
}

}}

#endif
