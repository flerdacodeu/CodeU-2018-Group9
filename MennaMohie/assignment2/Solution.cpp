#include<bits/stdc++.h>
using namespace std;

enum direction {addLeft, addRight};

template<class T>
class BinaryTree;

template<class T>
class Node
{
    T value;
    Node *left, *right;
    friend class BinaryTree<T>;

public:
    Node(T val):left(nullptr),right(nullptr),value(val) {}

    T getValue()
    {
        return value;
    }
};

template<class T>
class BinaryTree
{
    Node<T> *root;
    int Size;
    add(Node<T>* currentRoot, T parentVal, T val, direction dir)
    {
        if(currentRoot->value==parentVal)
        {
            if(dir==0)
            {
                if(currentRoot->left==nullptr)
                {
                    currentRoot->left=new Node<T>(val);
                    Size++;
                    return true;
                }
                else
                    return false;
            }
            if(dir==1)
            {
                if(currentRoot->right==nullptr)
                {
                    currentRoot->right=new Node<T>(val);
                    return true;
                }
                else
                    return false;
            }
        }
        if(dir==0)
        {
            if(addChildToParent(currentRoot->left, parentVal, val, addLeft))
                return true;
            return addChildToParent(currentRoot->right, parentVal, val, addLeft);
        }
        if(dir==1)
        {
            if(addChildToParent(currentRoot->left, parentVal, val, addRight))
                return true;
            return addChildToParent(currentRoot->right, parentVal, val, addRight);
        }
    }
public:
    BinaryTree(T val):root(new Node<T>(val)),Size(1) {}

    Node<T>* getRoot()
    {
        return root;
    }

    Node<T>* contains(Node<T> *currentRoot, T val)
    {
        if(currentRoot==nullptr || currentRoot->value==val)
            return currentRoot;
        Node<T> *leftSide = contains(currentRoot->left, val);
        Node<T> *rightSide = contains(currentRoot->right, val);
        return (leftSide==nullptr?rightSide:leftSide);
    }

    //adds a new node (val) as a left/right child (depends on dir) to an existing node (parentVal)
    bool addChildToParent(Node<T> *currentRoot, T parentVal, T val, direction dir)
    {
        if(!contains(root, parentVal) || contains(root, val) || currentRoot==nullptr)
            return false;
        else
            add(currentRoot, parentVal, val, dir);
    }

    void traverse(Node<T> *currentRoot, string indentation="")
    {
        if(currentRoot==nullptr)
        {
            cout<<indentation<<'*'<<endl;
            return;
        }
        cout<<indentation<<currentRoot->value<<endl;
        traverse(currentRoot->left,indentation+" ");
        traverse(currentRoot->right,indentation+" ");
    }

    bool getAncestors(Node<T> *currentRoot, T val, vector<T>& path)
    {
        path.clear();

        if(currentRoot==nullptr)
            return false;

        if(currentRoot->value==val)
            return true;

        bool foundInLeft = getAncestors(currentRoot->left, val, path);
        bool foundInRight = getAncestors(currentRoot->right, val, path);
        if(foundInLeft || foundInRight)
        {
            path.push_back(currentRoot->value);
        }

        return (foundInLeft || foundInRight);
    }

    Node<T> * leastCommonAncestor(Node<T> *currentRoot, T val1, T val2)
    {
        if(!contains(root,val1) || !contains(root, val2) || currentRoot==nullptr)
            return nullptr;
        if (currentRoot->value == val1 || currentRoot->value == val2)
            return currentRoot;
        Node<T> *left = leastCommonAncestor(currentRoot->left, val1, val2);
        Node<T> *right = leastCommonAncestor(currentRoot->right, val1, val2);
        if(left==nullptr && right==nullptr)
            return nullptr;
        if(left!=nullptr && right!=nullptr)
            return currentRoot;
        if(left!=nullptr)
            return left;
        else
            return right;

    }
};

int main()
{
    BinaryTree<int> tree(1);
    tree.addChildToParent(tree.getRoot(), 1, 2, addLeft);
    tree.addChildToParent(tree.getRoot(), 1, 3, addRight);
    tree.addChildToParent(tree.getRoot(), 2, 4, addLeft);
    tree.addChildToParent(tree.getRoot(), 2, 5, addRight);
    tree.addChildToParent(tree.getRoot(), 3, 6, addLeft);
    tree.addChildToParent(tree.getRoot(), 3, 7, addRight);
    tree.addChildToParent(tree.getRoot(), 7, 8, addLeft);
    tree.addChildToParent(tree.getRoot(), 8, 9, addRight);

    tree.traverse(tree.getRoot());

    vector<int> ancestors;
    if(tree.getAncestors(tree.getRoot(), 9, ancestors))
    {
        cout<<"Ancestors of 9: ";
        for(int ancestor : ancestors)
            cout<<ancestor<<' ';
        cout<<endl;
    }

    if(tree.getAncestors(tree.getRoot(), 6, ancestors))
    {
        cout<<"Ancestors of 6: ";
        for(int ancestor : ancestors)
            cout<<ancestor<<' ';
        cout<<endl;
    }

    Node<int> * LCA = tree.leastCommonAncestor(tree.getRoot(), 5, 4);
    cout<<"LCA of 5 and 4: "<<LCA->getValue()<<endl;
    LCA = tree.leastCommonAncestor(tree.getRoot(), 7, 2);
    cout<<"LCA of 7 and 2: "<<LCA->getValue()<<endl;
    LCA = tree.leastCommonAncestor(tree.getRoot(), 9, 8);
    cout<<"LCA of 9 and 8: "<<LCA->getValue()<<endl;


    return 0;
}
