#pragma once
#include <array>
#include <limits>
#include <initializer_list>
#include <string_view>
#include <optional>
#include <key_combo.hpp>
#include <phys_layout.hpp>

class Layout {
private:
    // Indexed by char value
    std::array<std::optional<KeyCombo>, std::numeric_limits<char>::max() + 1> key_map;
    PhysLayout phys_map;

public:
    Layout(PhysLayout phys_map, std::initializer_list<std::pair<char, KeyCombo>> char_key_map);

    float score_text(std::string_view text);

    static Layout get_qwerty();
};
