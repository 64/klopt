#pragma once
#include <phys_layout.hpp>
#include <layout.hpp>
#include <model.hpp>

class Optimizer {
    float initial_temp;
    int k_max;

public:
    Optimizer(float t0, int k_max) : initial_temp(t0), k_max(k_max) {}

    Layout compute_optimal(Model m, const std::string& text); 
};
