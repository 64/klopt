#include <catch2/catch.hpp>
#include <key_combo.hpp>
#include <finger.hpp>

TEST_CASE("key distances", "[key]") {
    auto key_a = PhysKey(0.0f, 0.0f, Finger::LEFT_INDEX);
    auto key_b = PhysKey(0.0f, 1.0f, Finger::LEFT_INDEX);
    REQUIRE(key_a.distance_to(key_b) == Approx(1.0));
}

TEST_CASE("key press", "[key]") {
    auto key_a = PhysKey(0.0f, 0.0f, Finger::LEFT_INDEX);
    auto key_b = PhysKey(0.0f, 1.0f, Finger::LEFT_INDEX);
    auto key_c = PhysKey(0.0f, 2.0f, Finger::LEFT_INDEX);

    auto key_press_a = KeyCombo(key_a);
    auto key_press_b = KeyCombo(key_a, key_b);
    auto key_press_c = KeyCombo(key_a, key_b, key_c);

    int iter_index = 0;
    for (PhysKey k : key_press_a) {
        if (iter_index == 0) REQUIRE(k == key_a);
        if (iter_index == 1) REQUIRE(k == key_b);
        if (iter_index == 2) REQUIRE(k == key_c);
        iter_index++;
    }
    REQUIRE(iter_index == 1);

    iter_index = 0;
    for (PhysKey k : key_press_b) {
        if (iter_index == 0) REQUIRE(k == key_a);
        if (iter_index == 1) REQUIRE(k == key_b);
        if (iter_index == 2) REQUIRE(k == key_c);
        iter_index++;
    }
    REQUIRE(iter_index == 2);

    iter_index = 0;
    for (PhysKey k : key_press_c) {
        if (iter_index == 0) REQUIRE(k == key_a);
        if (iter_index == 1) REQUIRE(k == key_b);
        if (iter_index == 2) REQUIRE(k == key_c);
        iter_index++;
    }
    REQUIRE(iter_index == 3);
}
