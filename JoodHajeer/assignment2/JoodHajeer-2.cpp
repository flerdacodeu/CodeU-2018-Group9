#include <iostream>
#include <stdio.h>  
#include <string>
#include <queue>
#include <stack>
#include <stdlib.h>
using namespace std;

template <class T>
class Binary_Tree;
template <class T>
class BTNode {
	//Binary tree Node Class building block for a BT
	// A BT node class to store elements of a generic type T
public:
	BTNode(T &VAL, BTNode * LEFT = nullptr, BTNode * RIGHT = nullptr, BTNode * PARENT = nullptr, int DEPTH = -1) : val(VAL), left(LEFT), right(RIGHT), parent(PARENT), depth(DEPTH) {};
	~BTNode() {};
private:
	T val;
	BTNode * left;
	BTNode * right;
	BTNode * parent;
	int depth;
	friend class Binary_Tree<T>;
};
template <class T>
class Binary_Tree{
public:
	Binary_Tree();
	Binary_Tree(const Binary_Tree <T> &)=delete;
	Binary_Tree & operator =(const Binary_Tree <T> &)=delete;
	~Binary_Tree();
	bool insert( T &VAL, T& PARENT, bool insertToTheRight); //insert left or right child to a chosen parent
	bool insertRoot( T &VAL);
	bool empty();
	void clear(); 
	bool find( T & VAL);
	bool getAncestors( T & VAL, vector<T> & ancestors);
	bool commonAncestor( T & NODE1,  T & NODE2, T& firstCommonAncestor);
private:
	BTNode<T> * root;
	void clear(BTNode<T>* node); //private clear don't want the user to mess the root
	BTNode<T> * find(T & VAL, BTNode<T> *);
};
template <class T>
Binary_Tree<T> ::Binary_Tree() {
	root = nullptr;
}
template <class T>
Binary_Tree<T> :: ~Binary_Tree() {
	clear();
}
template <class T>
bool Binary_Tree<T> ::empty() {
	return root == nullptr;
}
template <class T>
void Binary_Tree<T> ::clear() {
	clear(root); 
	root = nullptr;
}
template <class T>
void Binary_Tree<T> ::clear( BTNode<T>* node) { // post-order traverese to delete nodes in a tree
	if (!node)
		return;
	clear(node->left);
	clear(node->right);
	delete node;
}

template <class T>
bool Binary_Tree<T> ::find( T &VAL) {//check if value already exists in the tree
	return find(VAL, root)!=nullptr;
}
template <class T>
BTNode<T> * Binary_Tree<T> ::find(T &VAL, BTNode<T> * node) {//return a pointer to the node with val if exists
	if (node == nullptr)
		return nullptr;
	if (node->val == VAL)
		return node;
	BTNode<T> * leftSide = find(VAL, node->left);
	if (leftSide != nullptr)
		return leftSide;
	BTNode<T> * rightSide = find(VAL, node->right);
	return rightSide;
}
template <class T>
bool Binary_Tree<T> ::insert(T &VAL, T & PARENT, bool insertToTheRight ) {//insert node to a non-empty tree
	//insert only unique values , insertToTheRight tells left =false  or right child =true
	if (find(VAL))//value already exist in the tree, do not insert it
		return false;
	BTNode<T> * prevNode = find(PARENT , root);
	if (prevNode == nullptr)//parent node was not found, or tree is empty
		return false; 
	if (prevNode->left != nullptr && insertToTheRight == false) //parent already has a left child
		return false;
	if (prevNode->right != nullptr && insertToTheRight == true)//parent already has a right child
		return false;
	BTNode<T> * newNode = new BTNode<T>(VAL, nullptr, nullptr, prevNode , prevNode->depth+1); //val, left, right, patent, new depth
	if (insertToTheRight ==false)
		prevNode->left = newNode;
	else if (insertToTheRight ==true)
		prevNode->right = newNode;
	return true;
}
template <class T>
bool Binary_Tree<T> :: insertRoot( T &VAL) {
	if (root != nullptr)
		return false;
	BTNode<T> * newNode = new BTNode<T>(VAL, nullptr, nullptr, nullptr, 0); //val, left, right, parent, depth
	root = newNode;
	return true;
}

template <class T>
bool Binary_Tree<T> ::getAncestors( T & VAL, vector<T> & ancestors) {//get ancestors of node starting from the root
	BTNode<T> * node = find(VAL, root);
	if (node == nullptr) //tree is empty or value not found
		return false;
	node = node->parent;
	while (node != nullptr) {
		ancestors.push_back(node->val);
		node = node->parent;
	}
	return true;
}
template <class T>
bool Binary_Tree<T> ::commonAncestor(T & VAL1,  T & VAL2, T& firstCommonAncestor) { //complexity O(tree height)
	BTNode<T> * node1 = find(VAL1,root); //search for VAL1 in the tree and hold a pointer to the node with value VAL1
	if (node1 == nullptr) //value1 is not in the tree
		return false;
	BTNode<T> * node2 = find(VAL2,root); //same for VAL2
	if (node2 == nullptr) //value2 is not in the tree
		return false;
	while (node1 != node2) { //move the pointer with max depth to its parent, stop when both pointers are equal, first common ancestor is found.
		if (node1->depth >= node2->depth)
			node1 = node1->parent;
		else
			node2 = node2->parent;
	}
	firstCommonAncestor = node1->val;
	return true;
}
void fillTree(vector <int>& values,Binary_Tree<int> & myBT) {//hard-coded test case
	/*
						   1
						  / \
						 2   5
						/ \
					       3   4
	*/
	myBT.insertRoot(values[0]);
	myBT.insert(values[1], values[0], false);
	myBT.insert(values[2], values[1], false);
	myBT.insert(values[3], values[1], true);
	myBT.insert(values[4], values[0], true);
}
void testGetAncestors_valNotInTree(Binary_Tree<int> & myBT) {
	int i = 7;
	vector<int> v;
	if (!myBT.getAncestors(i, v))
		cout << i << " is not in tree" << endl;
	else
		cout << "error with get ancestors node not in tree case" << endl;
}
void testGetAncestors_valInTree(Binary_Tree<int> & myBT) {
	int i = 4;
	vector<int> v;
	if (myBT.getAncestors(i, v)) {
		cout << "ancestors of " << i << " are: ";
		for (int i = 0; i < v.size(); i++)
			cout << v[i] << " ";
		cout << endl;
	}
	else
		cout << "error with get ancestors node in tree case" << endl;
}
void testGetAncestors_Root(Binary_Tree<int> & myBT) {
	int i = 1;
	vector<int> v;
	if (myBT.getAncestors(i, v) && !v.size())
		cout << i << " is the root " << endl;
	else
		cout << "error with get ancestors node is the root case" << endl;
}
void testCommonAncestor_OneValueNotInTree(vector <int> & values,Binary_Tree<int> & myBT) {
	int res;
	int i = 7;
	if (!myBT.commonAncestor(values[1], i, res))
		cout <<i<< " is not in tree"<< endl;
	else
		cout << "error with LCA value not in tree case" << endl;
}
void testCommonAncestor_ValuesInTree(vector <int> & values, Binary_Tree<int> & myBT) {
	int res;
	if (myBT.commonAncestor(values[2], values[3], res))
		cout <<"LCA of "<< values[2] <<" and "<< values[3] << " is "<<res << endl;
	else
		cout << "error with LCA values in tree case" << endl;
}
void testCommonAncestor_SpecialAncestorRelation(vector <int> & values, Binary_Tree<int> & myBT) {
	int res;
	if (myBT.commonAncestor(values[0], values[3], res))
		cout << "LCA of " << values[0] << " and " << values[3] << " is " << res << endl;
	else
		cout << "error with LCA special ancestor case" << endl;
}

int main() {
	vector<int> values = { 1,2,3,4,5 };
	Binary_Tree<int> myBT;
	fillTree(values,myBT);
	testGetAncestors_valNotInTree(myBT);
	testGetAncestors_valInTree(myBT);
	testGetAncestors_Root(myBT);
	testCommonAncestor_OneValueNotInTree(values,myBT);
	testCommonAncestor_ValuesInTree(values, myBT);
	testCommonAncestor_SpecialAncestorRelation(values, myBT);
	return 0;
}
