#ifndef TEST_H
#define TEST_H

#include "Sequence.h"
#include "shuffle.h"
#include <vector>

class Test

{
private:

	std::vector<std::string> errors;

public:
	Test();

	void run_all_tests();

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

};


#endif // 

