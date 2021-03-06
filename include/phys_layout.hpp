#pragma once
#include <string>
#include <unordered_map>
#include <phys_key.hpp>

struct PhysLayout{ 
    std::unordered_map<std::string, PhysKey> key_map;
    std::array<PhysKey, Finger::NUM_FINGERS> home_row;

    PhysLayout(std::unordered_map<std::string, PhysKey> key_map,
            const std::array<PhysKey, Finger::NUM_FINGERS>& home_row) : key_map(key_map), home_row(home_row) {}

    PhysKey& operator[](const std::string& s) { return key_map.at(s); }
    PhysKey& operator[](char c) { return key_map.at(std::string(1, c)); }

    std::string stringify(const struct Layout &layout);

    static PhysLayout get_iso_gb();
};
