#include <optional>
#include <cctype>
#include <random>
#include <queue>
#include <iostream>
#include <phys_layout.hpp>
#include <layout.hpp>

Layout::Layout(PhysLayout phys_map,
        std::initializer_list<std::pair<char, KeyCombo>> char_key_map,
        std::initializer_list<PhysKey> home_row_keys) : home_row() {
    for (auto char_key : char_key_map) {
        key_map[char_key.first] = char_key.second;

        // Add the uppercase variant as well, with the appropriate shift key held
        if (std::islower(char_key.first)) {
            auto finger = char_key.second.main.finger;
            auto shift_string = finger.get_opposite_pinkie() == Finger::LEFT_PINKIE ? "lshift" : "rshift";
            key_map[std::toupper(char_key.first)] = KeyCombo(char_key.second.main, phys_map[shift_string]);
        }
    }

    for (auto key : home_row_keys) {
        home_row[key.finger] = key; 
    }
}

char random_char(std::mt19937& rng) {
    // TODO: Remove magic numbers
    std::uniform_int_distribution<> distrib(0, 25);
    return u8"abcdefghijklmnopqrstuvwxyz"[distrib(rng)];
}

Layout Layout::mutate(std::mt19937& rng) const {
    Layout copy = *this;

    char a = random_char(rng); 
    char b = random_char(rng); 

    std::swap<KeyCombo>(copy.key_map[a], copy.key_map[b]);

    // Correct the capitalized versions
    if (std::islower(a)) {
        copy.key_map[std::toupper(a)].value().set_main(copy.key_map[a].value().main);
    }

    if (std::islower(b)) {
        copy.key_map[std::toupper(b)].value().set_main(copy.key_map[b].value().main);
    }

    return copy;
}

// TODO: Move this to PhysLayout
void Layout::print() const {
    auto cmp = [](std::pair<char, PhysKey> a, std::pair<char, PhysKey> b) {
        if (a.second.abs_y == b.second.abs_y)
            return a.second.abs_x > b.second.abs_x;
        else
            return a.second.abs_y > b.second.abs_y;
    };
    std::priority_queue<std::pair<char, PhysKey>, std::vector<std::pair<char, PhysKey>>, decltype(cmp)> queue(cmp);

    std::string printable = "1234567890-=qwertyuiop[]asdfghjkl;'#zxcvbnm,./";
    for (auto c : printable)
        queue.push({ c, key_map[c].value().main });

    float current_y = queue.top().second.abs_y;
    while(!queue.empty()) {
        auto key = queue.top();
        if (current_y < key.second.abs_y) {
            std::putchar('\n');
            current_y = key.second.abs_y;
        }

        std::putchar(key.first);
        queue.pop();
    }
    std::putchar('\n');
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
    }, 
    // Home row 
    // TODO: This should really be moved to PhysLayout
    {
        phys_map["a"],
        phys_map["s"],
        phys_map["d"],
        phys_map["f"],
        phys_map["lalt"],
        phys_map["space"],
        phys_map["j"],
        phys_map["k"],
        phys_map["l"],
        phys_map[";"],
    });
}

// For testing purposes, this is terrible and hacky and will be removed
Layout Layout::from_string(std::string_view format) {
    PhysLayout phys_map = PhysLayout::get_iso_gb();
    Layout l = get_qwerty();
    std::string qwerty = "qwertyuiopasdfghjklzxcvbnm";
    
    for (std::size_t i = 0; i < qwerty.size(); i++) {
        char target = format[i];
        char qwerty_char = qwerty[i];
        Finger f = l.key_map[target].value().main.finger;
        l.key_map[target] = KeyCombo(phys_map[qwerty_char]);
        auto shift_string = f.get_opposite_pinkie() == Finger::LEFT_PINKIE ? "lshift" : "rshift";
        l.key_map[std::toupper(target)] = KeyCombo(phys_map[qwerty_char], phys_map[shift_string]);
    }

    return l;
}

