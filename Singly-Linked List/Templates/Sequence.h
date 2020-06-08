#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <iostream>
#include "sequenceexception.h"
#include <assert.h>

template<typename Key,typename Info>
class Sequence
{

private:

	struct Node
	{
		Key key;
		Info info;
		Node* next;

		Node(Key key, Info value) :key(key), info(value), next(nullptr)
		{

		}
	};

	Node* head;
	std::size_t length;

public:

	//constructors
	Sequence() noexcept : head(nullptr), length(0)
	{

	}
	Sequence(const Sequence<Key, Info>& source) noexcept : head(nullptr)
	{
		*this = source;
	}
	//destructor
	~Sequence()
	{
		clear_sequence();
	}

	//operators
	bool operator==(const Sequence<Key, Info>& source) const noexcept
	{
		Node* left = head;
		Node* right = source.head;

		if (this->size() != source.size())
			return false;

		while (left)
		{
			if (left->key != right->key || left->info != right->info)
			{
				return false;
			}
			else
			{
				left = left->next;
				right = right->next;
			}


		}

		return true;
	}
	bool operator!=(const Sequence<Key, Info>& source) const noexcept
	{
		return !(*this == source);
	}

	Sequence<Key, Info>& operator=(const Sequence<Key, Info>& source)
	{
		if (this == &source)
			return *this;

		clear_sequence();

		Node* temp = source.head;

		while (temp)
		{
			push_back(temp->key, temp->info);
			temp = temp->next;
		}

		return *this;
	}
	Sequence<Key, Info> operator+(const Sequence<Key, Info>& source) const
	{
		return this->merge(source);
	}
	Sequence<Key, Info> operator+=(const Sequence<Key, Info>& source)
	{
		return *this = *this + source;
	}

	//capacity
	bool empty() const noexcept
	{
		return length;
	}
	std::size_t size() const noexcept
	{
		return length;
	}

	//element access
	Info& front()
	{
		if (!empty())
			throw SequenceException("Front::Sequence is empty");

		return head->info;
	}
	Info& back()
	{
		if (!empty())
			throw SequenceException("Back::Sequence is empty");

		Node* temp = head;
		while (temp->next)
		{
			temp = temp->next;
		}
		return temp->info;
	}

    //methods
    void push_front(const Key& key,const Info& value) 
    {
        if(!empty())
        {
            Node* new_node = new Node(key,value);

            if (new_node == nullptr)
             throw SequenceException("Push_front::Failed to insert new node in front");

			head = new_node;

        }
        else
        {
			Node* temp;
			Node* new_node = new Node(key, value);

			if (new_node == nullptr)
				throw SequenceException("Push_front::Failed to insert new node in back");

			temp = head;
			new_node->next = temp;
			head = new_node;
        }

		length++;

    } 
	void push_back(const Key& key, Info value) 
	{
		if (!empty())
		{
			Node* new_node = new Node(key, value);

			if (new_node == nullptr)
				throw SequenceException("Push_back::Failed to insert new node");

			head = new_node;

		}
		else
		{
			Node* temp;
			Node* new_node = new Node(key, value);

			if (new_node == nullptr)
				throw SequenceException("Push_back::Failed to insert new node");

			temp = head;
			while (temp->next)
			{
				temp = temp->next;

			}
			temp->next = new_node;
		}
		length++;

	}
    void pop_front() 
    {
		if (!head)
			throw SequenceException("Pop_fornt::List is empty");

		Node* temp;
		if (head->next == nullptr)
		{
			temp = head;
			head = nullptr;
			delete temp;
		}
		else
		{
			temp = head;
			head = head->next;
			delete temp;
		}
		length--;
    } 
	void pop_back() 
	{
		if (!head)
			throw SequenceException("Pop_back::List is empty");

		Node* temp = head;
		Node* current;
		if (head->next == nullptr)
		{
			head = nullptr;
			delete temp;
		}
		else
		{
			while (temp->next->next)
			{
				temp = temp->next;
			}
			current = temp->next;
			temp->next = nullptr;
			delete current;
		}
		length--;
	}
	void remove_from_sequence(const Key& key)
	{
		if (!empty())
			throw SequenceException("Remove from sequence::Sequence is empty");

		std::size_t key_occurance = key_ocurrance(key);

		if (!key_occurance)
			throw SequenceException("Remove from sequence::Entered key does not exist");

		Node* temp = head;
		Node* current;

		while (key_occurance)
		{
			if (temp->key == key)
			{
				pop_front();
			}
			else
			{
				while (temp->next)
				{
					if (temp->next->key == key && temp->next->next == nullptr)
					{
						pop_back();
					}
					else
					{
						if (temp->next->key == key)
						{
							current = temp->next;
							temp->next = temp->next->next;
							delete current;
							length--;
						}
					}
					
					temp = temp->next;
				}

			}

			key_occurance--;

		}
		
	}
	void insert_after(const Key& after_key, const Key& new_key,const Info& new_value) 
	{
		if (!empty())
			throw SequenceException("Insert_after::sequence is empty");

		Node* temp = head;
		
			while (temp)
			{
				if (temp->key == after_key)
				{
					Node* new_node = new Node(new_key, new_value);

					new_node->next = temp->next;

					temp->next = new_node;

					length++;

					return;
				}

				temp = temp->next;

			}

		throw SequenceException("Instert_after::key not found");

	}
	void swap(Sequence<Key,Info>& source)
	{
		Sequence<Key, Info> temp(*this);
		*this = source;
		source = temp;
	}
	void present_sequece(std::ostream& os)
	{
		Node* temp;
		temp = head;
		std::cout << "Sequence: ";
		while (temp)
		{
			os << temp->info << ' ';
			temp = temp->next;
		}
		std::cout << '\n';
	}
	void clear_sequence()
	{
		while (head != nullptr)
		{
			pop_front();
		}
		head = nullptr;
		length = 0;

	}

	void cleverPrint()
	{
		present_normal_order(head);
		present_reversed_order(head->next);
		std::cout << '\n';

	}

	void present_reversed_order(Node* current)
	{
		if (current->next != nullptr)
		{
			present_reversed_order(current->next->next);
			std::cout << current->info << ' ';
		}
	}

	void present_normal_order(Node* current)
	{
		if (current->next->next != nullptr)
		{
			std::cout << current->info << ' ';
			present_normal_order(current->next->next);
		}
	}
	Sequence<Key, Info> subsequence(int start, int length) const
	{

		if (start < 0 || length < 0 )
			throw SequenceException("subsequence::start or length wrong range");

		if (!empty())
			throw SequenceException("Subsequence::sequence is empty");


		//setting pointer for starting position
		Node* temp = head;

		for (int i = 0; i < start; ++i)
		{
			if (!temp)
				break;
			temp = temp->next;
		}

		Sequence<Key, Info> return_seq;

		for (int i = 0; i < length; ++i)
		{
			if (!temp)
				break;

			return_seq.push_back(temp->key, temp->info);
			temp = temp->next;
		}

		return return_seq;
		

	}
	Sequence<Key, Info> merge(const Sequence<Key, Info> seq) const
	{
		Sequence<Key, Info> return_seq(*this);

		Node* temp = seq.head;
		{
			while (temp)
			{
				return_seq.push_back(temp->key, temp->info);
				temp = temp->next;
			}
		}

		return return_seq;
	}


private:
	
	std::size_t key_ocurrance(const Key& key)
	{
		std::size_t occurance = 0;
		Node* temp = head;

		while (temp)
		{
			if (temp->key == key)
				occurance++;

			temp = temp->next;
		}

		return occurance;
	}

};

#endif //SEQUENCE_H 
