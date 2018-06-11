#include "BinaryTree.cpp"
using namespace std;

template<class T>
bool BinaryTree<T>::AncestorsOfKey (const T & key, std::vector<T> &ancestors){
  BinaryTree<T> *tree_of_key;
  if (this->FindValueInTree(key, tree_of_key)){
    BinaryTree<T> *current_tree = tree_of_key;

      while (current_tree->parent_!=NULL){
        current_tree = current_tree->parent_;
        ancestors.push_back(current_tree->root_value_);
      }
    return true;
  }
  else {
    return false;
  }
}

template<class T>

void CHECK_EQUAL (const T true_result, const T obtained_result){
  if (true_result==obtained_result) cout<<"Ok!"<<endl;
  else {
    cout<<"Obtained "<<obtained_result<<" but expected "<<true_result<<endl;
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



  bt->PrintInorder();
  cout<<endl<<endl;
  bt3->PrintInorder();
  cout<<endl<<endl;


  vector<int> v;
  BinaryTree<int> *aux;

  int key = 9;
  cout<<"Ancestors of key "<<key<<endl;
  bt3->AncestorsOfKey(key,v);
  for (int i=0;i<v.size();++i) cout<<v[i]<< " ";
  cout<<endl;

  int lca_value;
  bool lca_success = bt3->LowestCommonAncestor(4,2,lca_value);

  if (lca_success){
    CHECK_EQUAL(2,lca_value);
  }
  else {
    cout<<"Lowest common ancestor not found"<<endl;
  }


}
