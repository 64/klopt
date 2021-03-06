#include <algorithm>
#include <numeric>
#include <model.hpp>

float Model::stretched_hand_penalty(
        const std::array<PhysKey, Finger::NUM_FINGERS>& finger_pos,
        PhysKey next) const {

    auto dist = [finger_pos, next](Finger a, Finger b) {
        const PhysKey* lhs = &finger_pos[static_cast<int>(a)];
        if (a == next.finger) 
            lhs = &next;
        const PhysKey* rhs = &finger_pos[static_cast<int>(a)];
        if (b == next.finger) 
            rhs = &next;
        return lhs->distance_to(*rhs);
    };

    auto finger_distances = {
        dist(Finger::LEFT_PINKIE, Finger::LEFT_RING),
        dist(Finger::LEFT_RING, Finger::LEFT_MIDDLE),
        dist(Finger::LEFT_MIDDLE, Finger::LEFT_INDEX),
        dist(Finger::RIGHT_PINKIE, Finger::RIGHT_RING),
        dist(Finger::RIGHT_RING, Finger::RIGHT_MIDDLE),
        dist(Finger::RIGHT_MIDDLE, Finger::RIGHT_INDEX),
    };

    auto penalty = 0.0f;

    auto sum = std::accumulate(finger_distances.begin(), finger_distances.end(), 0.0f);
    auto mean = sum / finger_distances.size();
    auto max_dist = *std::max_element(finger_distances.begin(), finger_distances.end());

    penalty += std::max(mean - 1.4f, 0.0f);
    penalty += std::max(max_dist - 2.5f, 0.0f);

    return penalty;
}

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

            // Penalize sideways movement and hand stretching
            penalty += finger_penalty * next_key.weighted_distance_to(last_key, 1.5f, 0.5f);
            penalty += stretched_hand_penalty(last_finger_pos, next_key);

            if (last_finger_used && next_key.finger.same_hand(last_key.finger)) {
                penalty += repeated_hand_penalty;

                if (next_key.finger == last_finger_used) {
                    penalty += finger_penalty * repeated_finger_penalty; 
                }
            }

            last_finger_pos[moving_finger_idx] = next_key;
            last_finger_used = next_key.finger;
        }
    }

    return -penalty;
}
