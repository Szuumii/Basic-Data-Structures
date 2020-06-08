#ifndef SHUFFLE_H
#define SHUFFLE_H

#include "Sequence.h"

bool check_shuffle_arguments(int start1, int len1, int start2, int len2) 
{
	return (start1 >= 0) && (len1 >= 0) && (start2 >= 0) && (len2 >= 0);
}

template<typename Key,typename Info>
Sequence<Key, Info>  shuffle(const Sequence<Key, Info>& s1, int start1, int len1, const Sequence<Key, Info>& s2, int start2, int len2, int count)
{
	Sequence<Key, Info> return_seq;

	if (!check_shuffle_arguments(start1, len1, start2, len2))
	{
		std::cout << "Wrong arguments" << '\n';
		return return_seq;
	}

	if (count <= 0)
		return return_seq;


	for (int i = 0; i <= count; ++i)
	{
		return_seq += s1.subsequence((start1 + i*len1), len1);
		return_seq += s2.subsequence((start2 + i*len2), len2);
	}

	return return_seq;



}
#endif // !SHUFFLE_H

