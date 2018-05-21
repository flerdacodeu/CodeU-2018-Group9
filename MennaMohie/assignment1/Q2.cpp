#include<bits/stdc++.h>
#include<stdlib.h>
#define endl '\n'

using namespace std;

template<class T>
class SinglyLinkedList;

template<class T>
class Node
{
    T value;
    Node *next;
    Node():next(NULL) {}
    Node(T val):next(NULL),value(val) {}
    ~Node() {}

    friend class SinglyLinkedList<T>;
};

template<class T>
class SinglyLinkedList
{

    Node<T> *head, *tail;
    int Size;

public:
    SinglyLinkedList():head(NULL),tail(NULL),Size(0) {}

    void DisplayKthToLastNode(int k)
    {
        assert(k>=0 && k<Size);
        int pos=Size-k-1;
        DisplayAt(pos);

    }

    void DisplayAt(int pos)
    {
        assert(pos>=0 && pos<Size);
        int i=0;
        Node<T> *temp = head;
        while(temp!=NULL)
        {
            if(i==pos)
            {
                cout<<temp->value<<endl;
                break;
            }
            temp=temp->next;
            i++;
        }
    }

    void DisplayAll()
    {
        Node<T> *temp = head;
        while(temp!=NULL)
        {
            cout<<temp->value<<' ';
            temp=temp->next;
        }
        cout<<endl;
        delete temp;
    }

    void Add(T val)
    {
        Node<T> *new_node = new Node<T>(val);
        if(head==NULL)
        {
            head=tail=new_node;
        }
        else
        {
            tail->next = new_node;
            tail=new_node;
        }
        Size++;
    }

    void AddAt(T val, int pos)
    {
        assert(pos>=0 && pos<=Size);
        Node<T> *new_node = new Node<T>(val);
        if(pos==0)
        {
            new_node->next=head;
            head=new_node;
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
            while(head->next!=NULL)
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
            delete temp;
        }
        Size++;
    }

    void Delete(T val) //deletes first occurrence of a value if it's repeated
    {

        if(head->value==val)
        {
            Node<T> *node_to_delete = head;
            head=head->next;
            delete node_to_delete;
            Size--;
        }
        else
        {
            Node<T> *temp = head;
            while(temp->next != NULL)
            {
                if(temp->next->value==val)
                {
                    Node<T> *node_to_delete = temp->next;
                    temp->next = node_to_delete->next;
                    if(node_to_delete->next==NULL)
                        tail=temp;
                    delete node_to_delete;
                    Size--;
                    break;
                }
                temp=temp->next;
            }
            delete temp;
        }
    }

    void DeleteAt(int pos)
    {
        assert(pos>=0 && pos<Size);
        if(pos==0)
        {
            Node<T> *node_to_delete = head;
            head=head->next;
            delete node_to_delete;
            Size--;
        }
        else
        {
            assert(pos>=0);
            Node<T> *temp=head;
            int i=0;
            while(temp->next!=NULL)
            {
                if(i==pos-1)
                {
                    Node<T> *node_to_delete = temp->next;
                    temp->next = node_to_delete->next;
                    if(node_to_delete->next==NULL)
                        tail=temp;
                    delete node_to_delete;
                    Size--;
                    break;
                }
                temp=temp->next;
                i++;
            }
            delete temp;
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
    SLL.DisplayKthToLastNode(0);
    SLL.DisplayKthToLastNode(1);
    SLL.Delete('b');
    SLL.DisplayAll();
    SLL.AddAt('x',1);
    SLL.DisplayAll();
    SLL.DeleteAt(3);
    SLL.DisplayAll();
    SLL.Delete('a');
    SLL.Add('z');
    SLL.DisplayAll();
    SLL.DisplayKthToLastNode(2);

    return 0;
}
