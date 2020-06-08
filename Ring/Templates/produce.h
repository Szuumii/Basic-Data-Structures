#ifndef PRODUCE_H
#define PRODUCE_H

#include "ring.h"
#include <math.h>


template<typename Key,typename Info>
Ring<Key, Info> produce(const Ring<Key, Info>& r1, int start1, int steps1, bool dir1, const Ring<Key, Info>& r2, int start2, int steps2, bool dir2, int mm, bool dir_out)
{
	Ring<Key, Info> retv;

	if (mm < 0)
		throw RingException("Produce:: wrong iterations number!");

	if (steps2 < 0 || steps1 < 0)
		throw RingException("Produce:: wrong steps number! ");

	if (!r1.empty() || !r2.empty())
		throw RingException("Produce::empty ring!");

	//declaring operators to indicate first
	typename Ring<Key, Info>::iterator iter1 = r1.iter();
	typename Ring<Key, Info>::iterator iter2 = r2.iter();

	//setting iterators on proper places
	if(start1 < 0)
		iter1 -= std::abs(start1);
	else
		iter1 += start1;


	if(start2 < 0)
		iter2 -= std::abs(start2);
	else
		iter2 += start2;



	for (int i = 0; i < mm; ++i)
	{
		for (int j = 0; j < steps1; ++j)
		{
			std::pair<Key, Info> value = *iter1;
			retv.insert(value.first,value.second);
			dir1 ? iter1++ : iter1--;
		}

		for (int j = 0; j < steps2; ++j)
		{
			std::pair<Key, Info> value = *iter2;
			retv.insert(value.first, value.second);
			dir2 ? iter2++ : iter2--;
		}
	}

	if (!dir_out)
		retv.reverse_ring();

	return retv;
}
#endif // !PRODUCE_H

