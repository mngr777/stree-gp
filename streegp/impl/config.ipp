namespace stree { namespace gp {

// TODO: use sections
std::ostream& operator<<(std::ostream& os, const stree::gp::Config& config) {
    // Get fields
    std::vector<stree::gp::Config::Field> fields;
    for (const auto& item : config.field_map_)
        fields.push_back(item.second);

    // Sort fields
    std::sort(
        fields.begin(), fields.end(),
        typename stree::gp::Config::CompareFields());

    // Print field names and values
    for (const auto& field : fields) {
        config.print(os, field.name);
    }
    return os;
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


Config make_config() {
    using namespace conf;
    std::string prefix;

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
