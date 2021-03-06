#include <cmath>
#include <random>
#include <thread>
#include <chrono>
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
OptResult Optimizer::simulated_annealing(Model m, std::string_view text) {
    // Prepare RNG
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_real_distribution<> distrib(0.0, 1.0);

    auto s_old = Layout::get_random(rng);
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

    return OptResult { s_best, e_best };
}

void Optimizer::thread_func(Model m,
        std::chrono::time_point<std::chrono::system_clock> end,
        OptResult& out,
        std::string_view text) {

    auto best = OptResult { Layout::get_qwerty(), -INFINITY };

    while (std::chrono::system_clock::now() < end) {
        auto cur = simulated_annealing(m, text);

        if (cur.score > best.score) {
            best = cur;
        }
    }

    out = best;
}

OptResult Optimizer::compute_optimal(Model m, int num_threads, int time_s, std::string_view text) {
    auto now = std::chrono::system_clock::now();
    auto end = now + std::chrono::seconds(time_s);

    auto threads = std::vector<std::thread>();
    auto out = std::vector<OptResult>(num_threads, OptResult { Layout::get_qwerty(), -INFINITY });

    for (int i = 0; i < num_threads; i++) {
        auto& thread_out = out[i];
        threads.emplace_back([&]{
            auto best = OptResult { Layout::get_qwerty(), -INFINITY };

            while (std::chrono::system_clock::now() < end) {
                auto cur = simulated_annealing(m, text);

                if (cur.score > best.score) {
                    best = cur;
                }
            }

            thread_out = best;
        });
    }

    auto best = OptResult { Layout::get_qwerty(), -INFINITY };
    for (int i = 0; i < num_threads; i++) {
        threads[i].join();

        auto& cur = out[i];
        if (cur.score > best.score) {
            best.layout = cur.layout;
            best.score = cur.score;
        }
    }

    return best;
}
