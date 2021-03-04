#include <catch2/catch.hpp>
#include <layout.hpp>
#include <model.hpp>

TEST_CASE("model score text", "[model]") {
    auto qwerty = Layout::get_qwerty();
    auto m = Model();
    
    auto score_a = m.score_text(qwerty, "hi people.");
    auto score_b = m.score_text(qwerty, "hi people.");
    REQUIRE(score_a == score_b);

    score_a = m.score_text(qwerty, "hi people.");
    score_b = m.score_text(qwerty, "hi pvevev.");
    REQUIRE(score_a < score_b);

    score_a = m.score_text(qwerty, "Hello World");
    score_b = m.score_text(qwerty, "Hello World!");
    REQUIRE(score_a < score_b);
}
