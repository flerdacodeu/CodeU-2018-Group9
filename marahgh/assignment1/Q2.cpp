
#include <iostream>
#include <ext/slist>

using namespace std;


/*Node's list class */
template <typename T>
class Node{
    T data;
    Node* next;
    public:
    Node(T data):data(data),next(nullptr){
    }
    Node* getNext(){
       return next; 
    }
    T& getData(){
        return data;
    }
	void setData(T& data){
		data=data;
	}
	void setNext(Node* node){
		next=node;
	}
	
};
//----------------------------------------------------------------------------------//
/* A generic list with basic functionality, constructor, destructor,
    insertion to the end if the list and removing the last element of the list*/
template< typename T>
class List{
    
	Node<T>* head;
	Node<T>* tail;
	int size;
	
	public:
	
	List():head(nullptr),tail(nullptr),size(0){}
	
	Node<T>* getHead(){
	    if(!this){
	       return nullptr;
	    }
	    return head;
	}
	
	int getSize(){
	    if(!this){
	        return -1;
	    }
        return size;
    }
	
	void insertLast(T& data){
	    Node<T>* nodeToInsert = new Node<T>(data);
	    nodeToInsert->setNext(nullptr);
		if(!head){
			head=nodeToInsert;
			tail=nodeToInsert;
			size=1;
			return;
		}
		tail->setNext(nodeToInsert);
		tail=nodeToInsert;
		size++;
	}

    void removeLast(){
        if(!head){
            return;
        }
        Node<T>* curr=head;
        Node<T>* beforeLast=nullptr;
        if(curr->getNext()==nullptr){
            delete head;
            head=nullptr;
            tail=nullptr;
            size=0;
            return;
        }
        while (curr){
            if(curr->getNext()== tail){
                beforeLast=curr;
                break;
            }
            curr=curr->getNext();
        }
        delete tail;
        tail=beforeLast;
        beforeLast->setNext(nullptr);
        size--;
    }
    
	~List(){
	    if(!head){
	        return;
	    }
	    Node<T>* currentNode = this->head; 
        while (currentNode){
            Node<T>* nextNode = currentNode->getNext();    
            delete currentNode;                         
            currentNode = nextNode;    
        }
    }
};

//----------------------------------------------------------------------------------//
/* A function to return the kth to last element of a singly linked list*/
template<typename T>
T* getKthToLast(List<T>& list, int k){
    if(!list.getHead()){
        return nullptr;
    }
    int listSize=list.getSize();
    if(k<0 || k>=listSize){
        return nullptr; 
    }
    Node<T>* tmp=list.getHead();
    for(int i=0;i<listSize-k-1;i++){
        tmp=tmp->getNext();
    }
    return &(tmp->getData());
}

