#include <streegp/individual.hpp>

namespace stree { namespace gp {

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
