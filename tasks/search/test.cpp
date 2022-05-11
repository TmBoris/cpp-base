#include <catch.hpp>

#include "search.h"

namespace {

bool Belongs(std::string_view text, std::string_view result) {
    return (result.data() >= text.data()) && (result.data() < (text.data() + text.size()));
}

}  // namespace

TEST_CASE("Search") {
    std::string_view text = "g ``p: 'a'a\n\nsergsо\n\n\nq g n";

    std::string_view query = "g";
    std::vector<std::string_view> expected = {"q g n", "g ``p: 'a'a"};

    REQUIRE(expected == Search(text, query, 3));

    text = "g ``p: 'a'a\nojnjn\nr g\n\ng r\nq g n\n";

    query = "g";
    expected = {"r g", "g r", "q g n"};

    REQUIRE(expected == Search(text, query, 3));

    text = "g p a\n\nr g\nhbh\ng r\nq g n\n";

    query = "g";
    expected = {"r g", "g r", "g p a"};

    REQUIRE(expected == Search(text, query, 3));

    text = "\n\n\n\n\n\n\n";

    query = "g";
    expected = {};

    REQUIRE(expected == Search(text, query, 1));

    text = "";

    query = "typesetting release";
    expected = {};

    const auto& actual = Search(text, query, 1);

    REQUIRE(expected == actual);
    SECTION("Result can not use extra memory") {
        for (const auto& doc : actual) {
            REQUIRE(Belongs(text, doc));
        }
    }
}
