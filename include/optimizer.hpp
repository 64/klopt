#pragma once
#include <chrono>
#include <phys_layout.hpp>
#include <layout.hpp>
#include <model.hpp>

struct OptResult {
    Layout layout;
    float score;
};

class Optimizer {
    float initial_temp;
    int k_max;

public:
    Optimizer(float t0, int k_max) : initial_temp(t0), k_max(k_max) {}

    OptResult compute_optimal(Model m, int num_threads, int time_s, std::string_view text); 
    OptResult simulated_annealing(Model m, std::string_view text);
    void thread_func(Model m, std::chrono::time_point<std::chrono::system_clock> end, OptResult& out, std::string_view text);
};
