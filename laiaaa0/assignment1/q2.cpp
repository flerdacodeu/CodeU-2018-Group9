#include <iostream>
using namespace std;

template <class T>
class ListNode{
  private:
    T value;
    ListNode * next;
  public:
    ListNode(){

        this->next = NULL;

    }
    ListNode(T v, ListNode * nextNode){
      this->value = v;
      this->next = nextNode;
    }

    T getValue(){
      return value;
    }
    ListNode * getNext (){
      return next;
    }
    void setNext (ListNode *n){
      this->next = n;
    }
    void setValue (T v){
      this->value = v;
    }
};
template <class T>

class MyList{
  private:
    ListNode<T> *initialNode;
    int size;
  public:
    MyList(){
      cout<<"New list created"<<endl;
    }
    MyList(ListNode<T> *init){
      this->initialNode=init;
      if (init!=NULL){

        ListNode<T>* curr;
        curr = init->getNext();

        this->size = 1;
        while (curr!=NULL){
          this->size++;
          curr = curr->getNext();
        }
        //cout<<"Size is "<<this->size<<endl;

      }//cout<<"New list created"<<endl;

    }

    T getInitialNode(){
      return this->initialNode;
    }
    int getSize(){
      return this->size;
    }
    void printList (){
      ListNode<T> *current = this->initialNode;
      while (current!=NULL){
          cout<<current->getValue()<<" ";
          current = current->getNext();
      }
      cout<<endl;
    }
    int recalculateSize(){ //probably not used
      ListNode<T> *current = this->initialNode;
      this->size = 0;
      while (current!=NULL){
        this-> size ++;
        current = current->getNext();
      }
      return this->size;
    }
    T kth_to_last(int k){
      //assume that size is correctly calculated.
      int itemPosition = this->size-k;
      if (itemPosition<0){
        cout<<"The value "<<k<<" is larger than the list"<<endl;
        return -1;
      }
      else {

        ListNode<T> *currentNode = this->initialNode;
        for (int i = 0; i<itemPosition-1; ++i){
          currentNode = currentNode->getNext();
        }
        return currentNode->getValue();

      }
    }
};
void runTest(int k, int n);
int main (){
  runTest(13, 20);
}
void runTest(int k, int n){
  ListNode<int> *initial = new ListNode<int>;
  ListNode<int> *current = new ListNode<int>;

  initial->setValue(0);
  initial->setNext(current);
  current->setValue(1);

  for (int i=2; i<n; ++i){
    ListNode<int>*newNode = new ListNode<int>;
    newNode->setValue(i);
    current->setNext(newNode);
    current = newNode;
  }
  MyList<int> l (initial);
  cout<<"The list is:"<<endl;
  l.printList();
  cout<<"The "<<k<<"-th to last element is"<<endl;
  cout<<l.kth_to_last(k)<<endl;

}
