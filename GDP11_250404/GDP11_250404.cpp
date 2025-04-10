
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <windows.h>

#include "common.h"
#include "PartOne.h"
#include "PartTwo.h"


using namespace std;

int main()
{
    char keydown = '\0';
    do {
        system("cls");
        cout << "E[x]it\n"
            << endl
            << "[1] Name and Age " << endl
            << "[2] Metric Conversion " << endl
            << "[3] Average of ints " << endl
            << "[4] Largest and Smallest" << endl
            << endl
            << "[5] Highest Number" << endl
            << "[6] Vector int even'd odds" << endl
            << "[7] Reverse For Loop" << endl
            << "[8] Sq metreage" << endl;
        keydown = getch();

        if (keydown == '1')
        {
            NameAndAgeExercise();
        }
        if (keydown == '2')
        {
            MetricConversionExercise();
        }
        if (keydown == '3')
        {
            AverageOfIntsExercise();
        }
        if (keydown == '4')
        {
            LargestAndSmallestExercise();
        }

        if (keydown == '5')
        {
            HighestNumberExercise();
        }
        if (keydown == '6')
        {
            EvenedOddsExercise();
        }
        if (keydown == '7')
        {
            ReverseForLoopExercise();
        }
        if (keydown == '8')
        {
            SquareMeterageExercise();
        }
        
    } while (keydown != 'x' && keydown != 'X');
}
