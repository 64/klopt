#pragma once
#include <cmath>
#include <string>
#include <unordered_map>
#include <finger.hpp>

struct PhysKey {
    float abs_x, abs_y;
    Finger finger;

    PhysKey() : abs_x(0.0f), abs_y(0.0f), finger(Finger::LEFT_PINKIE) {}
    PhysKey(float x, float y, Finger f) : abs_x(x), abs_y(y), finger(f) {}

    bool operator!=(const PhysKey& other) const { return !operator==(other); }
    bool operator==(const PhysKey& other) const {
        return (this->abs_x == other.abs_x)
            && (this->abs_y == other.abs_y)
            && (this->finger == other.finger);
    }

    float distance_to(const PhysKey& other) const {
        return weighted_distance_to(other, 1.0f, 1.0f);
    }

    float weighted_distance_to(const PhysKey& other, float x_weight, float y_weight) const {
        float x_diff = (abs_x - other.abs_x) * x_weight;
        float y_diff = (abs_y - other.abs_y) * y_weight;
        return std::sqrt(x_diff * x_diff + y_diff * y_diff);
    }
};
