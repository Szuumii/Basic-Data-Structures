#include "dictionary.h"
#include <assert.h>

int main()
{
	//creation test
	{
		Dictionary<int, int> entity;
		const Dictionary<int, int> instance;
	}
	//insert method test
	{
		std::cout << '\n' << "-------------insert method test-----------" << '\n';
		try
		{
			Dictionary<int, int> entity;
			entity.insert(2, 2);
			entity.insert(3, 3);
			entity.insert(4, 4);

			entity.print_inorder(std::cout);

			std::cout << '\n';

			entity.insert(1, 1);

			entity.print_inorder(std::cout);
		}
		catch (DictionaryException& e)
		{
			e.get_message();
		}
		
	}
	//clear method test
	{
		std::cout << '\n' << "-------------clear method test-----------" << '\n';
		try
		{
			Dictionary<int, int> entity;
			entity.insert(2, 2);
			entity.insert(3, 3);
			entity.insert(4, 4);
			entity.insert(1, 1);

			entity.print_inorder(std::cout);

			entity.clear();

			std::cout << '\n';

			entity.print_inorder(std::cout);
		}
		catch (DictionaryException& e)
		{
			e.get_message();
		}
	}
	//remove method test
	{
		std::cout << '\n' << "-------------remove method test-----------" << '\n';
		try
		{
			Dictionary<int, int> entity;
			entity.insert(2, 2);
			entity.insert(3, 3);
			entity.insert(4, 4);
			entity.insert(1, 1);
			entity.insert(5, 5);

			entity.print_graph(std::cout);

			std::cout << "---------------------------------"<< '\n';

			entity.remove(4);

			entity.print_graph(std::cout);

			std::cout << "---------------------------------" << '\n';

			assert(entity.height() == 2);

			entity.remove(3);

			entity.print_graph(std::cout);

			std::cout << "---------------------------------" << '\n';

			assert(entity.height() == 1);

		}
		catch (DictionaryException& e)
		{
			e.get_message();
		}

	}
	//copy constructor and operator= test
	{
		std::cout << '\n' << "---------Copy constructor and operator= method test-----------" << '\n';
		try
		{
			Dictionary<int, int> entity;
			
			entity.insert(1, 1);
			entity.insert(2, 2);
			entity.insert(3, 3);
			entity.insert(4, 4);

			std::cout << "Entity: ";

			entity.print_inorder(std::cout);

			std::cout << '\n';

			Dictionary<int, int> instance;

			instance = entity;

			std::cout << "Instance: ";

			instance.print_inorder(std::cout);

			std::cout << '\n';

			instance.insert(7, 7);
			instance.insert(9, 9);

			Dictionary<int, int> creation(instance);

			std::cout << "Creation: ";

			creation.print_inorder(std::cout);

			std::cout << '\n';
		}
		catch (DictionaryException& e)
		{
			e.get_message();
		}
	}
	//get_max and get_min method test
	{
		std::cout << '\n' << "-------------get max/min method test-----------" << '\n';
		try
		{
			Dictionary<int, int> entity;
			Dictionary<int, int> instance;
			entity.insert(2, 2);
			entity.insert(3, 3);
			entity.insert(4, 4);
			entity.insert(1, 1);
			entity.insert(5, 5);
			
			instance.insert(1, 1);
			instance.insert(5, 5);

			assert(entity.get_max() == instance.get_max());
			assert(entity.get_min() == instance.get_min());
		}
		catch (DictionaryException& e)
		{
			e.get_message();
		}
	}
	//clear method test
	{
		std::cout << '\n' << "-------------clear method test-----------" << '\n';
		try
		{
			Dictionary<int, int> entity;
			entity.insert(2, 2);
			entity.insert(3, 3);
			entity.insert(4, 4);
			entity.insert(1, 1);
			entity.insert(5, 5);

			entity.print_inorder(std::cout);

			std::cout << '\n';

			entity.clear();

			assert(entity.is_empty());

		}
		catch (DictionaryException& e)
		{
			e.get_message();
		}
	}
	std::cout << "-------------Done!-----------------" << '\n';
	std::cin.get();

	return 0;
}