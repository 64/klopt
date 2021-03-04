#pragma once
#include <layout.hpp>

class Model {
    float dummy = 0.0f;

public:
    Model() {}

    float score_text(const Layout& layout, std::string_view text) const;
};
