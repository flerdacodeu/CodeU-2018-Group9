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

    bool add(Node<T>* currentRoot, T parentVal, T val, direction dir)
    {
        if(currentRoot==nullptr)
            return false;

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
        if(dir==addLeft)
        {
            if(add(currentRoot->left, parentVal, val, addLeft))
                return true;
            return add(currentRoot->right, parentVal, val, addLeft);
        }
        if(dir==addRight)
        {
            if(add(currentRoot->left, parentVal, val, addRight))
                return true;
            return add(currentRoot->right, parentVal, val, addRight);
        }
    }

    bool ancestors(Node<T> *currentRoot, T val, vector<T>&path)
    {
        if(currentRoot==nullptr)
            return false;

        if(currentRoot->value==val)
        {
            path.clear();
            return true;
        }

        bool foundInLeft = ancestors(currentRoot->left, val, path);
        bool foundInRight = ancestors(currentRoot->right, val, path);
        if(foundInLeft || foundInRight)
        {
            path.push_back(currentRoot->value);
        }

        return (foundInLeft || foundInRight);
    }

    Node<T> *LCA(Node<T> *currentRoot, T val1, T val2)
    {
        if(currentRoot==nullptr)
            return nullptr;

        if (currentRoot->value == val1 || currentRoot->value == val2)
            return currentRoot;
        Node<T> *left = LCA(currentRoot->left, val1, val2);
        Node<T> *right = LCA(currentRoot->right, val1, val2);
        if(left==nullptr && right==nullptr)
            return nullptr;
        if(left!=nullptr && right!=nullptr)
            return currentRoot;
        if(left!=nullptr)
            return left;
        else
            return right;
    }

public:
    BinaryTree(T val):root(new Node<T>(val)),Size(1) {}

    Node<T>* getRoot()
    {
        return root;
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

    Node<T>* findNode(Node<T> *currentRoot, T val)
    {
        if(currentRoot==nullptr || currentRoot->value==val)
            return currentRoot;
        Node<T> *leftSide = findNode(currentRoot->left, val);
        Node<T> *rightSide = findNode(currentRoot->right, val);
        return (leftSide==nullptr?rightSide:leftSide);
    }

    //adds a new node (val) as a left/right child (depends on dir) to an existing node (parentVal)
    bool addChildToParent(T parentVal, T val, direction dir)
    {
        if(!findNode(root, parentVal) || findNode(root, val) || root==nullptr)
            return false;
        else
            return add(root, parentVal, val, dir);
    }

    bool getAncestors(T val, vector<T>& path)
    {
        if(root==nullptr)
            return false;
        else
            return ancestors(root, val, path);
    }

    Node<T> *leastCommonAncestor(T val1, T val2)
    {
        if(!findNode(root,val1) || !findNode(root, val2) || root==nullptr)
            return nullptr;
        else
            return LCA(root, val1, val2);

    }
};

int main()
{
    BinaryTree<int> tree(1);
    tree.addChildToParent(1, 2, addLeft);
    tree.addChildToParent(1, 3, addRight);
    tree.addChildToParent(2, 4, addLeft);
    tree.addChildToParent(2, 5, addRight);
    tree.addChildToParent(3, 6, addLeft);
    tree.addChildToParent(3, 7, addRight);
    tree.addChildToParent(7, 8, addLeft);
    tree.addChildToParent(8, 9, addRight);

    tree.traverse(tree.getRoot());

    vector<int> ancestors;
    if(tree.getAncestors(9, ancestors))
    {
        cout<<"Ancestors of 9: ";
        for(int ancestor : ancestors)
            cout<<ancestor<<' ';
        cout<<endl;
    }

    if(tree.getAncestors(6, ancestors))
    {
        cout<<"Ancestors of 6: ";
        for(int ancestor : ancestors)
            cout<<ancestor<<' ';
        cout<<endl;
    }

    Node<int> * LCA = tree.leastCommonAncestor(5, 4);
    cout<<"LCA of 5 and 4: "<<LCA->getValue()<<endl;
    LCA = tree.leastCommonAncestor(7, 2);
    cout<<"LCA of 7 and 2: "<<LCA->getValue()<<endl;
    LCA = tree.leastCommonAncestor(9, 8);
    cout<<"LCA of 9 and 8: "<<LCA->getValue()<<endl;

    return 0;
}
