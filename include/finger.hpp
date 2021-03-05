#pragma once
#include <cstddef>

class Finger {
public:
    enum Value {
        LEFT_PINKIE = 0,
        LEFT_RING,
        LEFT_MIDDLE,
        LEFT_INDEX,
        LEFT_THUMB,
        RIGHT_THUMB,
        RIGHT_INDEX,
        RIGHT_MIDDLE,
        RIGHT_RING,
        RIGHT_PINKIE,
    };

    static constexpr std::size_t NUM_FINGERS = 10;

private:
    Value v;

public:
    Finger(Value v) : v(v) {}
    operator Value() const { return v; };
    explicit operator bool() = delete;

    Finger get_opposite_pinkie() {
        switch (v) {
            case Finger::RIGHT_THUMB:
            case Finger::RIGHT_INDEX:
            case Finger::RIGHT_MIDDLE:
            case Finger::RIGHT_RING:
            case Finger::RIGHT_PINKIE:
                return Finger::LEFT_PINKIE;
            case Finger::LEFT_THUMB:
            case Finger::LEFT_INDEX:
            case Finger::LEFT_MIDDLE:
            case Finger::LEFT_RING:
            case Finger::LEFT_PINKIE:
            default:
                return Finger::RIGHT_PINKIE;
        }

    }
};

