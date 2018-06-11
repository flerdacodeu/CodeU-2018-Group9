#include <iostream>
#include <stdexcept>
using namespace std;
/*
Check for loops
Free all elements when list is destroyed
Unique pointers
*/
template <class T>
class ListNode{
  private:
    T node_value_;
    ListNode * node_next_;
  public:
    ListNode(){
        this->node_next_ = NULL;
    }
    ListNode(T v, ListNode * nextNode){
      this->node_value_ = v;
      this->node_next_ = nextNode;
    }

    const T & GetValue(){
      return this->node_value_;
    }
    ListNode * GetNext (){
      return this->node_next_;
    }
    void SetNext (ListNode *n){
      this->node_next_ = n;
      /*
TODO
This is a bit risky, how ca you avoid clients messing thing up?
For example, a user can create a loop on the list, or make two different lists have converge into one, something like :
A -> B -> C -> D
&
E -> C -> D
      */
    }
    void SetValue (T v){
      this->node_value_ = v;
    }
};
template <class T>

class MyList{
  private:
    ListNode<T> *list_initial_node_;
    int list_size_;
  public:
    MyList(){
    }
    MyList(ListNode<T> *init){
      this->list_initial_node_=init;
      this->list_size_ = RecalculateSize();

    }

    const T & GetInitialNode(){
      return this->list_initial_node_;
    }
    int GetSize(){
      return this->list_size_;
    }
    void PrintList (){
      ListNode<T> *current = this->list_initial_node_;
      while (current!=NULL){
          cout<<current->GetValue()<<" ";
          current = current->GetNext();
      }
      cout<<endl;
    }
    
    int RecalculateSize(){
      ListNode<T> *current = this->list_initial_node_;
      this->list_size_ = 0;
      while (current!=NULL){
        this-> list_size_ ++;
        current = current->GetNext();
      }
      return this->list_size_;
    }
    const T & KthToLast(int k){
      if (k<0){
        throw invalid_argument("k is negative");
      }
      int itemPosition = this->list_size_-k;
      if (itemPosition<=0){
        throw invalid_argument("k is larger than the list ");
      } else {

        ListNode<T> *current_node = this->list_initial_node_;
        for (int i = 0; i<itemPosition-1; ++i){
          current_node = current_node->GetNext();
        }
        return current_node->GetValue();

      }
    }
};
void RunTest(int k, int n);
int main (){
  for (int i =0; i<20;++i){
    RunTest(i,20);
  }
}
void RunTest(int k, int n){
  ListNode<int> *initial = new ListNode<int>;
  ListNode<int> *current = new ListNode<int>;

  initial->SetValue(0);
  initial->SetNext(current);
  current->SetValue(1);

  for (int i=2; i<n; ++i){
    ListNode<int>*newNode = new ListNode<int>;
    newNode->SetValue(i);
    current->SetNext(newNode);
    current = newNode;
  }
  MyList<int> l (initial);
  //cout<<"The list is:"<<endl;
  //l.PrintList();
  cout<<"The "<<k<<"-th to last element is"<<endl;
  cout<<l.KthToLast(k)<<endl;

}
