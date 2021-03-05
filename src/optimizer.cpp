#include <cmath>
#include <random>
#include <optimizer.hpp>
#include <model.hpp>

float temperature(float initial_temp, int k, int k_max) {
    return initial_temp * std::exp(-static_cast<float>(k) / k_max);
}

float transition_prob(float e_old, float e_new, float temp) {
    if (e_new > e_old) {
        return 1.0;
    } else {
        return std::exp((e_old - e_new)/temp);
    }
}

float energy(const Model& m, const Layout& layout, std::string_view text) {
    return m.score_text(layout, text);
}

// https://en.wikipedia.org/wiki/Simulated_annealing#Pseudocode
Layout Optimizer::compute_optimal(Model m, const std::string& text) {
    // Prepare RNG
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_real_distribution<> distrib(0.0, 1.0);

    // TODO: Randomize starting layout
    auto s_old = Layout::get_qwerty();
    auto e_old = energy(m, s_old, text);

    auto s_best = s_old;
    auto e_best = e_old;

    for (int k = 0; k < k_max; k++) {
        auto temp = temperature(initial_temp, k, k_max);

        auto s_new = s_old.mutate(rng);
        auto e_new = energy(m, s_new, text);

        auto p = transition_prob(e_old, e_new, temp);
        if (p > distrib(rng)) {
            // Accept s_new
            e_old = e_new;
            s_old = s_new;
        }

        // Update best
        if (e_new > e_best) {
            e_best = e_new;
            s_best = s_new;
        }
    }

    return s_best;
}
