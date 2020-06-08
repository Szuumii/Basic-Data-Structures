#include <iostream>
#include "Sequence.h"
#include "shuffle.h"

int main()
{


	Sequence<int, int> entity;

	for (int i = 1; i <= 11; ++i)
	{
		entity.push_back(i, i);
	}

	entity.cleverPrint();
	

	std::cout << "-------Done!------------" << '\n';
	std::cin.get();
}