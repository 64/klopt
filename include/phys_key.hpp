#pragma once
#include <cmath>
#include <string>
#include <unordered_map>
#include <finger.hpp>

class PhysKey {
    float abs_x, abs_y;
    Finger finger;

public:
    PhysKey() : abs_x(0.0f), abs_y(0.0f) {}
    PhysKey(float x, float y, Finger f) : abs_x(x), abs_y(y), finger(f) {}
    Finger get_finger() { return finger; }

    bool operator==(const PhysKey& other) const {
        return (this->abs_x == other.abs_x)
            && (this->abs_y == other.abs_y)
            && (this->finger == other.finger);
    }

    float distance_to(const PhysKey& other) const {
        float x_diff = abs_x - other.abs_x;
        float y_diff = abs_y - other.abs_y;
        return std::sqrt(x_diff * x_diff + y_diff * y_diff);
    }

    static std::unordered_map<std::string, PhysKey> phys_key_positions();
};
