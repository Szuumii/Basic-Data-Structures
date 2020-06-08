#include "Test.h"

Test::Test()
{

}

void Test::run_all_tests()
{
	void creation_test();
	void push_front_method_test();
	void push_back_method_test();
	void pop_front_method_test();
	void pop_back_method_test();
	void empty_method_test();
	void operator_equal_method_test();
	void element_access_method_test();
	void swap_method_test();
	void insert_after_method_test();
	void remove_after_method_test();
	void subsequence_method_test();

	std::cout << errors.size() << "Erorrs: ";

	for (auto it : errors)
	{
		std::cout << it << ' ';
	}

}

void Test::creation_test()
{
	Sequence<int, int> entity;
    const Sequence<int, int> instance;
}

void Test::push_front_method_test()
{
	Sequence<int, std::string> entity;
	try
	{
		entity.push_front(1, "One");
		entity.push_front(2, "Two");
		entity.push_front(3, "Three");
		entity.push_front(4, "Four");
		entity.present_sequece(std::cout);
	}
	catch (SequenceException& e)
	{
		errors.push_back(e.get_message());
	}
}

void Test::push_back_method_test()
{
	Sequence<int, std::string> entity;
	try
	{
		entity.push_back(1, "One");
		entity.push_back(2, "Two");
		entity.push_back(3, "Three");
		entity.push_back(4, "Four");
		entity.present_sequece(std::cout);
	}
	catch (SequenceException& e)
	{
		errors.push_back(e.get_message());
	}
}

void Test::pop_front_method_test()
{
	Sequence<int, std::string> entity;
	try
	{
		entity.push_back(1, "One");
		entity.push_back(2, "Two");
		entity.push_back(3, "Three");
		entity.push_back(4, "Four");

		entity.pop_front();
		entity.pop_front();

		entity.present_sequece(std::cout);
		std::cout << entity.size() << '\n';

		entity.pop_front();
		entity.pop_front();
		entity.pop_front();
		entity.pop_front();
	}
	catch (SequenceException& e)
	{
		errors.push_back(e.get_message());
	}

	try
	{
		Sequence<int, std::string> entity;
		entity.pop_front();
	}
	catch (SequenceException& e)
	{
		errors.push_back(e.get_message());
	}
}

void Test::pop_back_method_test()
{
	Sequence<int, std::string> entity;
	try
	{
		entity.push_front(1, "One");
		entity.push_front(2, "Two");
		entity.push_front(3, "Three");
		entity.push_front(4, "Four");

		entity.pop_back();
		entity.pop_back();

		entity.present_sequece(std::cout);
		std::cout << entity.size() << '\n';

		entity.pop_back();
		entity.pop_back();
		entity.pop_back();
		entity.pop_back();
	}
	catch (SequenceException& e)
	{
		errors.push_back(e.get_message());
	}

	try
	{
		Sequence<int, std::string> entity;
		entity.pop_back();
	}
	catch (SequenceException& e)
	{
		errors.push_back(e.get_message());
	}
}

void Test::empty_method_test()
{
	Sequence<int, std::string> entity;

	entity.push_back(1, "First");

	if (!entity.empty())
	{
		std::cerr << "Error in empty method" << '\n';
	}
}

void Test::operator_equal_method_test()
{
	std::cout << "---Start of operator= and copy constructor test---" << '\n';
	Sequence<int, std::string> entity;
	Sequence<int, std::string> instance;

	try
	{
		instance.push_back(1, "One");
		instance.push_back(2, "Two");
		instance.push_back(2, "Three");

		entity = instance;

		entity.present_sequece(std::cout);

		assert(entity == instance);
	}
	catch (SequenceException& e)
	{
		errors.push_back(e.get_message());
	}

	try
	{
		entity.push_back(4, "Four");
		entity.push_back(5, "Five");

		Sequence<int, std::string> existance(entity);

		existance.present_sequece(std::cout);
	}
	catch (SequenceException& e)
	{
		errors.push_back(e.get_message());
	}
}

void Test::element_access_method_test()
{
	Sequence<int, std::string> entity;
	Sequence<int, std::string> instance;
	try
	{
		entity.push_back(1, "One");
		entity.push_front(2, "Two");

		entity.present_sequece(std::cout);

		instance.back();

		assert("Two" == entity.front());
		assert("One" == entity.back());
	}
	catch (SequenceException& e)
	{
		errors.push_back(e.get_message());
	}
}

void Test::swap_method_test()
{
	Sequence<int, std::string> entity;
	Sequence<int, std::string> instance;
	Sequence<int, std::string> existance;
	try
	{
		entity.push_back(1, "One");
		entity.push_back(2, "Two");

		existance = entity;

		instance.push_back(3, "Three");
		instance.push_back(4, "Four");

		existance.present_sequece(std::cout);

		existance.swap(instance);

		existance.present_sequece(std::cout);
	}
	catch (SequenceException& e)
	{
		errors.push_back(e.get_message());
	}
}

void Test::insert_after_method_test()
{
	Sequence<int, std::string> entity;
	Sequence<int, std::string> instance;

	try
	{
		entity.push_back(1, "One");
		entity.push_back(3, "Three");
		entity.push_back(4, "Four");
		entity.push_back(6, "Six");

		entity.insert_after(1, 2, "Two");
		entity.insert_after(4, 5, "Five");
		entity.insert_after(6, 7, "Seven");

		entity.present_sequece(std::cout);
	}
	catch (SequenceException& e)
	{
		errors.push_back(e.get_message());
	}

	try
	{
		instance.push_back(1, "One");
		instance.push_back(3, "Three");

		instance.insert_after(4, 5, "Five");

		instance.present_sequece(std::cout);
	}
	catch (SequenceException& e)
	{
		errors.push_back(e.get_message());
	}
}

void Test::remove_after_method_test()
{
	Sequence<int, std::string> entity;
	try
	{
		entity.push_back(1, "One");
		entity.push_back(2, "Two");
		entity.push_back(3, "Three");
		entity.push_back(4, "Four");

		entity.remove_from_sequence(4);
		entity.present_sequece(std::cout);
	}
	catch (SequenceException& e)
	{
		errors.push_back(e.get_message());
	}
}

void Test::subsequence_method_test()
{
	Sequence<int, std::string> entity;
	Sequence<int, std::string> instance;

	try
	{
		entity.push_back(1, "One");
		entity.push_back(2, "Two");
		entity.push_back(3, "Three");
		entity.push_back(4, "Four");

		entity.present_sequece(std::cout);

		instance = entity.subsequence(1, 2);

		instance.present_sequece(std::cout);
	}
	catch (SequenceException& e)
	{
		errors.push_back(e.get_message());
	}
}