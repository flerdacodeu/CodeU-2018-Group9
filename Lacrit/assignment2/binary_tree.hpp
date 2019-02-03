#include <vector>
#include <iostream>
template <class T>
class Btree;

template <class T>
struct Node
{
    private: 
		T data;
		Node *left; 
		Node *right;
		friend class Btree<T>;
	public: 
		T get_data() {return data;}
};

template <class T>
class Btree 
{
	void insert(T key, Node<T> **leaf)
	{
		if ((*leaf) == nullptr) 
		{
			(*leaf) = new Node<T>;
			(*leaf)->data = key; 
			(*leaf)->left = nullptr;
			(*leaf)->right = nullptr;
		}
		else 
		{
 			if ((*leaf)->left == nullptr) 
				insert(key, &((*leaf)->left));
			else 
				insert(key, &((*leaf)->right));
		}
	};
	void destroy_node(Node<T> *node)
	{
			if (node == nullptr)
				return;

			destroy_node(node->left);

			destroy_node(node->right);

			delete node;
	};
	bool print_ancestors(std::vector<T>& res, Node<T> *node, T key) 
	{
		if ( node == nullptr ) return false;
		if ( node->data == key ) 
		{
			res.clear();
			return true;
		} 


		if (print_ancestors(res, node->left, key) ||  print_ancestors(res, node->right, key))
		{
			res.push_back(node->data);
			return true;
		}
		return false;
	}
		
	Node<T> *root;

public: 
	Btree():
		root(nullptr)
	{}; 
	~Btree()
	{
		destroy_node(root);
	};
	void insert(T key)
	{
		insert(key, &root);
	};
	Node<T>* get_root() 
	{
		return root;
	};
	void print_ancestors(std::vector<T>& res, T key)
	{
		print_ancestors(res, root, key);
	};
 	Node<T> * least_common_ancestor(Node<T> *root, T val1, T val2)
    {
		// TODO: check if values are in the tree
	    if ( root == nullptr ) return nullptr;
        if ( root->data == val1 || root->data == val2 ) return root;

        Node<T> *left = least_common_ancestor(root->left, val1, val2);
        Node<T> *right = least_common_ancestor(root->right, val1, val2);

        if( left != nullptr && right != nullptr) return root;
        if( left != nullptr ) return left;
        else return right;

    };	
};

	
