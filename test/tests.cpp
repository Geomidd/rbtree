#include <catch2/catch.hpp>
#include <rbtree.hpp>

TEST_CASE("Library is imported", "[library]")
{
  rbt::Node test;
  test.value = 5;
  REQUIRE(test.value == 5);
}