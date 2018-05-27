
//ASSUMPTIONS
/*
- the "kth_to_last" function is a part of the linkedlist class
- the "kth_to_last" function assumes the list size is unknown
- the "kth_to_last" function takes O(n) time and 0(1) space.
*/

#include <iostream>
using namespace std;

template <class T>
class linkedlist {

    struct Node {
        T data;
        Node *next;
        Node(const T &input, Node *next) : data(input), next(next) {}
    };
    int listsize;
    Node *head;
    Node *tail;


    struct empty_list_exception : public exception {
        const char * what () const throw () {
            return "list is empty";
        }
    };
    struct out_of_bounds_exception : public exception {
        const char * what () const throw() {
            return "index out of bounds";
        }
    };


public:
    linkedlist() : head(nullptr), tail(nullptr), listsize(0) {} //first constructor
    ~linkedlist(); //destructor
    const int& size() {return listsize;}
    bool empty() {return listsize==0;}
    T front();
    T back();
    void push_front(const T& input);
    void pop_front();
    void push_back(const T& input);
    void pop_back();
    T kth_to_last(const int& k); // returns the value of the node at kth position from the end of the list // as if  listsize is unknown // takes O(n) time and 0(1) space.
    void print(); //for testing
};

template<class T>
linkedlist<T>::~linkedlist(){
    Node *ptr=head, *temp;
    while(ptr!=nullptr){
        temp=ptr;
        ptr=ptr->next;
        delete temp;
    }
}

template<class T>
T linkedlist<T>::front(){
   if(listsize==0)
        throw empty_list_exception();
    return head->data;
}

template<class T>
T linkedlist<T>::back(){
   if(listsize==0)
        throw empty_list_exception();
    return tail->data;
}

template<class T>
void linkedlist<T>::push_front(const T& input){

    Node *newnode = new Node(input,head);
    head=newnode;
    if(listsize==0)
        tail=head;
    listsize++;
    return;
}
template<class T>
void linkedlist<T>::pop_front(){

     if(listsize==0)
        throw empty_list_exception();

    Node *temp=head;
    head=head->next;
    delete temp;
    listsize--;
    if(listsize == 0){
        tail = nullptr;
    }
    return;
}

template<class T>
void linkedlist<T>::push_back(const T& input){
    Node *newnode= new Node(input,nullptr);
    if(tail!=nullptr)
        tail->next=newnode;
    tail=newnode;
    if(listsize==0) head=tail;
    listsize++;
    return;
}

template<class T>
void linkedlist<T>::pop_back(){

    Node *temp=head;

     if(listsize==0)
        throw empty_list_exception();

    if(listsize==1)
        pop_front();

    else{
        while(temp->next->next!=nullptr){
            temp=temp->next;
        }
        temp->next=nullptr;
        delete tail;
        tail=temp;
        listsize--;
    }

    return;
}

template<class T>
T linkedlist<T>::kth_to_last(const int& k){

    if(k>=listsize || k<0)
        throw out_of_bounds_exception();

    Node *ptr=head, *runner=head;
    for(int i=0; i<k; i++) {
        runner=runner->next;
    }
    while(runner->next!=nullptr){
        ptr=ptr->next;
        runner=runner->next;
    }
    return ptr->data;
}

template<class T>
void linkedlist<T>::print(){
    Node *ptr=head;
    while(ptr!=nullptr){
        cout << ptr->data << " ";
        ptr=ptr->next;
    }
    cout << endl;
    return;
}


int main()
{


    // test
    linkedlist<int> ll;
    ll.push_back(5);
    ll.push_back(3);
    ll.push_back(2);
    ll.push_back(4);
    ll.print();
    cout << ll.kth_to_last(0) << " " << ll.kth_to_last(1) <<  " "  << ll.kth_to_last(2)<< " " << ll.kth_to_last(3)<<  endl;
    cout << ll.kth_to_last(4)<<endl;
    cout << ll.kth_to_last(-1)<<endl;

    return 0;
}
