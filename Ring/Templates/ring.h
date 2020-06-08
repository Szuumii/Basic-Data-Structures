#ifndef RING_H
#define RING_H

#include <iostream>
#include <memory>
#include "ringexception.h"

template<typename Key,typename Info>
class Ring
{
private:
	//private class members

	//Node definition
	struct Node
	{
		Key key;
		Info info;

		Node* next;
		Node* previous;

		Node(Key key, Info info) : key(key), info(info), next(nullptr), previous(nullptr) {}
		Node(Key key, Info info, Node* previous, Node* next) : key(key), info(info), previous(previous), next(next)	{}
	};


	Node* first;
	std::size_t length;

public:
	//public API

	//iterator definition
	class iterator
	{
		mutable Node* node_view;
	public:

		//constructors
		iterator(Node* temp) : node_view(temp) {}
		iterator(const iterator& source) noexcept
		{
			*this = source;
		}

		~iterator() = default;

		//opetators
		iterator& operator=(const iterator& source) noexcept
		{
			node_view = source.node_view;
			return *this;
		}
		iterator& operator++() const
		{
			node_view = node_view->next;
			return *this;
		}
		iterator operator++(int) const
		{
			iterator copy(node_view);
			node_view = node_view->next;

			return copy;
		}
		iterator& operator--() const
		{
			node_view = node_view->previous;
			return *this;
		}
		iterator operator--(int) const
		{
			iterator copy(node_view);
			node_view = node_view->previous;

			return copy;
		}
		std::pair<Key&, Info&> operator*()
		{
			return std::make_pair(std::ref(node_view->key), std::ref(node_view->info));
		}
		bool operator==(const iterator& source) const
		{
			return node_view == source.node_view;
		}
		bool operator!=(const iterator& source) const
		{
			return node_view != source.node_view;
		}

		iterator operator+(int x) const
		{
		    iterator temp(node_view);
			for (int i = 0; i < x; ++i)
			{
				temp.node_view = temp.node_view->next;
			}

			return temp;
		}
		iterator operator-(int x) const noexcept
		{
		    iterator temp(node_view);
			for (int i = 0; i < x; ++i)
			{
				temp.node_view = temp.node_view->previous;
			}
			return temp;
		}
		iterator& operator+=(int x)
		{
			*this = *this + x;

			return *this;
		}

		iterator& operator-=(int x)
		{
			*this = *this - x;

			return *this;
		}

		Key& get_key() noexcept
		{
			return node_view->key;
		}


		Info& get_info() noexcept
		{
			return node_view->info;
		}

	};


	//constructors
	Ring() : first(nullptr), length(0)
	{

	}
	Ring(const Ring<Key, Info>& source) : first(nullptr)
	{
		*this = source;
	}

	//destructor
	~Ring()
	{
		clear_ring();
	}



	//capacity
	bool empty() const
	{
		return first;
	}
	std::size_t size() const
	{
		return length;
	}

	//iterator
	iterator iter() const noexcept
	{
		return first ? iterator(first) : iterator(nullptr);
	}

	//operators
	Ring& operator=(const Ring<Key, Info>& source)
	{
		if (*this == source)
			return *this;

		this->clear_ring();

		Node* current = source.first;

		if (!current)
			return *this;

		do
		{
			this->insert(current->key, current->info);
			current = current->next;
		} while (current != source.first);

		return *this;
	}
	bool operator==(const Ring<Key, Info>& source) const noexcept
	{
		if (size() != source.size()) //size comparison in order to establish if sizes are diffrent
			return false;

		Node* left = first;
		Node* right = source.first;

		do
		{
			if (left->key != right->key || left->info != right->info)
				return false;

			left = left->next;
			right = right->next;

		} while (left != first);

		return true;

	}
	bool operator!=(const Ring<Key, Info>& source) const noexcept
	{
		return !(*this == source);
	}
	Ring<Key, Info> operator+(const Ring<Key, Info>& source)
	{
		this->merge(source);

		return *this;
	}
	Ring<Key, Info>& operator+=(const Ring<Key, Info>& source)
	{
		return *this = *this + source;
	}


	//methods
	/*
	method for adding a single node into the ring
	accepts key and info for a new key and adds it into the list
	if sth goes wrong throws a RingException with message
	*/
	void insert(const Key& new_key, const Info& new_info)
	{
		if (!empty())
		{
			first = new Node(new_key, new_info);

			if (first == nullptr)
				throw RingException("insert::failed to allocate memory");

			first->next = first;
			first->previous = first;

			length++;

			return;
		}
		else
		{
			Node* new_node = new Node(new_key, new_info, first->previous, first);

			if (new_node == nullptr)
				throw RingException("insert::failed to allocate memory");

			first->previous->next = new_node;
			first->previous = new_node;

			length++;

			return;

		}

		throw RingException("insert::failed to insert new node");

	}

	/*
	*/
	void insert_after()
	{

	}
	/*
	method that removes multiple amount of keys in the ring
	*/
	void remove(const Key& key)
	{
		std::size_t occurance = key_occurance(key);

		if (!occurance)
		{
			throw RingException("Remove::key not found");
			return;
		}


		while (occurance != 0)
		{
			Node* current = first;

			if (size() == 1 && current->key == key)
			{
				delete current;
				first = nullptr;
				length--;
			}
			else if (current->key == key)
			{
				Node* temp = current;

				first = current->next;
				current->previous->next = current->next;
				current->next->previous = current->previous;
				length--;


				delete temp;
			}
			else
			{
				do
				{
					if (current->key == key)
					{
						current->previous->next = current->next;
						current->next->previous = current->previous;
						length--;

						delete current;
						break;
					}
					current = current->next;
				} while (current != first);

			}


			occurance--;
		}
	}

	//method for clearing entire ring
	void clear_ring() noexcept
	{
		if (!empty())
			return;

		Node* current = first->next;

		do
		{
			Node* temp = current;
			current = current->next;
			delete temp;


		} while (current != first);

		delete first;

		first = nullptr;
		length = 0;
	}

	/*
	method for checking amount of given keys in the ring
	accepts key reference and returns size_t with amount of keys that are inside ring
	*/
	std::size_t key_occurance(const Key& key)
	{
		if (!empty())
			return false;

		std::size_t occurance = 0;

		Node* current = first;

		do
		{
			if (current->key == key)
				occurance++;

			current = current->next;
		} while (current != first);

		return occurance;
	}

	/*
	presents ring
	in arguments accepts an ostream if you want to print the list in some other ostream than cout
	*/
	void present_ring(std::ostream& os) noexcept
	{
		if (!empty())
			return;

		Node* current = first;

		do
		{
			os << current->key << ' ' << current->info << '\n';
			current = current->next;
		} while (current != first);

	}

	/*
	merges second list into the first one
	method created for operator+ implementation
	*/
	void merge(const Ring<Key, Info>& source)
	{
		if (!source.empty())
			throw RingException("Merge:: source is empty");

		Node* current = source.first;

		do
		{
			this->insert(current->key, current->info);
			current = current->next;
		} while (current != source.first);


	}

	/*
	swaps diffrent rings
	*/
	void swap(Ring<Key, Info>& source) noexcept
	{
		Ring<Key, Info> temp(*this);
		*this = source;
		source = temp;
	}

	void reverse_ring() noexcept
	{
		if (!empty())
			return;

		Node* current = first;
		Node* next = current->next;
		do
		{
			Node* previous = current->previous;
			current->previous = current->next;
			current->next = previous;

			current = next;
			next = current->next;

		} while (current != first);
	}
};

#endif // !RING_H

