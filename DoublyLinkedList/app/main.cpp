

#include "Queue.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <utility>

struct Customer
{
public:
	int waited_time = 0;

	int getTime()
	{
		return waited_time;
	}

};


int main()
{
	std::cout << "LOG" << std::endl;
	int time = 0;
	int length;
	int registerLength;
	int lineLength;
	int registerNum;
	std::string lineType;
	int currentTime;
	int customers;

	int lost = 0;
	int enteredLine = 0;
	int exitedLine = 0;
	int exitedRegister = 0;
	int inLine = 0;
	int inRegister = 0;

	std::cin >> length;
	std::cin >> registerLength;
	std::cin >> lineLength;
	std::cin >> lineType;

	std::vector<int> registers; 
	std::vector<std::pair<int, Queue<Customer>>> lines;

	for (int i = 0; i < registerLength; ++i)
	{
		std::cin >> registerNum;
		registers.push_back(registerNum); 
	}

	if (lineType == "S")
	{
		int line_number = 1;
		Queue<Customer> tempQueue;
		lines.push_back(std::pair(line_number, tempQueue));
	}
	else
	{
		for (int i = 0; i < registerLength; ++i)
		{
			int line_number = i+1;
			Queue<Customer> tempQueue;
			lines.push_back(std::pair(line_number, tempQueue));
		}	
	}

	std::cout << time << " start" << std::endl;

	while(time < length)
	{
		std::cin >> customers;
		std::cin >> currentTime;

		int min;

		for (int i = 0; i < customers; ++i)	//LLOOP THROUGH EACH CUSTOMER THAT ARRIVES TO THE SIMULATION
		{
			min = 0;
			for (int j = 1; j < lines.size(); ++j)
			{
				if (lines[j].second.size() < lines[min].second.size())
				{
					min = j;
				}
			}
			if (lines[min].second.size() >= lineLength)
			{
				++lost;
				std::cout << currentTime << " lost " << std::endl;
			}
			else
			{
				Customer new_customer;
				new_customer.waited_time = (lines[min].second.size()-1)*registers[min];
				++enteredLine;
				lines[min].second.enqueue(new_customer);
				std::cout << currentTime << " entered line " << lines[min].first 
					<< " length " << lines[min].second.size() << std::endl; 
			}
		}

		for (int k = 0; k < customers; ++k)
		{
			int waitTime;
			if (lines[k].second.size() != 0)
			{
					
				waitTime = (lines[k].second.size()-1) * registers[k];
				int lineNum = lines[k].first;
				lines[k].second.dequeue();
				++exitedLine;
				
				std::cout << currentTime << " exited line " << lineNum <<
					" length " << lines[k].first << " wait time " << waitTime
					 << std::endl;

				std::cout << currentTime << " entered register " << lineNum << 
					std::endl;				

			}

		}

		++time;
	}

	std::cout << std::endl;
	std::cout << "STATS" << std::endl;
	std::cout << "Entered Line" << '\t' << ": " << enteredLine << std::endl;
	std::cout << "Exited Line" << '\t' << ": " << exitedLine << std::endl;
	std::cout << "Exited Register" << '\t' << ": " << exitedRegister << std::endl;
	std::cout << "Avg Wait Time" << '\t' << ": " << 0 << std::endl;
	std::cout << "Left In Line" << '\t' << ": " << inLine << std::endl;
	std::cout << "Left In Register" <<  ": " <<inRegister << std::endl;
	std::cout << "Lost" << '\t' << '\t' << ": " << lost << std::endl;


    return 0;
}

