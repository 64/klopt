#include <catch2/catch.hpp>
#include <iostream>
#include <fstream>
#include <layout.hpp>
#include <model.hpp>

std::string slurp(std::istream& in) {
    std::string out, tmp;

    while(std::getline(in, tmp)) {
        out += tmp;
        out += '\n';
    }

    return out;
}

TEST_CASE("model score text", "[model]") {
    auto qwerty = Layout::get_qwerty();
    auto m = Model();
    
    auto score_a = m.score_text(qwerty, "hi people.");
    auto score_b = m.score_text(qwerty, "hi people.");
    REQUIRE(score_a == score_b);

    score_a = m.score_text(qwerty, "hi pvevev.");
    score_b = m.score_text(qwerty, "hi people.");
    REQUIRE(score_a > score_b);

    score_a = m.score_text(qwerty, "Hello World");
    score_b = m.score_text(qwerty, "Hello World!");
    REQUIRE(score_a > score_b);

    score_a = m.score_text(qwerty, "asdf");
    score_b = m.score_text(qwerty, "aadf");
    REQUIRE(score_a > score_b);

    std::ifstream file("tests/words.txt");
    auto test_text = slurp(file);

    auto layout_a = Layout::from_string("zkydlxgwvuetirjabonqfphmcs");
    auto layout_b = Layout::from_string("zkydlagwvuetirjxbonqfphmcs");
    score_a = m.score_text(layout_a, "etaoinshrdlu");
    score_b = m.score_text(layout_b, "etaoinshrdlu");
    REQUIRE(score_a > score_b);

    score_a = m.score_text(layout_a, test_text);
    score_b = m.score_text(layout_b, test_text);
    REQUIRE(score_a > score_b);
}
