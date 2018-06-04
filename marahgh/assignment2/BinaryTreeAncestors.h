#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
/*The Binary Tree class,it has no duplicate values */
template <typename S>
class BinaryTree {
  /*Node's Tree class*/
  template <typename T>
  class Node {
   private:
    T data;
    Node<T>* left;
    Node<T>* right;
    friend class BinaryTree;

   public:
    /*Node's constructor */
    Node(T data) : data(data), left(nullptr), right(nullptr) {}

    /*Inserts a node as the right son of this node*/
    bool insertRight(Node<T>* node) {
      if (right) {
        return false;
      }
      right = node;
      return true;
    }

    /*Inserts a node as the right son of this node*/
    bool insertLeft(Node<T>* node) {
      if (left) {
        return false;
      }
      left = node;
      return true;
    }
  };

  /****************************************************************************/
  /*Binary Tree fields: the root node of the tree*/
  Node<S>* root;

  /****************************************************************************/

  /*Deleting a binary Tree recursive auxiliary function*/
  void recursiveDelete(Node<S>* root) {
    if (!root) {
      return;
    }
    recursiveDelete(root->left);
    recursiveDelete(root->right);
    delete root;
  }

  /*an auxiliary insert recursive function of the insert method.
  returns true if insertion succeeded, flase otherwise.
  leftOrRight is string which can be either right or left */
  bool insertElement(Node<S>* treeRoot, Node<S>* node, S parent,
                     string leftOrRight) {
    if (!treeRoot) {
      return false;
    }
    if (treeRoot->data == parent) {
      if (leftOrRight == "right") {
        return treeRoot->insertRight(node);
      }
      return treeRoot->insertLeft(node);
    }
    return (insertElement(treeRoot->left, node, parent, leftOrRight) ||
            insertElement(treeRoot->right, node, parent, leftOrRight));
  }
  /*return true if the given key exists in the given root tree,
  false otherwise*/
  bool find(Node<S>* root, S key) {
    if (!root) {
      return false;
    }
    if (root->data == key) {
      return true;
    }
    return (find(root->left, key)) || (find(root->right, key));
  }

  /*Auxiliary recursive function of findAncestorsInTree in BinaryTree class*/
  void findAncestors(Node<S>* root, S& key) {
    if (!root) {
      return;
    }
    if (root->data == key) {
      return;
    }
    if (find(root, key)) {
      findAncestors(root->left, key);
      findAncestors(root->right, key);
      cout << root->data << endl;
    }
  }
  /*Auxiliary  recursive method,
  finds the lowest common ancestor of the given two keys*/
  Node<S>* LCA(Node<S>* treeRoot, S& key1, S& key2) {
    if (!treeRoot) {
      return nullptr;
    }
    if ((treeRoot->data == key1) || (treeRoot->data == key2)) {
      return treeRoot;
    }
    Node<S>* leftResult = LCA(treeRoot->left, key1, key2);
    Node<S>* rightResult = LCA(treeRoot->right, key1, key2);
    if ((!leftResult) && (!rightResult)) {
      return nullptr;
    }
    if ((leftResult) && (rightResult)) {
      return treeRoot;
    }
    if (!leftResult) {
      return rightResult;
    } else {
      return leftResult;
    }
    return treeRoot;
  }

  /**************************************************************************/
  /*The public method of Binary Tree class*/

 public:
  /*Binary Tree constructor,
  creates a binary tree which cosists of the root node*/
  BinaryTree(S rootData) : root(new Node<S>(rootData)) {}

  /*the tree constructor expects to recieve a function object
  which will be used to compare tree elements*/
  ~BinaryTree() { recursiveDelete(root); }

  /*inserts the given key as the leftOrRight son of parent,
  returns true if insertion succeeded, flase otherwise.*/
  bool insert(S key, S parent, string leftOrRight) {
    if (!root) {
      return false;
    }
    if (!find(root, parent) || find(root, key)) {
      return false;
    }
    if (leftOrRight != "left" && leftOrRight != "right") {
      return false;
    }
    Node<S>* nodeToInsert = new Node<S>(key);
    if (!insertElement(root, nodeToInsert, parent, leftOrRight)) {
      delete nodeToInsert;
      return false;
    }
    return true;
  }

  /*Prints all the ancestors of the key in the given binary tree.
    The function recieves the root of the binart tree*/
  void printAncestors(S key) {
    if (!root) {
      return;
    }
    findAncestors(root, key);
  }

  /*prints the lowest common ancestor of the given two keys.*/
  void printLowestCommonAncestor(S key1, S key2) {
    if (!root) {
      return;
    }
    if (!find(root, key1) || !find(root, key2)) {
      return;
    }
    Node<S>* lca = LCA(root, key1, key2);
    if (lca) {
      cout << lca->data << endl;
    }
  }
};
