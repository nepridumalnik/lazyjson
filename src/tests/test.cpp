#include <gtest/gtest.h>

#include <lazyjson/json.hpp>

namespace json = lazyjson;

TEST(Test, MapTesting)
{
    json::Json json;
    json::element& it = json["test"];
    it = true;

    bool res = std::get<bool>(it);
    ASSERT_THROW(int resInt = std::get<int>(it), std::bad_variant_access);
}
