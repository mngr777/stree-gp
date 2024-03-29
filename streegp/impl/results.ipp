#include <algorithm>
#include <functional>
#include <cassert>

namespace stree { namespace gp {

template<typename I>
bool is_goal_achieved(
    Population<I>& population,
    Fitness goal,
    Evaluator<I> evaluator)
{
    return std::any_of(
        population.begin(), population.end(),
        [goal, evaluator](Individual& individual) {
            return individual.fitness(evaluator) <= goal;
        });
}

template<typename I>
bool is_goal_achieved(
    Group<I>& group,
    Fitness goal,
    Evaluator<I> evaluator)
{
    return std::any_of(
        group.begin(), group.end(),
        [goal, evaluator](auto& item) {
            Individual& individual = item.get();
            return individual.fitness(evaluator) <= goal;
        });
}

template<typename I>
Group<I> reap(Population<I>& population, unsigned k, Evaluator<I> evaluator) {
    // Evaluate population
    for (auto& individual : population)
        individual.eval(evaluator);

    Group<I> group;

    // Special cases
    if (k == 0 || population.empty()) {
        return group;
    } else if (k == 1) {
        auto it = std::max_element(
            population.begin(), population.end(),
            &more_fit);
        group.emplace_back(*it);
        return group;
    }

    // Counter
    typename Population<I>::size_type i = 0;

    // Add first k items
    for (; i < k && i < population.size(); ++i) {
        group.emplace_back(population[i]);
    }
    // Make heap, less fit on top
    std::make_heap(group.begin(), group.end(), &more_fit);

    // Iterate over population
    assert(!group.empty());
    for (; i < population.size(); ++i) {
        Individual& individual = population[i];
        if (more_fit(individual, group.front().get())) {
            // Replace the least fit individual in group
            std::pop_heap(group.begin(), group.end(), &more_fit);
            group.back() = std::ref(individual);
            std::push_heap(group.begin(), group.end(), &more_fit);
        }
    }

    // Sort
    using std::sort;
    sort(group.begin(), group.end(), &more_fit);

    return group;
}

template<typename I>
void update_hall_of_fame(Population<I>& hof, const Group<I> best, unsigned k) {
    assert(std::is_heap(hof.begin(), hof.end(), &more_fit));
    for (auto item : best) {
        const Individual& individual = item.get();
        if (hof.size() < k) {
            // Add individual
            hof.push_back(individual.copy(true));
            std::push_heap(hof.begin(), hof.end(), &more_fit);
        } else if (more_fit(individual, hof.front())) {
            // Replace the least fit individual
            std::pop_heap(hof.begin(), hof.end(), &more_fit);
            hof.back() = individual.copy(true);
            std::push_heap(hof.begin(), hof.end(), &more_fit);
        }
    }
}

template<typename I>
void sort_hall_of_fame(Population<I>& hof) {
    std::sort(hof.begin(), hof.end(), &more_fit);
}

}}
