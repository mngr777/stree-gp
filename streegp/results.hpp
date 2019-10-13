#ifndef STREEGP_RESULTS_HPP_
#define STREEGP_RESULTS_HPP_

#include <algorithm>
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

}}

#include "impl/results.ipp"

#endif
