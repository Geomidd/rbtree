#include <iostream>
#include <catch2/catch.hpp>
#include <rbtree.hpp>

TEST_CASE("Library is imported", "[library]")
{
  rbt::Node first{};
  first.value = 5;
  REQUIRE(first.value == 5);

  rbt::Node second{ 3, &first, nullptr, nullptr };
  REQUIRE(second.value == 3);
  REQUIRE(second.parent == &first);
  first.left = &second;
  REQUIRE(first.left == &second);
  REQUIRE(first.left->value == 3);

  rbt::RBTree tree;
  REQUIRE(tree.GetRoot() == nullptr);
  tree.Insert(3);
  tree.Insert(2);
  auto i3 = tree.Insert(4);
  REQUIRE(i3->color == rbt::RED);
  tree.Insert(10);
  tree.Insert(7);
  tree.Insert(1);
  tree.Insert(5);
  tree.Insert(20);
  tree.Insert(2);
  tree.Insert(3);
  tree.Insert(6);
  REQUIRE(tree.GetRoot()->value == 4);
  tree.Dump(tree.GetRoot(), 0);
}