#pragma once
#include <array>
#include <limits>
#include <initializer_list>
#include <string_view>
#include <optional>
#include <key_press.hpp>

class Layout {
private:
    // Indexed by char value
    std::array<std::optional<KeyPress>, std::numeric_limits<char>::max() + 1> key_map;

public:
    Layout(std::initializer_list<std::pair<char, KeyPress>> char_key_map);

    float score_text(std::string_view text);

    static Layout get_qwerty();
};
