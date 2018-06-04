#include<bits/stdc++.h>
using namespace std;

template<class T>
class BinaryTree;

template<class T>
class Node
{
    T value;
    Node *left, *right;
    friend class BinaryTree<T>;

public:
    Node():left(nullptr),right(nullptr) {}
    Node(T val):left(nullptr),right(nullptr),value(val) {}
};

template<class T>
class BinaryTree
{
    Node<T> *root;

public:
    BinaryTree(T val):root(new Node<T>(val)) {}

    Node<T>* getRoot()
    {
        return root;
    }

    bool contains(Node<T> *currentRoot, T val)
    {
        if(currentRoot == nullptr)
            return false;
        if(currentRoot->value == val)
            return true;
        return (contains(currentRoot->left, val) || contains(currentRoot->right, val));
    }

    bool resetRoot(T val)
    {
        if(root==nullptr)
        {
            root=new Node<T>(val);
            return true;
        }
        else if(!contains(root, val))
        {
            root->value=val;
            return true;
        }
        else
            return false;
    }

    //adds a new node (val) as a left child to an existing node (parentVal)
    bool addAsLeftChild(Node<T> *currentRoot, T parentVal, T val)
    {
        if(!contains(root, parentVal) || contains(root, val) || currentRoot==nullptr)
            return false;
        if(currentRoot->value==parentVal)
        {
            if(currentRoot->left==nullptr)
            {
                currentRoot->left=new Node<T>(val);
                return true;
            }
            else
            {
                return false;
            }
        }
        if(addAsLeftChild(currentRoot->left, parentVal, val))
            return true;
        return addAsLeftChild(currentRoot->right, parentVal, val);

    }

    bool addAsRightChild(Node<T> *currentRoot, T parentVal, T val)
    {
        if(!contains(root, parentVal) || contains(root, val) || currentRoot==nullptr)
            return false;
        if(currentRoot->value==parentVal)
        {
            if(currentRoot->right==nullptr)
            {
                currentRoot->right=new Node<T>(val);
                return true;
            }
            else
            {
                return false;
            }
        }
        if(addAsRightChild(currentRoot->left, parentVal, val))
            return true;
        else
            return addAsRightChild(currentRoot->right, parentVal, val);

    }

    void traverse(Node<T> *currentRoot)
    {
        if(currentRoot==nullptr)
            return;
        cout<<currentRoot->value<<endl;
        traverse(currentRoot->left);
        traverse(currentRoot->right);
    }

    bool printAncestors(Node<T> *currentRoot, T val)
    {
        if(currentRoot==nullptr)
            return false;

        if(currentRoot->value==val)
            return true;

        bool foundInLeft = printAncestors(currentRoot->left, val);
        bool foundInRight = printAncestors(currentRoot->right, val);
        if(foundInLeft || foundInRight)
        {
            cout<<currentRoot->value<<endl;
        }

        return (foundInLeft || foundInRight);
    }
};

int main()
{
    BinaryTree<int> tree(1);
    tree.addAsLeftChild(tree.getRoot(), 1, 2);
    tree.addAsRightChild(tree.getRoot(), 1, 3);
    tree.addAsLeftChild(tree.getRoot(), 2, 4);
    tree.addAsRightChild(tree.getRoot(), 2, 5);
    tree.addAsLeftChild(tree.getRoot(), 3, 6);
    tree.addAsRightChild(tree.getRoot(), 3, 7);
    tree.addAsLeftChild(tree.getRoot(), 7, 8);
    tree.addAsRightChild(tree.getRoot(), 8, 9);

    tree.printAncestors(tree.getRoot(), 9);

    return 0;
}
