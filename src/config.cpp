#include <streegp/config.hpp>

namespace stree { namespace gp {

std::ostream& operator<<(std::ostream& os, const stree::gp::Config& config) {
    config.write(os);
    return os;
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


bool Config::CompareFields::operator()(
    const Config::Field& field1, const Config::Field& field2)
{
    return field1.order < field2.order;
}

std::vector<Config::Field> Config::sorted_fields() const {
    // Get fields
    std::vector<Field> fields;
    for (const auto& item : field_map_)
        fields.push_back(item.second);

    // Sort fields
    std::sort(fields.begin(), fields.end(), CompareFields());

    return fields;
}

void Config::add_or_update_field(
    const std::string name,
    Config::Type type,
    unsigned order)
{
    if (field_map_.count(name) == 0) {
        // add field
        Field field(name, type, (order > 0 ? order : order_next()));
        field_map_.emplace(name, field);
    } else {
        // update field
        Field& field = field_map_.at(name);
        if (field.type != type)
            throw std::invalid_argument("Field type doesn't match");
        if (order != 0)
            field.order = order;
    }
}

Config::Field Config::get_field(const std::string& name) const {
    if (field_map_.count(name) == 0)
        throw std::out_of_range(std::string("Field `") + name + "' not found");
    return field_map_.at(name);
}

unsigned Config::order_next() {
    unsigned result = order_;
    order_ += order_step_;
    return result;
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

}}
