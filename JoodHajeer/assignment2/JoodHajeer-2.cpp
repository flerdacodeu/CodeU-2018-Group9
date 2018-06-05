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
	BTNode(T &VAL, BTNode * LEFT = nullptr, BTNode * RIGHT = nullptr, BTNode * PARENT = nullptr, int DEPTH = -1);
	~BTNode();
private:
	T val;
	BTNode * left;
	BTNode * right;
	BTNode * parent;
	int depth;
	friend class Binary_Tree<T>;
};
template <class T>
BTNode<T>::BTNode(T &VAL, BTNode * LEFT = nullptr, BTNode * RIGHT = nullptr, BTNode * PARENT = nullptr, int DEPTH = -1){
	val = VAL;
	left = LEFT;
	right = RIGHT;
	parent = PARENT;
	depth = DEPTH;
}
template <class T>
BTNode<T>::~BTNode() {}

template <class T>
class Binary_Tree{
public:
	Binary_Tree();
	Binary_Tree( Binary_Tree <T> &copy_from);
	~Binary_Tree();
	bool insert(T &VAL);
	bool empty();
	void clear(); 
	bool find(T & VAL);
	void printAncestors(T & VAL);
	pair<bool, T> commonAncestor(T & NODE1, T & NODE2);
private:
	BTNode<T> * root;
	BTNode<T> * getRoot();
	void computeDepth(BTNode<T> * );
	void clear(BTNode<T>* node); //private clear don't want the user to mess the root
	BTNode<T> * find(T & VAL, BTNode<T> *);
	BTNode<T> * findAvailableParent();
};
template <class T>
Binary_Tree<T> ::Binary_Tree() {
	root = nullptr;
}
template <class T>
BTNode<T> * Binary_Tree<T> ::getRoot() {
	return root;
}
template <class T>
Binary_Tree<T> ::Binary_Tree( Binary_Tree<T> & copy_from) {
	BTNode<T> * currentNode = copy_from.getRoot();
	root = nullptr;
	if (!currentNode)
		return;
	queue <BTNode<T> *> nodes;
	nodes.push(currentNode);
	while (!nodes.empty()) {
		currentNode = nodes.front();
		nodes.pop();
		this->insert(currentNode->val);
		if(currentNode->left)
			nodes.push(currentNode->left);
		if(currentNode->right)
			nodes.push(currentNode->right);
	}
}
template <class T>
Binary_Tree<T> :: ~Binary_Tree() {
	clear();
}
template <class T>
void Binary_Tree<T> ::computeDepth(BTNode<T> * node) { //compute depth (distance from root) using depth first pre-order traverse
	if (!node) 
		return;
	if (node == root)
		node->depth = 0;
	else
		node->depth = node->parent->depth + 1;
	computeDepth(node->left);
	computeDepth(node->right);
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
BTNode<T> * Binary_Tree<T> ::findAvailableParent() {// find first available parent in level order using breadth first traverese
	if (empty())
		return nullptr;
	queue <BTNode<T> *> parents;
	BTNode<T> * currentNode = root;
	parents.push(currentNode);
	while (!parents.empty()) {
		currentNode = parents.front();
		parents.pop();
		if (!currentNode->left  || !currentNode->right) //found an availabe parent
			return currentNode;
		parents.push(currentNode->left);
		parents.push(currentNode->right);
	}
}
template <class T>
bool Binary_Tree<T> ::find(T &VAL) {//check if value already exists in the tree
	return find(VAL, root)!=nullptr;
}
template <class T>
BTNode<T> * Binary_Tree<T> ::find(T &VAL, BTNode<T> * node) {//return a pointer to the node with val if exists
	if (!node)
		return nullptr;
	if (node->val == VAL)
		return node;
	BTNode<T> * leftSide = find(VAL, node->left);
	BTNode<T> * rightSide = find(VAL, node->right);
	if (leftSide)
		return leftSide;
	return rightSide;
}
template <class T>
bool Binary_Tree<T> :: insert(T &VAL) {//insert only unique values
	if (find(VAL))//value already exist in the tree, do not insert it
		return false;
	BTNode<T> * prevNode = findAvailableParent();
	BTNode<T> * newNode = new BTNode<T>(VAL, nullptr, nullptr, prevNode , -1); //val, left, right, patent, depth
	if (!prevNode) {
		root = newNode;
		return true;
	}
	newNode->parent = prevNode;
	if (!prevNode->left)
		prevNode->left = newNode;
	else
		prevNode->right = newNode;
	return true;
}
template <class T>
void Binary_Tree<T> ::printAncestors(T & VAL) {//print ancestors of node starting from the root
	BTNode<T> * node = find(VAL, root);
	if (!node) {//tree is empty or value not found
		cout << "node was not found in the tree" << endl;
		return ;
	}
	stack <T> ancestorsStack;//save values of ancestors 
	node = node->parent;
	while (node) {
		ancestorsStack.push(node->val);
		node = node->parent;
	}
	if (ancestorsStack.empty()) {
		cout << "node is the root of the tree" << endl;
		return;
	}
	while (!ancestorsStack.empty()) {
		T nextAncestor= ancestorsStack.top();
		ancestorsStack.pop();
		cout << nextAncestor << " ";
	}
	cout << endl;
}
template <class T>
pair<bool,T> Binary_Tree<T> ::commonAncestor(T & VAL1, T & VAL2) { //complexity O(tree height)
	BTNode<T> * node1 = find(VAL1,root); //search for VAL1 in the tree and hold a pointer to the node with value VAL1
	BTNode<T> * node2 = find(VAL2,root); //same for VAL2
	if (!node1 || !node2) //one of the values is not in the tree
		return make_pair(nullptr, VAL1);
	computeDepth(root);
	while (node1 != node2) { //move the pointer with max depth to its parent, stop when both pointers are equal, first common ancestor is found.
		if (node1->depth >= node2->depth)
			node1 = node1->parent;
		else
			node2 = node2->parent;
	}
	return make_pair(true, node1->val);
}
int main() {
	Binary_Tree<int> myBT;
	for(int i=1;i<=13;i++)
		myBT.insert(i);
	int x = 12;
	if (!myBT.insert(x))
		cout << "could not add "<<x<<" again" << endl;
	else
		cout<<"added "<<x<<" again!" << endl;
	
	x = 5;
	if (myBT.find(x))
		cout << "found "<<x<<endl;
	else 
		cout << "couldn't find "<<x << endl;
	for (int i = 0; i <= 13; i++) {
		cout << "Ancestors of " << i << " are :";
		myBT.printAncestors(i);
	}
	
	x = 5;
	int y = 8;
	pair <bool, int> res = myBT.commonAncestor(x, y);
	if (res.first)
		cout << "Common Ancestor of "<<x<< " and "<<y<<" is "<< res.second << endl;
	else
		cout << "Common Ancestor of " << x << " and " << y << " is not found"<< endl;
	x = 14;
	res = myBT.commonAncestor(y, x);
	if (res.first)
		cout << "Common Ancestor of " << x << " and " << y << " is " << res.second << endl;
	else
		cout << "Common Ancestor of " << x << " and " << y << " is not found" << endl;
	Binary_Tree<int> myBT2=myBT;

	myBT.clear();
	cout << "cleared the tree" << endl;

	if (myBT.empty())
		cout << "your tree is empty" << endl;
	else
		cout << "your tree is NOT empty" << endl;
	
	return 0;
}





