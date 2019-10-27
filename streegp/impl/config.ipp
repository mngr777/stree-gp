#include <boost/optional.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/info_parser.hpp>

namespace stree { namespace gp {

// TODO: use sections
std::ostream& operator<<(std::ostream& os, const stree::gp::Config& config) {
    config.write(os);
    return os;
}

namespace {

template<typename V>
void copy_from_ptree(
    Config& config,
    const boost::property_tree::ptree& ptree,
    const std::string& name)
{
    boost::optional<V> value = ptree.get_optional<V>(name);
    if (value)
        config.set<V>(name, *value);
}

template<typename V>
void copy_to_ptree(
    const Config& config,
    boost::property_tree::ptree& ptree,
    const std::string& name)
{
    std::string actual;
    V value = config.get<V>(name, actual);
    if (actual == name)
        ptree.put<V>(name, value);
}

} // empty namespace

void Config::read(std::istream& is) {
    namespace pt = boost::property_tree;

    // Load data into ptree
    pt::ptree ptree;
    pt::info_parser::read_info(is, ptree);

    // Read each field value from ptree
    for (const auto& pair : field_map_) {
        const auto& name = pair.first;
        const auto& field  = pair.second;
        switch (field.type) {
            case TypeUnsigned: {
                copy_from_ptree<unsigned>(*this, ptree, name);
                break;
            }
            case TypeFloat: {
                copy_from_ptree<float>(*this, ptree, name);
                break;
            }
            default: assert(false && "Invalid field type");
        }
    }
}

void Config::write(std::ostream& os) const {
    namespace pt = boost::property_tree;

    // Copy data to ptree
    pt::ptree ptree;
    auto fields = sorted_fields();
    for (const auto& field : fields) {
        switch (field.type) {
            case TypeUnsigned: {
                copy_to_ptree<unsigned>(*this, ptree, field.name);
                break;
            }
            case TypeFloat: {
                copy_to_ptree<float>(*this, ptree, field.name);
                break;
            }
            default: assert(false && "Invaid field type");
        }
    }

    // Write ptree data
    pt::info_parser::write_info(os, ptree);
}


template<>
Config::ValueMap<unsigned>& Config::get_map() {
    return map_unsigned_;
}

template<>
Config::ValueMap<float>& Config::get_map() {
    return map_float_;
}

template<>
const Config::ValueMap<unsigned>& Config::get_map() const {
    return map_unsigned_;
}

template<>
const Config::ValueMap<float>& Config::get_map() const {
    return map_float_;
}


Config make_default_config() {
    using namespace conf;

    Config config;

    /// General
    config.set_order(0);
    config.set<unsigned>(PopulationSize, 100);
    config.set<float>(PTermDefault, 0.1);

    /// Initialization
    config.set_order(100);
    config.set<unsigned>(InitMaxDepthDefault, 5);
    config.add_fallback<float>(InitPTermDefault, PTermDefault);
    // ramped_half_and_half
    config.add_fallback<unsigned>(InitRampedMaxDepth, InitMaxDepthDefault);
    config.add_fallback<float>(InitRampedPTermGrow, InitPTermDefault);
    // grow
    config.add_fallback<unsigned>(InitGrowMaxDepth, InitMaxDepthDefault);
    config.add_fallback<float>(InitGrowPTerm, InitPTermDefault);
    // full
    config.add_fallback<unsigned>(InitFullMaxDepth, InitMaxDepthDefault);


    /// Selection
    config.set_order(200);
    config.set<unsigned>(SelectionTournamentSize, 5);

    /// Mutation
    config.set_order(300);
    config.add_fallback<float>(MutationPTermDefault, PTermDefault);
    config.add_fallback<float>(MutationPTermGrowDefault, PTermDefault);
    // subtree
    config.set<unsigned>(MutationSubtreeDepth, 5);
    config.add_fallback<float>(MutationSubtreePTerm, MutationPTermDefault);
    config.add_fallback<float>(MutationSubtreePTermGrow, MutationPTermDefault);
    // point
    config.add_fallback<float>(MutationPointPTerm, MutationPTermDefault);
    // hoist
    config.add_fallback<float>(MutationHoistPTerm, MutationPTermDefault);

    /// Crossover
    config.set_order(400);
    config.add_fallback<float>(CrossoverPTermDefault, PTermDefault);
    // one point
    config.add_fallback<float>(CrossoverOnePointPTerm, CrossoverPTermDefault);
    // random
    config.add_fallback<float>(CrossoverRandomPTerm, CrossoverPTermDefault);

    return config;
}

}}
