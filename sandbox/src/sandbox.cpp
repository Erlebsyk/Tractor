#include "sandbox.hpp"

#include <iostream>

#include <tractor.hpp>

int main()
{
	std::cout << "We are in sandbox!" << std::endl;
	tractor();
	std::cout << "End of sandbox!" << std::endl;

	return 0;
}