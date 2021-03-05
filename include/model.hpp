#pragma once
#include <layout.hpp>

class Model {
    float repeated_finger_penalty = 1.0f;
    float non_home_row_penalty = 0.5f;

    std::array<float, Finger::NUM_FINGERS> finger_penalties = {
        0.85f, // Left pinkie
        0.45f, // Left ring
        0.25f, // Left middle
        0.20f, // Left index
        0.40f, // Left thumb
        0.40f, // Right thumb
        0.20f, // Right index
        0.20f, // Right middle
        0.40f, // Right ring
        0.80f, // Right pinkie
    };

public:
    Model() {}

    float score_text(const Layout& layout, std::string_view text) const;
};
