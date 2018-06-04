#include<bits/stdc++.h>
#include<stdlib.h>

using namespace std;

template<class T>
class SinglyLinkedList;

template<class T>
class Node
{
    T value;
    Node *next;
    Node():next(nullptr) {}
    Node(T val):next(nullptr),value(val) {}
    ~Node() {}

    friend class SinglyLinkedList<T>;
};

template<class T>
class SinglyLinkedList
{

    Node<T> *head, *tail;
    int Size;

public:
    SinglyLinkedList():head(nullptr),tail(nullptr),Size(0) {}
    SinglyLinkedList(const SinglyLinkedList<T> &SLL)
    {
        Size = SLL.Size;

        if(SLL.head==nullptr)
        {
            head=nullptr;
            tail=nullptr;
        }
        else
        {
            head=new Node<T>(SLL.head->value);
            Node<T> *this_temp_ptr = head;
            Node<T> *other_list_ptr = SLL.head->next;
            while(other_list_ptr!=nullptr)
            {
                this_temp_ptr->next = new Node<T>(other_list_ptr->value);
                other_list_ptr=other_list_ptr->next;
                this_temp_ptr=this_temp_ptr->next;
            }
            this->tail = this_temp_ptr;

        }
    }
    SinglyLinkedList<T>& operator = (const SinglyLinkedList<T> &SLL)
    {
        this->Size = SLL.Size;

        if(SLL.head==nullptr)
        {
            head=nullptr;
            tail=nullptr;
        }
        else
        {
            head=new Node<T>(SLL.head->value);
            Node<T> *this_temp_ptr = head;
            Node<T> *other_list_ptr = SLL.head->next;
            while(other_list_ptr!=nullptr)
            {
                this_temp_ptr->next = new Node<T>(other_list_ptr->value);
                other_list_ptr=other_list_ptr->next;
                this_temp_ptr=this_temp_ptr->next;
            }
            this->tail = this_temp_ptr;
        }
        return *this;
    }

    T GetKthToLastNode(int k)
    {
        if(k>=0 && k<Size)
        {
            int pos=Size-k-1;
            return(GetAt(pos));
        }

    }

    T GetAt(int pos)
    {
        if(pos>=0 && pos<Size);
        {
            int i=0;
            Node<T> *temp = head;
            while(temp!=nullptr)
            {
                if(i==pos)
                {
                    return temp->value;
                }
                temp=temp->next;
                i++;
            }
        }
    }

    void DisplayAll()
    {
        Node<T> *temp = head;
        while(temp!=nullptr)
        {
            cout<<temp->value<<' ';
            temp=temp->next;
        }
        cout<<endl;
        delete temp;
    }

    void AddAt(T val, int pos)
    {
        if(pos>=0 && pos<=Size);
        {
            Node<T> *new_node = new Node<T>(val);
            if(pos==0)
            {
                new_node->next=head;
                head=new_node;
                if(Size==0)
                    tail=head;
            }
            else if(pos==Size)
            {
                tail->next=new_node;
                tail=new_node;
            }
            else
            {
                Node<T> *temp = head;
                int i=0;
                while(head->next!=nullptr)
                {
                    if(i==pos-1)
                    {
                        new_node->next=temp->next;
                        temp->next=new_node;
                        break;
                    }
                    temp=temp->next;
                    i++;
                }
            }
            Size++;
        }
    }

    void Add(T val)
    {
        AddAt(val, Size);
    }

    void Delete(T val) //deletes first occurrence of a value if it's repeated
    {

        if(head->value==val)
        {
            Node<T> *node_to_delete = head;
            head=head->next;
            delete node_to_delete;
            Size--;
            if(Size==0)
                tail=nullptr;
        }
        else
        {
            Node<T> *temp = head;
            while(temp->next != nullptr)
            {
                if(temp->next->value==val)
                {
                    Node<T> *node_to_delete = temp->next;
                    temp->next = node_to_delete->next;
                    if(node_to_delete->next==nullptr)
                        tail=temp;
                    delete node_to_delete;
                    Size--;
                    break;
                }
                temp=temp->next;
            }
        }
    }

    void DeleteAt(int pos)
    {
        if(pos>=0 && pos<Size);
        {
            if(pos==0)
            {
                Node<T> *node_to_delete = head;
                head=head->next;
                delete node_to_delete;
                Size--;
                if(Size==0)
                    tail=nullptr;
            }
            else
            {
                Node<T> *temp=head;
                int i=0;
                while(temp->next!=nullptr)
                {
                    if(i==pos-1)
                    {
                        Node<T> *node_to_delete = temp->next;
                        temp->next = node_to_delete->next;
                        if(node_to_delete->next==nullptr)
                            tail=temp;
                        delete node_to_delete;
                        Size--;
                        break;
                    }
                    temp=temp->next;
                    i++;
                }
            }
        }
    }

    ~SinglyLinkedList()
    {
        while(Size!=0)
        {
            DeleteAt(0);
        }
    }
};

int main()
{
    SinglyLinkedList<char> SLL;
    SLL.Add('a');
    SLL.Add('b');
    SLL.Add('c');
    SLL.Add('d');
    SLL.DisplayAll();
    cout<<SLL.GetKthToLastNode(0)<<endl;
    cout<<SLL.GetKthToLastNode(1)<<endl;
    SLL.Delete('b');
    SLL.DisplayAll();
    SLL.AddAt('x',1);
    SLL.DisplayAll();
    SLL.DeleteAt(3);
    SLL.DisplayAll();
    SLL.Delete('a');
    SLL.Add('z');
    SLL.DisplayAll();
    cout<<SLL.GetKthToLastNode(2)<<endl;

    SinglyLinkedList<char> SLL2 = SLL; //this uses the copy constructor
    cout<<"\nSLL2=SLL: ";
    SLL2.DisplayAll();
    SLL.Add('m');
    cout<<"SLL+m: ";
    SLL.DisplayAll();
    cout<<"SLL2(SLL+m): ";
    SLL2.DisplayAll();

    SinglyLinkedList<char> SLL3;
    SLL3 = SLL2; //this uses the overloaded assignment operator
    cout<<"SLL3=SLL2: ";
    SLL3.DisplayAll();
    SLL3.Add('2');
    cout<<"SLL3+2: ";
    SLL3.DisplayAll();
    cout<<"SLL2(SLL3+2): ";
    SLL2.DisplayAll();

    return 0;
}
