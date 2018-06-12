#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*enum used basically* for insert method
 to choose in which son will the element be inserted*/
enum Son { Left, Right };

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

    /*Inserts a node as the right son of this node,
    the method checks if the right son of the node
    is already occuupied by another element and only if it's not
    the method inserts the node and returns true,otherwise returns false*/
    bool insertRight(Node<T>* node) {
      if (right != nullptr) {
        return false;
      }
      right = node;
      return true;
    }

    /*Inserts a node as the right son of this node
    the method checks if the left son of the node
    is already occuupied by another element and only if it's not
    the method inserts the node and returns true,otherwise returns false*/
    bool insertLeft(Node<T>* node) {
      if (left != nullptr) {
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
    if (root == nullptr) {
      return;
    }
    recursiveDelete(root->left);
    recursiveDelete(root->right);
    delete root;
  }

  /*an auxiliary insert recursive function of the insert method.
  returns true if insertion succeeded, flase otherwise.
  leftOrRight is an enum which can be either right or left */
  bool insertElement(Node<S>* treeRoot, Node<S>* node, S parent,
                     Son leftOrRight) {
    if (treeRoot == nullptr) {
      return false;
    }
    if (treeRoot->data == parent) {
      if (leftOrRight == Right) {
        return treeRoot->insertRight(node);
      }
      return treeRoot->insertLeft(node);
    }
    return insertElement(treeRoot->left, node, parent, leftOrRight) ||
           insertElement(treeRoot->right, node, parent, leftOrRight);
  }
  /*return the wanted node if the given key exists in the given root tree,
  false nullptr*/
  Node<S>* find(Node<S>* root, S key) {
    if (!root) {
      return nullptr;
    }
    if (root->data == key) {
      return root;
    }
    Node<S>* leftResult = find(root->left, key);
    Node<S>* rightResult = find(root->right, key);
    if ((leftResult == nullptr) && (rightResult == nullptr)) {
      return nullptr;
    }
    if (leftResult != nullptr) {
      return leftResult;
    }
    return rightResult;
  }

  /*Auxiliary recursive function of findAncestorsInTree in BinaryTree class*/
  void findAncestors(Node<S>* root, const S& key, vector<S>& ancestors) {
    if (root == nullptr) {
      return;
    }
    if (root->data == key) {
      return;
    }
    if (find(root, key) != nullptr) {
      findAncestors(root->left, key, ancestors);
      findAncestors(root->right, key, ancestors);
      ancestors.push_back(root->data);
    }
  }
  /*Auxiliary  recursive method,
  finds the lowest common ancestor of the given two keys*/
  Node<S>* LCA(Node<S>* treeRoot, S& key1, S& key2) {
    if (treeRoot == nullptr) {
      return nullptr;
    }
    if ((treeRoot->data == key1) || (treeRoot->data == key2)) {
      return treeRoot;
    }
    Node<S>* leftResult = LCA(treeRoot->left, key1, key2);
    Node<S>* rightResult = LCA(treeRoot->right, key1, key2);
    if ((leftResult == nullptr) && (rightResult == nullptr)) {
      return nullptr;
    }
    if ((leftResult != nullptr) && (rightResult != nullptr)) {
      return treeRoot;
    }
    if (leftResult != nullptr) {
      return leftResult;
    }
    return rightResult;
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
  returns true if insertion succeeded, false otherwise.*/
  bool insert(const S& key, const S& parent, Son leftOrRight) {
    if (root == nullptr) {
      return false;
    }
    if ((find(root, parent) == nullptr) || (find(root, key) != nullptr)) {
      return false;
    }
    if (leftOrRight != Left && leftOrRight != Right) {
      return false;
    }
    Node<S>* nodeToInsert = new Node<S>(key);
    if (!insertElement(root, nodeToInsert, parent, leftOrRight)) {
      delete nodeToInsert;
      return false;
    }
    return true;
  }

  /*return a vector of all the ancestors of the key in the given binary tree.
    The function recieves the root of the binary tree*/
  vector<S> getAncestors(S key) {
    vector<S> ancestors = vector<S>();
    if (root != nullptr) {
      findAncestors(root, key, ancestors);
    }
    return ancestors;
  }

  /*returns the lowest common ancestor of the given two keys in a vector,
  in any case of error, or if there is no lca of the given keys,
  the vector will be returned empty, otherwise it will contain the lca .*/
  vector<S> lowestCommonAncestor(S key1, S key2) {
    vector<S> lowestCommonAncestor = vector<S>();
    if (root == nullptr) {
      return lowestCommonAncestor;
    }
    if ((find(root, key1) == nullptr) || (find(root, key2) == nullptr)) {
      return lowestCommonAncestor;
    }
    Node<S>* lca = LCA(root, key1, key2);
    if (lca) {
      lowestCommonAncestor.push_back(lca->data);
    }
  }
};
