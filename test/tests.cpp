#include <catch2/catch.hpp>
#include <rbtree.hpp>

unsigned int Factorial(unsigned int number)
{
  return number <= 1 ? number : Factorial(number - 1) * number;
}

TEST_CASE("Factorials are computed", "[factorial]")
{
  REQUIRE(Factorial(1) == 1);
  REQUIRE(Factorial(2) == 2);
  REQUIRE(Factorial(3) == 6);
  REQUIRE(Factorial(10) == 3628800);
}

TEST_CASE("Library is imported", "[library]")
{
  REQUIRE(rbt::add(1, 1) == 2);
  REQUIRE(rbt::add(2, 2) == 4);
  REQUIRE(rbt::add(1, 2) == 3);
}