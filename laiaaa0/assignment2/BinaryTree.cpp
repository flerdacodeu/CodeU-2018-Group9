#include "BinaryTree.h"


template <class T>
BinaryTree<T>::BinaryTree(){
  this->left_subtree_ = nullptr;
  this->right_subtree_ = nullptr;
  this->parent_ = nullptr;
}
template <class T>
BinaryTree<T>::BinaryTree(const T & value){
  this->root_value_ = value;
  this->left_subtree_ = nullptr;
  this->right_subtree_ = nullptr;
  this->parent_ = nullptr;
}
template <class T>
BinaryTree<T>::BinaryTree(const T & value, BinaryTree<T> * left, BinaryTree<T> * right){
  this->root_value_ = value;
  this->left_subtree_ = left;
  this->right_subtree_ = right;
  this->left_subtree_->parent_ = this;
  this->right_subtree_->parent_ = this;
}

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
bool BinaryTree<T>::FindValueInTree (const T & value, BinaryTree<T>*& root_of_value){
  if (this==nullptr) return false;
  if (this->root_value_==value){
    root_of_value = this;
    return true;
  }
  else {
    if (this->left_subtree_!=nullptr){
        if (this->left_subtree_->FindValueInTree(value, root_of_value)) return true;
        else {
          if (this->right_subtree_!=nullptr){
            if (this->right_subtree_->FindValueInTree(value, root_of_value)) return true;
          }
        }
    }
  }
  return false;
}


template <class T>
void BinaryTree<T>::PrintInorder(){

  if (this->left_subtree_!=nullptr){
    this->left_subtree_->PrintInorder();
  }
  std::cout<<this->root_value_<<" ";
  if (this->right_subtree_!=nullptr){
    this->right_subtree_->PrintInorder();
  }
}


template <class T>
int BinaryTree<T>::Depth(){
  if (this==nullptr) return 0;
  else {
      int left_depth, right_depth;
      if (this->left_subtree_!=nullptr){
          left_depth = this->left_subtree_->Depth();
      }
      else left_depth = 0;
      if (this->right_subtree_!=nullptr){
        right_depth = this->right_subtree_->Depth();
      }
      else right_depth = 0;
    if (left_depth<right_depth)
      return right_depth+1;
    else
      return left_depth+1;
  }
}


template<class T>
bool BinaryTree<T>::LowestCommonAncestor (const T & key1, const T & key2,  T & lca){

  if (this == nullptr){
    return false;
  }
  else {
    BinaryTree<T> *tree_of_key;

    bool foundInLeft1 = this->left_subtree_->FindValueInTree(key1,tree_of_key);
    bool foundInRight1 = this->right_subtree_->FindValueInTree(key1,tree_of_key);
    bool foundInLeft2 = this->left_subtree_->FindValueInTree(key2,tree_of_key);
    bool foundInRight2 = this->right_subtree_->FindValueInTree(key2,tree_of_key);

    if ((foundInLeft1 && foundInRight2) || (foundInLeft2 && foundInRight1)){

      lca = this->root_value_;
      return true;
    }
    else if (this->root_value_==key1){
      if (foundInLeft2 || foundInRight2) {
        lca = this->root_value_;
        return true;
      }
    }
    else if (this->root_value_==key2){
      if (foundInLeft1 || foundInRight1){
        lca = this->root_value_;
        return true;
      }
    }
    else {
      bool left_subtree_result = this->left_subtree_->LowestCommonAncestor(key1,key2,lca);
      if (left_subtree_result==true){
          return left_subtree_result;
      } else {
        bool right_subtree_result = this->right_subtree_->LowestCommonAncestor(key1,key2,lca);
        if (right_subtree_result== true){
          return right_subtree_result;
        }
        else {
          return false;
        }
      }

    }
  }

}
