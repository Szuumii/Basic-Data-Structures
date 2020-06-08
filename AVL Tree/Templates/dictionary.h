#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include <iomanip>

#include "dictionaryException.h"

template<typename Key, typename Info>
class Dictionary
{
private:

	struct Node
	{
		Key key;
		Info info;

		int bf;
		int height;
		Node* left;
		Node* right;
		Node* parent;

		Node(Key key, Info info) : key(key), info(info), left(nullptr), right(nullptr),parent(nullptr), bf(0), height(0) {}
		Node(Key key, Info info, int bf, int height, Node* left, Node* right) : key(key), info(info), bf(bf), height(height), left(left), right(right),parent(nullptr) {}
		Node(Key key, Info info, int bf, int height, Node* left, Node* right, Node* parent) : key(key), info(info), bf(bf), height(height), left(left), right(right), parent(parent) {}
	};

	Node* root;
public:

	//constructors and destructors
	Dictionary() noexcept : root(nullptr)
	{}

	Dictionary(const Dictionary<Key, Info>& source)
	{
		root = copy(source.root);
	}

	~Dictionary()
	{
		clear(root);
	}

	//iterator
	class AVLIterator 
	{
		Node* it;
public:

    AVLIterator() :  it(nullptr){ }
	AVLIterator(Node* start): it(start) {}
	AVLIterator(const AVLIterator& source) 
	{
		it = source.it; 
	}
	~AVLIterator()
	{

	}

	AVLIterator& operator=(const AVLIterator& source)
	{
		if (*this == source)
			return *this;

		it = source.it;

		return *this;
	}

	AVLIterator begin()
	{
		if (it != nullptr)
		{
			Node* ret = it;
			while (ret->left != nullptr)
			{
				ret = ret->left;
			}
		}
		return AVLIterator(ret);
	}
	AVLIterator end()
	{
		return nullptr;
	}

	AVLIterator& operator++()
	{
		Node *parent;
		
		if (it == nullptr)
		{
			it = root;
			if (it == nullptr)
				return nullptr;

			while (it->left != nullptr)
			{
				it = it->left;
			}
		}
		else if (it->right != nullptr)
		{
			it = it->right;
			
			while (it->left != null)
			{
				it = it->left;
			}
		}
		else
		{
			p = it->parent;
			while (p != nullptr && it == p->right)
			{
				it = p;
				p = p->parent;
			}

			it = p;
		}

		return *this;
	}

	AVLIterator& operator--()
	{
		Node *parent;

		if (it == nullptr)
		{
			it = root;
			if (it == nullptr)
				return nullptr;

			while (it->right != nullptr)
			{
				it = it->right;
			}
		}
		else if (it->left != nullptr)
		{
			it = it->left;

			while (it->right != null)
			{
				it = it->right;
			}
		}
		else
		{
			p = it->parent;
			while (p != nullptr && it == p->left)
			{
				it = p;
				p = p->parent;
			}

			it = p;
		}

		return *this;
	}

	AVLIterator operator+(int length) 
	{
		Node* ret = it;
		if (length > 0)
		{
			for (int i = 0; ret && ret->left && ret < length; i++)
				ret = ret->left;
		}			

		return AVLIterator(ret);
	}

	AVLIterator operator-(int length)
	{
		Node* ret = it;
		if (length > 0)
		{
			for (int i = 0; ret && ret->left && ret < length; i++)
				ret = ret->right;
		}

		return AVLIterator(ret);
	}

	bool operator==(const AVLIterator& source)
	{
		return it == source.it;
	}

	bool operator!=(const AVLIterator& source)
	{
		return it != source.it;
	}

	Node& operator*()
	{
		return *it;
	}
	
	Key get_key()
	{
		return it->key;
	}
	Info get_info()
	{
		return it->info;
	}
};

	//operators
	Dictionary<Key,Info>& operator=(const Dictionary<Key,Info>& source)
	{
		clear();
		root = copy(source.root);
		return *this;
	}
	
	//capacity
	bool is_empty() const noexcept
	{
		return root == nullptr;
	}

	int height() const noexcept
	{
		return root ? root->height : 0;
	}

	//element access
	Key& get_max()
	{
		return get_max(root);
	}
	const Key& get_max() const
	{
		return get_max(root);
	}
	Key& get_min()
	{
		return get_min(root);
	}
	const Key& get_min() const
	{
		return get_min(root);
	}
	Info& get_into(const Key& key)
	{
		return get_node(key, root)->info;
	}
	const Info& get_info(const Key& key) const
	{
		return get_node(key, root)->info;
	}

	//modifiers
	// inserts a node
	void insert(const Key& key, const Info& info)
	{
		if (exists(key, root))
			throw DictionaryException("Insert::key already exists");

		root = insert(key, info, root);
	}
	//Clears entire tree
	void clear()
	{
		clear(root);
		root = nullptr;
	}
	//removes a node with a given key
	void remove(const Key& key)
	{
		if (!exists(key,root))
			throw DictionaryException("Remove:: key doesn't exist");

		root = remove(key, root);
	}

	//public printing functions
	void print_graph(std::ostream& os) const
	{
		graph(os, 0, root);
	}
	void print_inorder(std::ostream& os) const
	{
		inorder(os, root);
	}
	void print_preorder(std::ostream& os) const
	{
		preorder(os, root);
	}
	void print_postorder(std::ostream& os) const
	{
		postorder(os, root);
	}
	

	//public operations
	bool contain(const Key& key) const
	{
		return contain(key, root);
	}

private:

	//element access 
	Key & get_max(Node* start) const
	{
		if (!start->right)
			return start->key;

		return get_max(start->right);
	}
	Key& get_min(Node* start) const
	{
		if (!start->left)
			return start->key;

		return get_min(start->left);
	}
	Node* get_node(const Key& key, Node* start) const
	{
		if (!start)
			throw DictionaryException("GetP_node:: given key doesn't represent any node");

		if (key > start->key)
			return get_node(key, start->right);
		else if (key > start->key)
			return get_node(key, start->left);

		return start;
	}

	// modifiers
	Node* insert(const Key& key, const Info& info, Node* start)
	{
		if (!start)
			return new Node(key, info, 0, 0, nullptr, nullptr,start);

		if (key > start->key)
			start->right = insert(key, info, start->right);
		else if (key < start->key)
			start->left = insert(key, info, start->left);

		update(start);
		return balance(start);
	}
	void clear(Node* start)
	{
		if (!start)
			return;

		clear(start->left);
		clear(start->right);
		delete start;
	}
	Node* remove(const Key& key, Node* start)
	{
		if (!start)
			return nullptr;

		if (key < start->key)
			start->left = remove(key, start->left);
		else if (key > start->key)
			start->right = remove(key, start->right);
		else
		{
			if (!start->left)
				return start->right;
			else if (!start->right)
				return start->left;
			else
			{
				if (start->left->height > start->right->height)
				{
					Node *replacement = get_node(get_max(start->left), start->left);
					start->info = replacement->info;
					start->key = replacement->key;

					start->left = remove(replacement->key, start->left);
					delete replacement;
				}
				else
				{
					Node *replacement = get_node(get_max(start->right), start->right);
					start->info = replacement->info;
					start->key = replacement->key;

					start->right = remove(replacement->key, start->right);
					delete replacement;
				}
			}
		}

		update(start);
		return balance(start);
	}

	//rotations and updating
	Node* llrotation(Node* node) noexcept
	{
		return rrotation(node);
	}
	Node* lrrotation(Node* node) noexcept
	{
		node->left = lrotation(node->left);
		return rrotation(node);
	}
	Node* rrrotation(Node* node) noexcept
	{
		return lrotation(node);
	}
	Node* rlrotation(Node* node) noexcept
	{
		node->right = rrotation(node->right);
		return lrotation(node);
	}
	Node* lrotation(Node* node) noexcept
	{
		Node* new_node = node->right;
		node->right = new_node->left;
		new_node->left = node;
		new_node->parent = node;
		update(node);
		update(new_node);

		return new_node;
	}
	Node* rrotation(Node* node) noexcept
	{
		Node* new_node = node->left;
		node->left = new_node->right;
		new_node->right = node;
		new_node->parent = node;
		update(node);
		update(new_node);

		return new_node;
	}

	void update(Node* node) noexcept
	{
		int left_height = node->left ? node->left->height : -1;
		int right_height = node->right ? node->right->height : -1;

		node->height = left_height > right_height ? 1 + left_height : 1 + right_height;
		node->bf = right_height - left_height;
	}
	Node* balance(Node* node) noexcept
	{
		if (node->bf < -1)
		{
			if (node->left->bf <= 0)
				return llrotation(node);
			else
				return lrrotation(node);
		}
		else if (node->bf > 1)
		{
			if (node->right->bf >= 0)
				return rrrotation(node);
			else
				return rlrotation(node);
		}

		return node;
	}
	
	//private printing functions
	void graph(std::ostream& os, int  width, Node* start) const
	{
		if (start)
		{
			if (start->right)
				graph(os, width + 8, start->right);
			if (width > 0)
				os << std::setw(width) << ' ';
			if (start->right)
				os << '\n' << std::setw(width) << ' ';

			os << '(' << start->key << ',' << start->info << ")\n";
			if (start->left)
			{
				os << std::setw(width) << ' ' << '\n';
				graph(os, width + 8, start->left);
			}
		}
	}

	void inorder(std::ostream& os, Node* start) const
	{
		if (start)
		{
			inorder(os, start->left);
			os << start->info << ' ';
			inorder(os, start->right);
		}
	}

	void preorder(std::ostream& os, Node* start) const
	{
		if (start)
		{
			os << start->info << ' ';
			preorder(os, start->left);
			preorder(os, start->right);
		}
	}

	void postorder(std::ostream& os, Node* start) const
	{
		if (start)
		{
			postorder(os, start->left);
			postorder(os, start->right);
			os << start->info << ' ';
		}
	}

	//operations
	bool exists(const Key& key, Node* start) const
	{
		if (!start)
			return false;

		if (key > start->key)
			return exists(key, start->right);
		else if (key < start->key)
			return exists(key, start->left);
		else
			return true;
	}

	Node* copy(Node* start)
	{
		Node* ret = nullptr;
		if (start)
		{
			ret = new Node(start->key, start->info, start->bf, start->height, nullptr, nullptr);
			ret->left = copy(start->left);
			ret->right = copy(start->right);
		}

		return ret;
	}
};

#endif // DICTIONARY_H

