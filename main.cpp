#include <iostream>
#include "MyVector.hpp"

///	Your welcome
using std::cout;
using std::endl;

//
int main()
{
	
	MyVector<int> test1;
	MyVector<std::string> test2;
	for (int i = 0; i < 5; i++) {
		test1.push_back(i);
	}
	test1.reserve(100);
	std::cout<< test1.capacity() << endl;
	std::cout<< test1.size() << endl;
	for (size_t i = 0; i < test1.size(); i++) {
		std::cout << test1.at(i);
	}
	
	return 0;
}
