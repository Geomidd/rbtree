This is a C++ library for red/black trees

Red/black trees are a self-balancing form of binary search trees such that search times are
guaranteed to be <img src="https://render.githubusercontent.com/render/math?math=O({\log}n)">
at the cost of an extra bit per node and increased insertion/deletion times.

Properties of a red/black tree:
1. Each node is either red _or_ black
2. The root is **black**
3. All leaves (null) are **black**
4. Both of a red node's children must be **black**
5. For any node, every path to its descendant leaves should contain the same number of black nodes.