#include <iostream>


template<class T> 
struct Node
{
	private:
    	T i;
		Node *next;
	public: 
		Node* get_next()
		{
			return next;
		}  
		T get_i()
		{
			return i;
		}
		void set_next(Node *new_next)
		{
			next = new_next;
		}
		void set_i(T j)
		{
			i = j;
		}
			
};


template<class T> 
T findNode (Node<T> *listHead, int n)
{
	 if (listHead == NULL) return 0; 
     Node<T> *ptr1, *ptr2;  // we need 2 pointers
     ptr1 = ptr2 = listHead; // set the pointers to point to the list head initially

    while(ptr1->get_next() != NULL) // keep looping until we reach the tail (next will be NULL for the last node)
    {
        if(n > 0)
        {
            ptr1 = ptr1->get_next(); //increment only the 1st pointer
            n--;
        }
        else
        {
            ptr1 = ptr1->get_next(); //increment both pointers
            ptr2 = ptr2->get_next();
        }
   }
   return ptr2->get_i();
}

template<class T> 
void push(Node<T>** head, T data)
{
  //Node<T>* new_node =(Node<T>*) malloc(sizeof(Node<T>))
  //Just left the upper row for reference. Correction:
  Node<T>* new_node = new Node<T>(); // no need to pass the size
  new_node->set_i(data);
  new_node->set_next((*head));
 
  *head = new_node;
}

template<class T>
void free_nodes(Node<T>* head) 
{
	Node<T>* temp; 
	while (head != NULL) 
	{
		temp = head; 
		head = head->get_next(); 
		free(temp);
	}
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
  free_nodes(head);
  return 0;

}
