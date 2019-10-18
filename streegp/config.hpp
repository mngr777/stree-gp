#ifndef STREEGP_CONFIG_HPP_
#define STREEGP_CONFIG_HPP_

#include <cassert>
#include <map>
#include <ostream>
#include <stdexcept>
#include <string>

#include <algorithm>
#include <vector>

namespace stree { namespace gp {

namespace conf {

/// General
const char PopulationSize[]           = "population_size";
const char PTermDefault[]             = "p_term_default";

/// Initialization
const char InitMaxDepthDefault[]      = "init.max_depth_default";
const char InitPTermDefault[]         = "init.max_depth_default";
// ramped_half_and_half
const char InitRampedMaxDepth[]       = "init.ramped.depth";
const char InitRampedPTermGrow[]      = "init.ramped.p_term_grow";
// grow
const char InitGrowMaxDepth[]         = "init.grow.max_depth";
const char InitGrowPTerm[]            = "init.grow.p_term";
// full
const char InitFullMaxDepth[]         = "init.full.max_depth";

/// Selection
const char SelectionTournamentSize[]  = "selection.tournament_size";

/// Mutation
const char MutationPTermDefault[]     = "mutation.p_term_default";
const char MutationPTermGrowDefault[] = "mutation.p_term_grow_default";
// subtree
const char MutationSubtreeDepth[]     = "mutation.subtree.depth";
const char MutationSubtreePTerm[]     = "mutation.subtree.p_term";
const char MutationSubtreePTermGrow[] = "mutation.subtree.p_term_grow";
// point
const char MutationPointPTerm[]       = "mutation.point.p_term";
// hoist
const char MutationHoistPTerm[]       = "mutation.hoist.p_term";

/// Crossover
const char CrossoverPTermDefault[]    = "crossover.p_term_default";
// one point
const char CrossoverOnePointPTerm[]   = "crossover.one_point.p_term";
// random
const char CrossoverRandomPTerm[]     = "crossover.random.p_term";

} // namespace conf


class Config;
Config make_config();

class Config {
    friend std::ostream& operator<<(std::ostream& os, const Config& config);

    template<typename V>
    using ValueMap = std::map<const std::string, V>;

public:
    Config()
        : order_(0),
          order_step_(5) {}

    // NOTE: no circularity check
    void add_fallback(const std::string& name, const std::string& fallback_name) {
        fallback_map_[name] = fallback_name;
    }

    template<typename V>
    V get(const std::string& name, std::string& actual) const {
        const ValueMap<V>& map = get_map<V>();
        return (map.count(name) == 1)
            ? map.at(name)
            : fallback<V>(name, actual);
    }

    template<typename V>
    V get(const std::string& name) const {
        std::string actual;
        return get<V>(name, actual);
    }

    void print(std::ostream& os, const std::string& name) const {
        Field field = get_field(name);
        std::string actual;
        switch (field.type) {
            case TypeUnsigned: {
                unsigned value = get<unsigned>(name, actual);
                os << value;
                break;
            }
            case TypeFloat: {
                float value = get<float>(name, actual);
                os << value;
                break;
            }
            default: assert(false);
        }
    }

    template<typename V>
    void set(const std::string& name, V value, unsigned order = 0) {
        // Add/update field
        if (field_map_.count(name) == 0) {
            // add field
            Field field(name, get_type<V>(), (order > 0 ? order : order_next()));
            field_map_.emplace(name, field);
        } else {
            // update field
            Field& field = field_map_.at(name);
            if (field.type != get_type<V>())
                throw std::invalid_argument("Field type doesn't match");
            if (order != 0)
                field.order = order;
        }
        // Set value
        get_map<V>()[name] = value;
    }

    unsigned order() const {
        return order_;
    }

    void set_order(unsigned order) {
        order_ = order;
    }

    void set_order_step(unsigned order_step) {
        order_step_ = order_step;
    }

private:
    enum Type {
        TypeUnsigned,
        TypeFloat
    };

    struct Field {
        Field(const std::string& name, Type type, unsigned order)
            : name(name), type(type), order(order) {}
        std::string name;
        Type type;
        unsigned order;
    };

    struct CompareFields {
        bool operator()(const Field& field1, const Field& field2) {
            return field1.order < field2.order;
        }
    };

    template<typename V>
    Type get_type() {
        if (std::is_same<V,unsigned>::value) {
            return TypeUnsigned;
        } else if (std::is_same<V, float>::value) {
            return TypeFloat;
        } else {
            throw std::invalid_argument("Invalid field type");
        }
        assert(false);
    }

    Field get_field(const std::string& name) const {
        if (field_map_.count(name) == 0)
            throw std::out_of_range(std::string("Field `") + name + "' not found");
        return field_map_.at(name);
    }

    template<typename V>
    ValueMap<V>& get_map() {
        throw std::invalid_argument("Invalid field type");
    }

    template<typename V>
    const ValueMap<V>& get_map() const {
        throw std::invalid_argument("Invalid field type");
    }

    template<typename V>
    V fallback(const std::string& name, std::string& actual) const {
        if (fallback_map_.count(name) == 0)
            throw std::out_of_range(
                std::string("Value `") + name + "' not found");
        actual = fallback_map_.at(name); // use [] ??
        return get<V>(actual, actual);
    }

    unsigned order_next() {
        unsigned result = order_;
        order_ += order_step_;
        return result;
    }

    unsigned order_;
    unsigned order_step_;
    std::map<const std::string, Field> field_map_;
    ValueMap<unsigned> map_unsigned_;
    ValueMap<float> map_float_;
    std::map<const std::string, std::string> fallback_map_;
};

}}

#include "impl/config.ipp"

#endif
