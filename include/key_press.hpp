#pragma once
#include <iterator>
#include <phys_key.hpp>

struct KeyPress {
    PhysKey main;
    std::tuple<std::optional<PhysKey>, std::optional<PhysKey>> modifiers;

    KeyPress(PhysKey key) : main(key) {}
    KeyPress(PhysKey key, PhysKey modA) : main(key), modifiers({ modA, std::nullopt }) {}
    KeyPress(PhysKey key, PhysKey modA, PhysKey modB) : main(key), modifiers({ modA, modB }) {}

    class KeyPressIterator {
        KeyPress& press;
        int index = 0;

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = PhysKey;
        using difference_type = int;
        using pointer_type = PhysKey*;
        using reference = PhysKey&;

        KeyPressIterator(KeyPress& press) : press(press) {}
        KeyPressIterator(KeyPress& press, int index) : press(press), index(index) {}

        bool operator==(const KeyPressIterator& other) { return this->index == other.index; }
        bool operator!=(const KeyPressIterator& other) { return this->index != other.index; }

        KeyPressIterator begin() { return KeyPressIterator(press, 0); }
        KeyPressIterator end() { return KeyPressIterator(press, -1); }

        KeyPressIterator& operator++() {
            bool exists;
            switch (index + 1) {
                case 1:
                    exists = std::get<0>(press.modifiers).has_value();
                    break;
                case 2:
                    exists = std::get<1>(press.modifiers).has_value();
                    break;
                default:
                    exists = false;
                    break;
            }

            if (exists)
                index++;
            else
                index = -1;

            return *this;
        }

        KeyPressIterator operator++(int) {
            KeyPressIterator old = *this;
            operator++();
            return old;
        }

        PhysKey* operator->() {
            switch (index) {
                case 0:
                    return &press.main;
                case 1:
                    return &std::get<0>(press.modifiers).value();
                case 2:
                    return &std::get<1>(press.modifiers).value();
                default:
                    throw std::out_of_range("KeyPressIterator index");
            }
        }

        PhysKey& operator*() {
            switch (index) {
                case 0:
                    return press.main;
                case 1:
                    return std::get<0>(press.modifiers).value();
                case 2:
                    return std::get<1>(press.modifiers).value();
                default:
                    throw std::out_of_range("KeyPressIterator index");
            }
        }
    };

    KeyPressIterator begin() { return KeyPressIterator(*this).begin(); }
    KeyPressIterator end() { return KeyPressIterator(*this).end(); }
};
