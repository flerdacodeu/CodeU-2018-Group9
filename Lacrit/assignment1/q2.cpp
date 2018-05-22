#include <iostream>


template<class T> 
struct Node
{
    T i;
    struct Node *next;
};


template<class T> 
T findNode (Node<T> *listHead, int n)
{
     Node<T> *ptr1, *ptr2;  // we need 2 pointers
     ptr1 = ptr2 = listHead; // set the pointers to point to the list head initially

    while(ptr1->next != NULL) // keep looping until we reach the tail (next will be NULL for the last node)
    {
        if(n > 0)
        {
            ptr1 = ptr1->next; //increment only the 1st pointer
            n--;
        }
        else
        {
            ptr1 = ptr1->next; //increment both pointers
            ptr2 = ptr2->next;
        }
   }
   return ptr2->i;
}

template<class T> 
void push(Node<T>** head, T data)
{
  Node<T>* new_node =(Node<T>*) malloc(sizeof(Node<T>));
 
  new_node->i  = data;
  new_node->next = (*head);
 
  *head = new_node;
}


int main() 
{
  //char just to test (could be anything)
  Node<char>* head = NULL;

  // create linked r->n->b->a
  push(&head, 'a');
  push(&head, 'b');
  push(&head, 'n');
  push(&head, 'r');

  std::cout << findNode(head, 3) << std::endl;
  return 0;

}
