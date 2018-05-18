#include <iostream>
using namespace std;

struct list_node{
  int value;
  list_node * next;
}
struct sl_list{
  list_node initialNode;
  int listLength;
}


int kth_to_last (sl_list l, int k){
  int itemPosition = l->listLength-k;
  list_node currentNode = l->initialNode;
  for (int i = 0; i<itemPosition; ++i){
    currentNode = currentNode->next;

  }
  return currentNode;
}
