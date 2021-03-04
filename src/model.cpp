#include <model.hpp>

float Model::score_text(const Layout& layout, std::string_view text) const {
    float penalty = 0.0f;

    auto last_finger_pos = layout.home_row;

    for (auto c : text) {
        KeyCombo next_key_seq = layout.key_map[c].value();

        // Some characters require more than one key press (e.g uppercase characters)
        for (PhysKey next_key : next_key_seq) {
            int moving_finger_idx = static_cast<int>(next_key.finger);
            PhysKey last_key = last_finger_pos[moving_finger_idx];
            last_finger_pos[moving_finger_idx] = next_key;
            penalty += next_key.distance_to(last_key);
        }
    }

    return penalty;
}
