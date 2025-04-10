
#include "PartOne.h"

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <windows.h>
#include "common.h"


void NameAndAgeExercise()
{
    std::string input; // these are mutable arrays
    std::string input2;
    std::cout << "Enter name: ";
    std::getline(std::cin, input);

    int result = -1;
    std::cout << "Enter Age: ";
    while (!(result > 0))
    {
        std::getline(std::cin, input2);
        result = atoi(input2.c_str());
        if (!(result > 0))
        {
            std::cout << "Not a valid age. Enter another: " << std::endl;
        }
    }
    std::cout << "\nHi, " << input << "of age " << result << std::endl;
    std::cout << "\nEOF :: Press any key to continue" << std::endl;
    getch(); // result output pause, eat input buffer
}
void MetricConversionExercise()
{
    std::string input;
    int celcius = 0;
    float pounds = 0.f;
    double dollars = 0.0;
    std::cout << "Enter value in celsius: ";
    std::getline(std::cin, input);
    celcius = atoi(input.c_str());
    printf("%d C => %f F\n", celcius, 32.f + (9.f / 5.f * celcius));
    printf("\nEnter value in pounds: ");
    std::getline(std::cin, input);
    pounds = atof(input.c_str());
    printf("%f lb => %f kg\n", pounds, pounds / 0.4535924f);
    printf("\nEnter value in USD: $");
    std::getline(std::cin, input);
    dollars = atof(input.c_str());
    printf("Conversion rate 1 $ = 0.91 €\n%f $ => %f €\n", dollars, dollars * 0.91);

    std::cout << "\nEOF :: Press any key to continue" << std::endl;
    getch(); // result output pause, eat input buffer
}
void AverageOfIntsExercise()
{
    std::string input;
    printf("\nprint sequence of numbers separated by a space e.g. 1 1 2 3 5:\nYour numbers: ");
    std::getline(std::cin, input);

    if (!input.length()) {
        printf("Average: 0\n");
    }
    else
    {
        char* ctx = NULL;
        int len = input.length();
        char* line = new char[len + 1];
        int runningTotal = 0;

        memcpy(line, &input[0], sizeof(char) * len);
        line[len] = '\0';
        int tklen = 0;
        char* token = strtok_s(line, " ", &ctx);
        while (token != NULL) {
            int a = atoi(token);
            printf("%d ", a);
            if (a != 0) {
                runningTotal += a;
                tklen++;
            }
            token = strtok_s(nullptr, " ", &ctx);
        }
        float avg = 0.f;
        if (tklen != 0) {
            avg = (float)runningTotal / tklen;
        }
        printf("\nnums: %d, average: %.02f", tklen, avg);

        delete[] line;
        ctx = NULL;
        line = nullptr;
    }

    std::cout << "\nEOF :: Press any key to continue" << std::endl;
    getch(); // result output pause, eat input buffer
}
void LargestAndSmallestExercise()
{
    std::vector<int> numbers;
    printf("\nprint sequence of numbers separated by a space e.g. 1 1 2 3 5:\nYour numbers: ");
    getIntsFromUser(numbers, '\n');
    if (!numbers.size())
    {
        printf("Largest: NULL\n");
        printf("Smallest: NULL\n");
    }
    else
    {
        std::sort(numbers.begin(), numbers.end());

        //quicksort(numbers, 0, tklen - 1);
        printf("Largest: %d\n", *(--numbers.end()));
        printf("Smallest: %d\n", numbers[0]);
    }
    std::cout << "\nEOF :: Press any key to continue" << std::endl;
    getch(); // result output pause, eat input buffer
}
