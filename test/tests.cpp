#include <iostream>
#include <string>
#include <catch2/catch.hpp>
#include <rbtree.hpp>

TEST_CASE("Library is imported", "[library]")
{
  rbt::Node<int, std::string> first{};
  first.key = 5;
  first.value = "Hello";
  REQUIRE(first.key == 5);
  REQUIRE(first.value == "Hello");

  rbt::Node<int, std::string> second{ 3, "World", rbt::BLACK, nullptr, nullptr, &first };
  REQUIRE(second.key == 3);
  REQUIRE(second.value == "World");
  REQUIRE(second.parent == &first);
  first.left = &second;
  REQUIRE(first.left == &second);
  REQUIRE(first.left->key == 3);

  rbt::RBTree<int, char> tree;
  tree.Insert(3, 'C');
  tree.Insert(2, 'B');
  tree.Insert(4, 'D');
  tree.Insert(10, 'J');
  tree.Insert(7);
  REQUIRE(tree.GetValueFromKey(7) == char());
  tree.Insert(1, 'A');
  tree.Insert(5, 'E');
  tree.Insert(20, 'T');
  tree.Insert(2, 'b');
  tree.Insert(3, 'c');
  tree.Insert(6, 'F');
  REQUIRE(tree.GetRoot()->key == 4);
  REQUIRE(tree.GetRoot()->value == 'D');
  REQUIRE(tree.UpdateValue(6, 'Z') == true);
  REQUIRE(tree.GetValueFromKey(6) == 'Z');
  REQUIRE(tree.UpdateValue(26, '1') == false);
  tree.Dump();
  tree.Remove(20);
  tree.Dump();
  tree.Remove(4);
  tree.Dump();

  rbt::RBTree<std::string, int> stringTree;
  stringTree.Insert("A", 1);
  stringTree.Insert("Apple", 2);
  stringTree.Insert("Bob", 3);
  stringTree.Dump();
  int valueFromKey1 = stringTree.GetValueFromKey("A");
  REQUIRE(valueFromKey1 == 1);
  auto removed1 = stringTree.Remove("A");
  REQUIRE(removed1 == 1);
  stringTree.Dump();
  REQUIRE(stringTree.GetValueFromKey("Apple") == 2);
}