#include <model.hpp>

float Model::score_text(const Layout& layout, std::string_view text) const {
    float penalty = 0.0f;

    auto last_finger_pos = layout.home_row;
    std::optional<Finger> last_finger_used = std::nullopt;

    for (auto c : text) {
        KeyCombo next_key_seq = layout.key_map[c].value();

        // Some characters require more than one key press (e.g uppercase characters)
        for (PhysKey next_key : next_key_seq) {
            int moving_finger_idx = static_cast<int>(next_key.finger);
            PhysKey last_key = last_finger_pos[moving_finger_idx];
            float finger_penalty = finger_penalties[moving_finger_idx];

            penalty += finger_penalty * next_key.distance_to(last_key);

            if (last_finger_used && next_key.finger == last_finger_used) {
                penalty += finger_penalty * repeated_finger_penalty; 
            }

            // TODO: Penalize stretched hands instead of this
            if (next_key != layout.home_row[moving_finger_idx]) {
                penalty += finger_penalty * non_home_row_penalty;
            }

            last_finger_pos[moving_finger_idx] = next_key;
            last_finger_used = next_key.finger;
        }
    }

    return -penalty;
}
