#include <catch2/catch.hpp>
#include <layout.hpp>

TEST_CASE("layout score text", "[layout]") {
    auto qwerty = Layout::get_qwerty();

    auto score_a = qwerty.score_text("hi people.");
    auto score_b = qwerty.score_text("hi people.");
    REQUIRE(score_a == score_b);

    score_a = qwerty.score_text("hi people.");
    score_b = qwerty.score_text("hi pvevev.");
    REQUIRE(score_a < score_b);

    score_a = qwerty.score_text("Hello World");
    score_b = qwerty.score_text("Hello World!");
    REQUIRE(score_a < score_b);
}
