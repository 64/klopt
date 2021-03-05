#include <unordered_map>
#include <string>
#include <phys_key.hpp>
#include <phys_layout.hpp>

PhysLayout PhysLayout::get_iso_gb() {
    std::unordered_map<std::string, PhysKey> map;

    map.insert({ "backtick",  PhysKey(0.5f,  0.5f, Finger::LEFT_PINKIE) });
    map.insert({ "one",       PhysKey(1.5f,  0.5f, Finger::LEFT_PINKIE) });
    map.insert({ "two",       PhysKey(2.5f,  0.5f, Finger::LEFT_RING) });
    map.insert({ "three",     PhysKey(3.5f,  0.5f, Finger::LEFT_MIDDLE) });
    map.insert({ "four",      PhysKey(4.5f,  0.5f, Finger::LEFT_INDEX) });
    map.insert({ "five",      PhysKey(5.5f,  0.5f, Finger::LEFT_INDEX) });
    map.insert({ "six",       PhysKey(6.5f,  0.5f, Finger::RIGHT_INDEX) });
    map.insert({ "seven",     PhysKey(7.5f,  0.5f, Finger::RIGHT_INDEX) });
    map.insert({ "eight",     PhysKey(8.5f,  0.5f, Finger::RIGHT_MIDDLE) });
    map.insert({ "nine",      PhysKey(9.5f,  0.5f, Finger::RIGHT_RING) });
    map.insert({ "zero",      PhysKey(10.5f, 0.5f, Finger::RIGHT_PINKIE) });
    map.insert({ "minus",     PhysKey(11.5f, 0.5f, Finger::RIGHT_PINKIE) });
    map.insert({ "equals",    PhysKey(12.5f, 0.5f, Finger::RIGHT_PINKIE) });
    map.insert({ "backspace", PhysKey(13.5f, 0.5f, Finger::RIGHT_PINKIE) });

    map.insert({ "tab",   PhysKey(0.7f,  1.5f, Finger::LEFT_PINKIE) });
    map.insert({ "q",     PhysKey(2.0f,  1.5f, Finger::LEFT_PINKIE) });
    map.insert({ "w",     PhysKey(3.0f,  1.5f, Finger::LEFT_RING) });
    map.insert({ "e",     PhysKey(4.0f,  1.5f, Finger::LEFT_MIDDLE) });
    map.insert({ "r",     PhysKey(5.0f,  1.5f, Finger::LEFT_INDEX) });
    map.insert({ "t",     PhysKey(6.0f,  1.5f, Finger::LEFT_INDEX) });
    map.insert({ "y",     PhysKey(7.0f,  1.5f, Finger::RIGHT_INDEX) });
    map.insert({ "u",     PhysKey(8.0f,  1.5f, Finger::RIGHT_INDEX) });
    map.insert({ "i",     PhysKey(9.0f,  1.5f, Finger::RIGHT_MIDDLE) });
    map.insert({ "o",     PhysKey(10.0f, 1.5f, Finger::RIGHT_RING) });
    map.insert({ "p",     PhysKey(11.0f, 1.5f, Finger::RIGHT_PINKIE) });
    map.insert({ "[",     PhysKey(12.0f, 1.5f, Finger::RIGHT_PINKIE) });
    map.insert({ "]",     PhysKey(13.0f, 1.5f, Finger::RIGHT_PINKIE) });

    map.insert({ "a",     PhysKey(2.2f,  2.5f, Finger::LEFT_PINKIE) });
    map.insert({ "s",     PhysKey(3.2f,  2.5f, Finger::LEFT_RING) });
    map.insert({ "d",     PhysKey(4.2f,  2.5f, Finger::LEFT_MIDDLE) });
    map.insert({ "f",     PhysKey(5.2f,  2.5f, Finger::LEFT_INDEX) });
    map.insert({ "g",     PhysKey(6.2f,  2.5f, Finger::LEFT_INDEX) });
    map.insert({ "h",     PhysKey(7.2f,  2.5f, Finger::RIGHT_INDEX) });
    map.insert({ "j",     PhysKey(8.2f,  2.5f, Finger::RIGHT_INDEX) });
    map.insert({ "k",     PhysKey(9.2f,  2.5f, Finger::RIGHT_MIDDLE) });
    map.insert({ "l",     PhysKey(10.2f, 2.5f, Finger::RIGHT_RING) });
    map.insert({ ";",     PhysKey(11.2f, 2.5f, Finger::RIGHT_PINKIE) });
    map.insert({ "'",     PhysKey(12.2f, 2.5f, Finger::RIGHT_PINKIE) });
    map.insert({ "#",     PhysKey(13.2f, 2.5f, Finger::RIGHT_PINKIE) });
    map.insert({ "enter", PhysKey(14.0f, 2.0f, Finger::RIGHT_PINKIE) });

    map.insert({ "lshift",    PhysKey(0.5f,  3.5f, Finger::LEFT_PINKIE) });
    map.insert({ "backslash", PhysKey(1.7f,  3.5f, Finger::LEFT_PINKIE) });
    map.insert({ "z",         PhysKey(2.7f,  3.5f, Finger::LEFT_PINKIE) });
    map.insert({ "x",         PhysKey(3.7f,  3.5f, Finger::LEFT_RING) });
    map.insert({ "c",         PhysKey(4.7f,  3.5f, Finger::LEFT_MIDDLE) });
    map.insert({ "v",         PhysKey(5.7f,  3.5f, Finger::LEFT_INDEX) });
    map.insert({ "b",         PhysKey(6.7f,  3.5f, Finger::LEFT_INDEX) });
    map.insert({ "n",         PhysKey(7.7f,  3.5f, Finger::RIGHT_INDEX) });
    map.insert({ "m",         PhysKey(8.7f,  3.5f, Finger::RIGHT_INDEX) });
    map.insert({ ",",         PhysKey(9.7f,  3.5f, Finger::RIGHT_MIDDLE) });
    map.insert({ ".",         PhysKey(10.7f,  3.5f, Finger::RIGHT_RING) });
    map.insert({ "/",         PhysKey(11.7f,  3.5f, Finger::RIGHT_PINKIE) });
    map.insert({ "rshift",    PhysKey(13.2f,  3.5f, Finger::RIGHT_PINKIE) });

    map.insert({ "lctrl", PhysKey(0.6f,  4.5f, Finger::LEFT_PINKIE) });
    map.insert({ "lalt",  PhysKey(3.6f,  4.5f, Finger::LEFT_THUMB) });
    map.insert({ "space", PhysKey(6.5f,  4.5f, Finger::RIGHT_THUMB) });
    map.insert({ "altgr", PhysKey(9.7f,  4.5f, Finger::RIGHT_THUMB) });
    map.insert({ "rctrl", PhysKey(11.7f,  4.5f, Finger::RIGHT_PINKIE) });

    return PhysLayout(map);
}
