#include "BinaryTree.cpp"
using namespace std;

template<class T>
bool BinaryTree<T>::AncestorsOfKey (const T & key, std::vector<T> &ancestors){
  BinaryTree<T> *tree_of_key;
  if (this->IsValueInTree(key, tree_of_key)){
    if (tree_of_key->parent_!=NULL){

      BinaryTree<T> *current_tree = tree_of_key->parent_;
      ancestors.push_back(current_tree->root_value_);
      while (current_tree->parent_!=NULL){
        current_tree = current_tree->parent_;
        ancestors.push_back(current_tree->root_value_);
      }
    }
    return true;
  }
  else {
    return false;
  }
}



int main (){
BinaryTree<int> * leaf1  = new BinaryTree<int>(8);
BinaryTree<int> * leaf2  = new BinaryTree<int>(9);

BinaryTree<int> * leaf3  = new BinaryTree<int>(4);
BinaryTree<int> * leaf4  = new BinaryTree<int>(5);



/*
        3
    1      2
  8   9   4 5
*/
BinaryTree<int>* bt = new BinaryTree<int>(1,leaf1,leaf2);
BinaryTree<int>* bt2 = new BinaryTree<int>(2,leaf3,leaf4);
BinaryTree<int>* bt3 = new BinaryTree<int>(3,bt,bt2);



//InputMethod im = PREORDER;

bt->PrintInorder();
cout<<endl<<endl;
bt3->PrintInorder();
cout<<endl<<endl;


vector<int> v;
BinaryTree<int> *aux;

bt3->AncestorsOfKey(9,v);

for (int i=0;i<v.size();++i) cout<<v[i]<< " ";
cout<<endl;
//BinaryTree<int> bt(values,im) = new BinaryTree<int>;

cout<<bt3->LowestCommonAncestor(4,2)<<endl;


}
