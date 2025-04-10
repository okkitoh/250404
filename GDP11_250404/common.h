#ifndef __COMMON_H__
#define __COMMON_H__


#include <Windows.h>
#include <string>
#include <vector>

TCHAR getch();
void getIntsFromUser(std::vector<int>& in, char terminator);
void trim(std::string& s);
void swap(int& a, int& b);
int quicksort(std::vector<int>& tosort, int l, int r);

#endif // __COMMON_H__
