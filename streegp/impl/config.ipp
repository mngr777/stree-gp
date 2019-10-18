namespace stree { namespace gp {

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
        os << field.name << " = ";
        config.print(os, field.name);
        os << std::endl;
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
    config.add_fallback(InitPTermDefault, PTermDefault);
    // ramped_half_and_half
    config.add_fallback(InitRampedMaxDepth, InitMaxDepthDefault);
    config.add_fallback(InitRampedPTermGrow, InitPTermDefault);
    // grow
    config.add_fallback(InitGrowMaxDepth, InitMaxDepthDefault);
    config.add_fallback(InitGrowPTerm, InitPTermDefault);
    // full
    config.add_fallback(InitFullMaxDepth, InitMaxDepthDefault);


    /// Selection
    config.set_order(200);
    config.set<unsigned>(SelectionTournamentSize, 5);

    /// Mutation
    config.set_order(300);
    config.add_fallback(MutationPTermDefault, PTermDefault);
    config.add_fallback(MutationPTermGrowDefault, PTermDefault);
    // subtree
    config.set<unsigned>(MutationSubtreeDepth, 5);
    config.add_fallback(MutationSubtreePTerm, MutationPTermDefault);
    config.add_fallback(MutationSubtreePTermGrow, MutationPTermDefault);
    // point
    config.add_fallback(MutationPointPTerm, MutationPTermDefault);
    // hoist
    config.add_fallback(MutationHoistPTerm, MutationPTermDefault);

    /// Crossover
    config.set_order(400);
    config.add_fallback(CrossoverPTermDefault, PTermDefault);
    // one point
    config.add_fallback(CrossoverOnePointPTerm, CrossoverPTermDefault);
    // random
    config.add_fallback(CrossoverRandomPTerm, CrossoverPTermDefault);

    return config;
}

}}
