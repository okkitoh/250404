#include "PartTwo.h"

#include <iostream>
#include <algorithm>
#include "common.h"


void HighestNumberExercise()
{
	printf("\nGet largest number from five integers\n");
	std::vector<int> nums = std::vector<int>();
	std::vector<int> temp = std::vector<int>();
	while (nums.size() < 5)
	{
		printf("Enter an integer: ");
		getIntsFromUser(temp, '\n');
		while (temp.empty())
		{
			getIntsFromUser(temp, '\n');
		}
		nums.push_back(temp[0]);
		temp.clear();
	}

	std::sort(nums.begin(), nums.end());
	printf("highest number: %d\n", *(--nums.end()));
	std::cout << "\nEOF :: Press any key to continue" << std::endl;
	getch();
}

void EvenedOddsExercise()
{
	std::vector<int> nums = std::vector<int>();
	printf("\nMake odd indicies an even number\nEnter integer vals. Submit 0 to end\n");
	getIntsFromUser(nums, '0');
	printf("Even'd Odd Indicies: ");
	for (int i = 0; i < nums.size(); ++i)
	{
		if ((i + 1) % 2 == 0)
		{
			nums[i] *= 2;
		}
		printf("%d ", nums[i]);
	}
	std::cout << "\nEOF :: Press any key to continue" << std::endl;
	getch();
}

void ReverseForLoopExercise()
{
	std::vector<int> nums = { 1, 2, 3, 4, 5 };
	printf("\nReverse For Looping - ");
	std::vector<int>::iterator iter = nums.begin();
	while (iter != nums.end())
	{
		printf("%d ", *(iter)++);
	}
	printf("\nReversed: ");
	for (int i = nums.size(); i > 0; --i)
	{
		printf("%d ", nums[i -1]);
	}
	std::cout << "\nEOF :: Press any key to continue" << std::endl;
	getch();
}

void SquareMeterageExercise()
{
	printf("\nTotal square meter calculator.\n");
	std::vector<int> nums = std::vector<int>();
	std::vector<int> temp = std::vector<int>();
	bool isEven = true;
	while (true)
	{
		printf("Enter %s (0 to end):", (isEven ? "width" : "height"));
		isEven = (isEven + 1) % 2;
		getIntsFromUser(temp, '\n');
		while (temp.empty())
		{
			getIntsFromUser(temp, '\n');
		}
		if (temp[0] == 0)
		{
			if (nums.size() % 2 > 0)
				nums.pop_back();
			break;
		}
		nums.push_back(temp[0]);
		temp.clear();
	}
	// eh i guess auto is cool. not a fan of ambiguity
	for (auto a : nums) {
		printf("%d ", a);
	}
	int total = 0;
	for (int i = 0; i < nums.size(); i += 2)
	{
		total += nums[i] * nums[i + 1];
	}
	printf("\ntotal square meters: %d\n", total);

	std::cout << "\nEOF :: Press any key to continue" << std::endl;
	getch();
}
