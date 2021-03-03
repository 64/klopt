#include <optional>
#include <cctype>
#include <phys_layout.hpp>
#include <layout.hpp>

Layout::Layout(PhysLayout phys_map, std::initializer_list<std::pair<char, KeyPress>> char_key_map) : phys_map(phys_map) {
    for (auto char_key : char_key_map) {
        key_map[char_key.first] = char_key.second;

        // Add the uppercase variant as well, with the appropriate shift key held
        if (std::islower(char_key.first)) {
            auto finger = char_key.second.main.get_finger();
            auto shift_string = finger.get_opposite_pinkie() == Finger::LEFT_PINKIE ? "lshift" : "rshift";
            key_map[std::toupper(char_key.first)] = KeyPress(char_key.second.main, phys_map[shift_string]);
        }
    }
}

float Layout::score_text(std::string_view text) {
    // Fingers start on the home row
    std::array<PhysKey, Finger::NUM_FINGERS> last_finger_pos = {
        PhysKey(1.5f,  2.5f, Finger::LEFT_PINKIE), // A
        PhysKey(2.5f,  2.5f, Finger::LEFT_RING), // S
        PhysKey(3.5f,  2.5f, Finger::LEFT_MIDDLE), // D
        PhysKey(4.5f,  2.5f, Finger::LEFT_INDEX), // F
        PhysKey(5.5f,  6.5f, Finger::LEFT_THUMB), // LThumb: Space
        PhysKey(6.5f,  6.5f, Finger::RIGHT_THUMB), // RThumb: Space
        PhysKey(7.5f,  2.5f, Finger::RIGHT_INDEX), // J
        PhysKey(8.5f,  2.5f, Finger::RIGHT_MIDDLE), // K
        PhysKey(9.5f,  2.5f, Finger::RIGHT_RING), // L
        PhysKey(10.5f, 2.5f, Finger::RIGHT_PINKIE), // ;
    };

    float penalty = 0.0f;

    for (auto c : text) {
        KeyPress next_key_seq = key_map[c].value();

        // Some characters require more than one key press (e.g uppercase characters)
        for (PhysKey next_key : next_key_seq) {
            int moving_finger_idx = static_cast<int>(next_key.get_finger());
            PhysKey last_key = last_finger_pos[moving_finger_idx];
            last_finger_pos[moving_finger_idx] = next_key;
            penalty += next_key.distance_to(last_key);
        }
    }

    return penalty;
}

Layout Layout::get_qwerty() {
    auto phys_map = PhysLayout::get_iso_gb();

    return Layout(phys_map, {
        { '`', phys_map["backtick"] },
        { '1', phys_map["one"] },
        { '2', phys_map["two"] },
        { '3', phys_map["three"] },
        { '4', phys_map["four"] },
        { '5', phys_map["five"] },
        { '6', phys_map["six"] },
        { '7', phys_map["seven"] },
        { '8', phys_map["eight"] },
        { '9', phys_map["nine"] },
        { '0', phys_map["zero"] },
        { '-', phys_map["minus"] },
        { '=', phys_map["equals"] },
        { '\t', phys_map["tab"] },
        { '!', { phys_map["one"], phys_map["rshift"] } },
        { '"', { phys_map["two"], phys_map["rshift"] } },
        //{ '£', { phys_map["three"], phys_map["rshift"] } },
        { '$', { phys_map["four"], phys_map["rshift"] } },
        { '%', { phys_map["five"], phys_map["rshift"] } },
        { '^', { phys_map["six"], phys_map["lshift"] } },
        { '&', { phys_map["seven"], phys_map["lshift"] } },
        { '*', { phys_map["eight"], phys_map["lshift"] } },
        { '(', { phys_map["nine"], phys_map["lshift"] } },
        { ')', { phys_map["zero"], phys_map["lshift"] } },
        { '_', { phys_map["minus"], phys_map["lshift"] } },
        { '+', { phys_map["equals"], phys_map["lshift"] } },

        { 'q', phys_map["q"] },
        { 'w', phys_map["w"] },
        { 'e', phys_map["e"] },
        { 'r', phys_map["r"] },
        { 't', phys_map["t"] },
        { 'y', phys_map["y"] },
        { 'u', phys_map["u"] },
        { 'i', phys_map["i"] },
        { 'o', phys_map["o"] },
        { 'p', phys_map["p"] },
        { '[', phys_map["["] },
        { ']', phys_map["]"] },
        { '{', { phys_map["["], phys_map["lshift"] } },
        { '}', { phys_map["]"], phys_map["lshift"] } },

        { 'a', phys_map["a"] },
        { 's', phys_map["s"] },
        { 'd', phys_map["d"] },
        { 'f', phys_map["f"] },
        { 'g', phys_map["g"] },
        { 'h', phys_map["h"] },
        { 'j', phys_map["j"] },
        { 'k', phys_map["k"] },
        { 'l', phys_map["l"] },
        { ';', phys_map[";"] },
        { '\'', phys_map["'"] },
        { '#', phys_map["#"] },
        { '\n', phys_map["enter"] },
        { ':', { phys_map[";"], phys_map["lshift"] } },
        { '@', { phys_map["'"], phys_map["lshift"] } },
        { '~', { phys_map["#"], phys_map["lshift"] } },

        { '\\', phys_map["backslash"] },
        { 'z', phys_map["z"] },
        { 'x', phys_map["x"] },
        { 'c', phys_map["c"] },
        { 'v', phys_map["v"] },
        { 'b', phys_map["b"] },
        { 'n', phys_map["n"] },
        { 'm', phys_map["m"] },
        { ',', phys_map[","] },
        { '.', phys_map["."] },
        { '/', phys_map["/"] },
        { '<', { phys_map[","], phys_map["lshift"] } },
        { '>', { phys_map["."], phys_map["lshift"] } },
        { '?', { phys_map["/"], phys_map["lshift"] } },

        { ' ', phys_map["space"] }
    });
}
