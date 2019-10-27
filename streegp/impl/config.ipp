#include <boost/optional.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/info_parser.hpp>

namespace stree { namespace gp {

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

template<>
Config::ValueMap<unsigned>& Config::get_map();

template<>
Config::ValueMap<float>& Config::get_map();

template<>
const Config::ValueMap<unsigned>& Config::get_map() const;

template<>
const Config::ValueMap<float>& Config::get_map() const;

}}
