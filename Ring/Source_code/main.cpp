#include "ring.h"
#include "produce.h"

int main()
{
	//creation test
	{
		Ring<int, int> ring1;
		const Ring<int, int> ring2;
	}
	//insert test
	{
		std::cout << "------------------Start of insert Test------------" << '\n';
		Ring<int, std::string> entity;
		try
		{

			entity.insert(1, "One");
			entity.insert(2, "Two");
			entity.insert(3, "Three");
			entity.insert(4, "Four");

			entity.present_ring(std::cout);
			
		}
		catch (RingException& e)
		{
			std::cout << e.get_message() << '\n';
		}
		std::cout << "------------------End of insert Test------------" << '\n';
	}
	//copy constructor and assingment operator test
	{
		std::cout << "------------------Start of operator= and copy constructor Test------------" << '\n';
		Ring<int, std::string> entity;
		Ring<int, std::string> instance;
		try
		{
			entity.insert(1, "One");
			entity.insert(2, "Two");
			entity.insert(3, "Three");
			entity.insert(4, "Four");

			instance = entity;

			if (instance == entity)
				throw RingException("Operator== test::pass");

			instance.insert(5,"Five");
			instance.insert(6,"Six");

			Ring<int, std::string> creation(instance);

			if (creation.size() != 6)
				throw RingException("Copy constructor test::failed");


		}
		catch (RingException& e)
		{
			std::cout << e.get_message() << '\n';
		}
		std::cout << "------------------Start of operator= and copy constructor Test------------" << '\n';
		
	}
	//key_occurance method test
	{
		std::cout << "------------------Start of key_occurance Test------------" << '\n';
		Ring<int, std::string> entity;
		try
		{
			entity.insert(1, "One");
			entity.insert(1, "Two");
			entity.insert(1, "Three");
			entity.insert(1, "Four");

			if (entity.key_occurance(1) != 4)
				throw RingException("Key_occurance::fail");

			if(entity.key_occurance(1) != 0)
				throw RingException("Key_occurance::pass");
		}
		catch (RingException& e)
		{
			std::cout << e.get_message() << '\n';
		}
		std::cout << "------------------End of how_many Test------------" << '\n';
	}
	//merge method and operator+ test
	{
		std::cout << "------------------Start of merge Test------------" << '\n';
		Ring<int, std::string> entity;
		Ring<int, std::string> instance;
		Ring <int, std::string> creation;
		Ring <int, std::string> something;
		try
		{
			entity.insert(2, "Two");
			entity.insert(3, "Three");
			entity.insert(4, "Four");
			instance.insert(1, "One");

			creation.insert(2, "Two");
			creation.insert(3, "Three");
			creation.insert(4, "Four");
			something.insert(1, "One");

			instance.merge(entity);

			something += creation;

			if (instance != something)
				throw RingException("Operator+= test::failed");

			//create other one using += and compare
		}
		catch (RingException& e)
		{
			std::cout << e.get_message() << '\n';
		}

		std::cout << "------------------End of merge Test------------" << '\n';
	}
	//remove method test
	{
		std::cout << "------------------Start of remove Test------------" << '\n';
		Ring<int, std::string> entity;
		try
		{
			entity.insert(1, "One");
			entity.insert(2, "Two");
			entity.insert(3, "Three");
			entity.insert(4, "Four");
			entity.insert(5, "Five");
			

			entity.remove(2);

			entity.insert(4, "Six");
			
			entity.remove(4);

			entity.remove(5);

			if (entity.size() != 2)
			 throw RingException("Remove method test::pass");

		}
		catch (RingException& e)
		{
			std::cout << e.get_message() << '\n';
		}
		std::cout << "------------------End of remove Test------------" << '\n';
	}
	//swap method test
	{
		std::cout << "------------------Start of swap Test------------" << '\n';
		Ring<int, std::string> entity;
		Ring<int, std::string> instance;
		try
		{

			entity.insert(1, "One");
			entity.insert(2, "Two");
			entity.insert(3, "Three");
			entity.insert(4, "Four");

			entity.swap(instance);

			if (instance.size() != 4)
				throw RingException("Swap test::failed");

		}
		catch (RingException& e)
		{
			std::cout << e.get_message() << '\n';
		}
		std::cout << "------------------End of swap Test------------" << '\n';
	}
	//produce method test
	{
		std::cout << "------------------Start of produce Test------------" << '\n';
		Ring<int, std::string> entity;
		Ring<int, std::string> instance;
		try
		{
			
			entity.insert(1, "One");
			entity.insert(2, "Two");
			entity.insert(3, "Three");

			instance.insert(10,"Ten");
			instance.insert(20, "Twenty");
			instance.insert(30, "Thirty");
			instance.insert(40, "Fourty");
			

			Ring<int, std::string> creation = produce(entity, 3, 2, true, instance, -2, 3, false, 2, true);

			creation.present_ring(std::cout);

		}
		catch (RingException& e)
		{
			std::cout << e.get_message() << '\n';
		}
		std::cout << "------------------End of produce Test------------" << '\n';
	}
	std::cout << "------------------------Done!----------------" << '\n';
	std::cin.get();
}