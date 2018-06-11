#include <vector>
#include <iostream>
#include <stdexcept>

template <class T>
class BinaryTree{
private:
  T root_value_;
  BinaryTree * left_subtree_;
  BinaryTree * right_subtree_;
  BinaryTree * parent_;

public:
  //Constructors
  BinaryTree ();
  BinaryTree(const T & value);
  BinaryTree(const T & value, BinaryTree * left, BinaryTree * right);

  //Getters
  const T & GetRootValue();
  BinaryTree * GetRightSubtree();
  BinaryTree * GetLeftSubtree();


  //Print
  void PrintInorder();


  int Depth();

  /*!
     \brief "Find if a value is in the tree"

     \param "value, the value to find. root_of_value returns the tree which has the value to find"
     \pre At most one node will have the value
     \post root_of_value contains the binary tree whose root is the value
     \return "true if the value is in the tree, false otherwise"
  */
  bool FindValueInTree (const T & value, BinaryTree<T>*&root_of_value);




  /**
  \brief Returns all the ancestors of a key in the tree.
  \param key, the key from which to calculate ancestors
  \param ancestors, vector that stores the ancestors
  \pre At most one node will have the value of key
  \return true if the key is in the tree, false otherwise
  */

  bool AncestorsOfKey (const T & key, std::vector<T> &ancestors);


  /**
  \brief find the value of the common ancestor between two nodes in a tree
  \pre the keys must be present in the binary tree, and there is only one occurance of each key
  \return the value of the common ancestor
  */
  bool LowestCommonAncestor (const T & key1, const T & key2, T & lca);
};
