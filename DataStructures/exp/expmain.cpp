// expmain.cpp
//
// ICS 46 Spring 2018
// Project #4: Set the Controls for the Heart of the Sun
//
// Do whatever you'd like here.  This is intended to allow you to experiment
// with your code, outside of the context of the broader program or Google
// Test.

#include <algorithm>
#include <iostream>
#include <string>

int main()
{
	std::string name = "Min Sung Cha";

	int sum= 0;
	for (auto letter : name)
	{
		sum += int(letter);
	}

	std::cout << sum << std::endl;

    return 0;
}

