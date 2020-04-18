#include <iostream>
#include <string>
#include <catch2/catch.hpp>
#include <rbtree.hpp>

TEST_CASE("Library is imported", "[library]")
{
  rbt::Node<int> first{};
  first.key = 5;
  REQUIRE(first.key == 5);

  rbt::Node<int> second{ 3, rbt::BLACK, nullptr, nullptr, &first };
  REQUIRE(second.key == 3);
  REQUIRE(second.parent == &first);
  first.left = &second;
  REQUIRE(first.left == &second);
  REQUIRE(first.left->key == 3);

  rbt::RBTree<int> tree;
  tree.Insert(3);
  tree.Insert(2);
  tree.Insert(4);
  tree.Insert(10);
  tree.Insert(7);
  tree.Insert(1);
  tree.Insert(5);
  tree.Insert(20);
  tree.Insert(2);
  tree.Insert(3);
  tree.Insert(6);
  REQUIRE(tree.GetRoot()->key == 4);
  tree.Dump();
  tree.Remove(20);
  tree.Dump();
  tree.Remove(4);
  tree.Dump();

  rbt::RBTree<std::string> stringTree;
  stringTree.Insert("A");
  stringTree.Insert("Apple");
  stringTree.Insert("Bob");
  stringTree.Dump();
  stringTree.Remove("A");
  stringTree.Dump();
}