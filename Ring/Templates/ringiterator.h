#ifndef RINGITERATOR_H
#define RINGITERATOR_H

#include "ring.h"
#include <memory>

template<typename Key, typename Info>
class Ring<Key,Info>::iterator
{
	Node* node_view;
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
	iterator& operator--() const
	{
		node_view = node_view->previous;
	}
	std::make_pair<Key&, Info&> operator*()
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

	iterator& operator+(int x) const
	{
		for (int i = 0; i < x; ++i)
		{
			node_view = node_view->next;
		}

		return *this;
	}
	iterator& operator-(int x) const
	{
		for (int i = 0; i < x; ++i)
		{
			node_view = node_view->previous;
		}

		return *this;
	}
	iterator& operator+=(int x) const
	{
		*this = *this + x;

		return *this;
	}

	iterator& operator-=(int x) const
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
#endif // !RINGITERATOR_H

