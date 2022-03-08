#ifndef STREEGP_RESULTS_HPP_
#define STREEGP_RESULTS_HPP_

#include <stree/stree.hpp>
#include <streegp/individual.hpp>

namespace stree { namespace gp {

template<typename I>
bool is_goal_achieved(
    Population<I>& population,
    Fitness goal,
    Evaluator<I> evaluator);

template<typename I>
bool is_goal_achieved(
    Group<I>& group,
    Fitness goal,
    Evaluator<I> evaluator);


template<typename I>
Group<I> reap(Population<I>& population, unsigned k, Evaluator<I> evaluate);

template<typename I>
void update_hall_of_fame(Population<I>& hof, const Group<I> best, unsigned k);

template<typename I>
void sort_hall_of_fame(Population<I>& hof);

}}

#include "impl/results.ipp"

#endif
