#pragma once
#include <string>
#include <unordered_map>
#include <phys_key.hpp>

class PhysLayout{ 
    std::unordered_map<std::string, PhysKey> key_map;
    PhysLayout(std::unordered_map<std::string, PhysKey> key_map) : key_map(key_map) {}

public:
    PhysKey& operator[](const std::string& s) { return key_map.at(s); }
    PhysKey& operator[](char c) { return key_map.at(std::string(1, c)); }

    static PhysLayout get_iso_gb();
};
