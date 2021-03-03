#pragma once
#include <string>
#include <unordered_map>
#include <phys_key.hpp>

class PhysLayout{ 
    std::unordered_map<std::string, PhysKey> key_map;
    PhysLayout(std::unordered_map<std::string, PhysKey> key_map) : key_map(key_map) {}

public:
    PhysKey& operator[](const std::string& s) { return key_map.at(s); }

    static PhysLayout get_iso_gb();
};
