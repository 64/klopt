#pragma once
#include <array>
#include <limits>
#include <initializer_list>
#include <string_view>
#include <optional>
#include <random>
#include <key_combo.hpp>
#include <phys_layout.hpp>

struct Layout {
    // Indexed by char value
    std::array<std::optional<KeyCombo>, std::numeric_limits<char>::max() + 1> key_map;

    // Indexed by finger
    std::array<PhysKey, Finger::NUM_FINGERS> home_row;

    Layout(PhysLayout phys_map,
            std::initializer_list<std::pair<char, KeyCombo>> char_key_map,
            std::initializer_list<PhysKey> home_row);

    Layout(PhysLayout phys_map, std::string_view format);

    Layout mutate(std::mt19937& rng) const;
    void print() const;

    static Layout get_qwerty();
    static Layout get_random(std::mt19937& rng);
    static Layout from_string(std::string_view format);
};
