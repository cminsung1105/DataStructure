
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

