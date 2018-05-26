

#include <iostream>
#include <ext/slist>

using namespace std;


//----------------------------------------------------------------------------------//
/* A generic list with basic functionality, constructor, destructor,
    insertion to the end if the list and removing the last element of the list*/
template< typename T>
class List{
/*Node's list class */
template <typename S>
class Node{
    public:
    S data;
    Node<S>* next;
    public:
    Node(S data):data(data),next(nullptr){
    }
};    
	private:
	Node<T>* head;
	Node<T>* tail;
	int size;
	
	public:
	
	List():head(nullptr),tail(nullptr),size(0){}
	
	Node<T>* getHead(){
	    return head;
	}
	
	int getSize(){
        return size;
    }
	
	void insertLast(T& data){
	    Node<T>* nodeToInsert = new Node<T>(data);
	    nodeToInsert->next=nullptr;
		if(!head){
			head=nodeToInsert;
			tail=nodeToInsert;
			size=1;
			return;
		}
		tail->next=nodeToInsert;
		tail=nodeToInsert;
		size++;
	}

    void removeLast(){
        if(!head){
            return;
        }
        Node<T>* curr=head;
        if(curr->next==nullptr){
            delete head;
            head=nullptr;
            tail=nullptr;
            size=0;
            return;
        }
        while (curr){
            if(curr->next== tail){
                break;
            }
            curr=curr->next;
        }
        delete tail;
        tail=curr;
        curr->next=nullptr;
        size--;
    }
    
	~List(){
	    if(!head){
	        return;
	    }
	    Node<T>* currentNode = this->head; 
        while (currentNode){
            Node<T>* nextNode = currentNode->next;    
            delete currentNode;                         
            currentNode = nextNode;    
        }
    }
//----------------------------------------------------------------------------------//
/* A Method to return the kth to last element of a singly linked list*/

T* getKthToLast(int k){
    if(!head){
        return nullptr;
    }
    if(k<0 || k>=size){
        return nullptr; 
    }
    Node<T>* tmp=head;
    for(int i=0;i<size-k-1;i++){
        tmp=tmp->next;
    }
    return &(tmp->data);
}    
    
};
