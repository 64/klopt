#pragma once
#include <iterator>
#include <phys_key.hpp>

// This is pretty hacky... but it seems like the nicest interface without including some small_vector library
// I think I can make it work nicely with ranges and a std::array<std::optional<PhysKey>, 3>
struct KeyCombo {
    PhysKey main;
    std::tuple<std::optional<PhysKey>, std::optional<PhysKey>> modifiers;

    KeyCombo(PhysKey key) : main(key) {}
    KeyCombo(PhysKey key, PhysKey modA) : main(key), modifiers({ modA, std::nullopt }) {}
    KeyCombo(PhysKey key, PhysKey modA, PhysKey modB) : main(key), modifiers({ modA, modB }) {}

    class KeyComboIterator {
        KeyCombo& press;
        int index = 0;

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = PhysKey;
        using difference_type = int;
        using pointer_type = PhysKey*;
        using reference = PhysKey&;

        KeyComboIterator(KeyCombo& press) : press(press) {}
        KeyComboIterator(KeyCombo& press, int index) : press(press), index(index) {}

        bool operator==(const KeyComboIterator& other) { return this->index == other.index; }
        bool operator!=(const KeyComboIterator& other) { return this->index != other.index; }

        KeyComboIterator begin() { return KeyComboIterator(press, 0); }
        KeyComboIterator end() { return KeyComboIterator(press, -1); }

        KeyComboIterator& operator++() {
            bool exists;
            // TODO: It would be nice to reduce the repitition of this switch
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

        KeyComboIterator operator++(int) {
            KeyComboIterator old = *this;
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
                    throw std::out_of_range("KeyComboIterator index out of range");
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
                    throw std::out_of_range("KeyComboIterator index out of range");
            }
        }
    };

    KeyComboIterator begin() { return KeyComboIterator(*this).begin(); }
    KeyComboIterator end() { return KeyComboIterator(*this).end(); }
};
