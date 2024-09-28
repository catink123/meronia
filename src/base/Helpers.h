#pragma once
#include <stdexcept>
#include <utility>
#include <vector>
#include "CommonConstants.h"
#include <SFML/Graphics/View.hpp>

#define DECLARE_RUNTIME_ERROR(Name) \
class Name : public std::runtime_error \
{ \
public: \
    Name(const std::string& msg): std::runtime_error(msg) \
    { \
    } \
};

template <typename K, typename V>
using UnsortedMap = std::vector<std::pair<K, V>>;

template<typename UnsortedMapT>
class UnsortedMapFinder
{
public:
    using Key = UnsortedMapT::value_type::first_type;
    using Value = UnsortedMapT::value_type::second_type;

public:
    UnsortedMapFinder() = delete;

public:
    static UnsortedMapT::const_iterator FindByKey(const UnsortedMapT& map, const Key& key)
    {
        return std::find_if(std::begin(map), std::end(map), [&](const auto& pair) { return pair.first == key; });
    }

    static UnsortedMapT::const_iterator FindByValue(const UnsortedMapT& map, const Value& value)
    {
        return std::find_if(std::begin(map), std::end(map), [&](const auto& pair) { return pair.second == value; });
    }
};

inline sf::Vector2f TranslateToViewCoords(const sf::Vector2f& point, const sf::View& view)
{
    return point - view.getViewport().getPosition();
}