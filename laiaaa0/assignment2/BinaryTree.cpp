#include "BinaryTree.h"

//BinaryTree::BinaryTreeInorder(){}
//BinaryTree::BinaryTreePostorder();
template <class T>
BinaryTree<T>::BinaryTree(){
  this->left_subtree_ = NULL;
  this->right_subtree_ = NULL;
  this->parent_ = NULL;
}
template <class T>
BinaryTree<T>::BinaryTree(const T & value){
  this->root_value_ = value;
  this->left_subtree_ = NULL;
  this->right_subtree_ = NULL;
  this->parent_ = NULL;
}
template <class T>
BinaryTree<T>::BinaryTree(const T & value, BinaryTree<T> * left, BinaryTree<T> * right){
  this->root_value_ = value;
  this->left_subtree_ = left;
  this->right_subtree_ = right;
  this->left_subtree_->parent_ = this;
  this->right_subtree_->parent_ = this;
}/*
template <class T>
BinaryTree<T>::BinaryTree(std::queue<T> &values, InputMethod method){

  switch (method) {
    case PREORDER:
    {
      if (!values.empty()){

        this->root_value_ = values.front();
        values.pop();
        BinaryTree<T> *left_tree = new BinaryTree<T>(values,method);
        this->left_subtree_ = left_tree;
        BinaryTree<T> * right_tree = new BinaryTree<T>(values,method);
        this->right_subtree_ = right_tree;
      }
      break;
    }

    case INORDER:
      break;
    default:
      break;
  }

}*/
template <class T>
const T & BinaryTree<T>::GetRootValue(){
  return this->root_value_;
}

template <class T>
BinaryTree<T> * BinaryTree<T>::GetRightSubtree(){
  return this->right_subtree_;
}

template <class T>
BinaryTree<T> * BinaryTree<T>::GetLeftSubtree(){
  return this->left_subtree_;
}


template <class T>
bool BinaryTree<T>::IsValueInTree (const T & value, BinaryTree<T>* &root_of_value){
  if (this->root_value_==value){
    root_of_value = this;
    return true;
  }
  else {
    if (this->left_subtree_!=NULL){
        if (this->left_subtree_->IsValueInTree(value, root_of_value)) return true;
        else {
          if (this->right_subtree_!=NULL){
            if (this->right_subtree_->IsValueInTree(value, root_of_value)) return true;
          }
        }
    }
  }
  return false;
}


template <class T>
void BinaryTree<T>::PrintInorder(){

  if (this->left_subtree_!=NULL){
    this->left_subtree_->PrintInorder();
  }
  std::cout<<this->root_value_<<" ";
  if (this->right_subtree_!=NULL){
    this->right_subtree_->PrintInorder();
  }
}


template <class T>
int BinaryTree<T>::Depth(){
  if (this==NULL) return 0;
  else {
    int left_depth = this->left_subtree_->Depth();
    int right_depth = this->right_subtree_->Depth();
    if (left_depth<right_depth)
      return right_depth+1;
    else
      return left_depth+1;
  }
}


template<class T>
const T BinaryTree<T>::LowestCommonAncestor (const T & key1, const T & key2){
  T lowest_common_ancestor;

  BinaryTree<T> *tree_of_key_1;
  BinaryTree<T> *tree_of_key_2;

  bool key1_in_tree = this->IsValueInTree(key1,tree_of_key_1);
  bool key2_in_tree = this->IsValueInTree(key2,tree_of_key_2);

  if (!key1_in_tree or !key2_in_tree){
    throw std::invalid_argument("key not in tree!");
  }
  else {
    std::vector<T> path_from_key1_to_root;

    BinaryTree<T> * trees_in_path_key1 = tree_of_key_1;

    path_from_key1_to_root.push_back(trees_in_path_key1->GetRootValue());

    while (trees_in_path_key1->parent_!=NULL){
      trees_in_path_key1 = trees_in_path_key1->parent_;
      path_from_key1_to_root.push_back(trees_in_path_key1->GetRootValue());
    }



    BinaryTree<T> * trees_in_path_key2 = tree_of_key_2;

    int current_root_value = trees_in_path_key2->GetRootValue();
    bool ancestorFound = false;
    while (!ancestorFound){
      for (int i=0; i<path_from_key1_to_root.size(); ++i){
        if (current_root_value==path_from_key1_to_root[i]){
          ancestorFound = true;
          lowest_common_ancestor = path_from_key1_to_root[i];

        }
      }
      if (trees_in_path_key2->parent_!=NULL){
        trees_in_path_key2 = trees_in_path_key2->parent_;
      }
      else{
        throw std::invalid_argument("Lowest Common Ancestor not found!");
      }
    }
    return lowest_common_ancestor;

  }

}
