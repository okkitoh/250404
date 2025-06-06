#include "common.h"


#include <iostream>

namespace MyCommon
{
    int partition(std::vector<int>& tosort, int l, int r)
    {
        int pivot = tosort[r];
        int iter = l - 1; // keeps track of last swapped position
        for (int i = l; i <= r - 1; ++i) {
            if (tosort[i] <= pivot) {
                ++iter;
                swap(tosort[iter], tosort[i]);
            }
        }
        swap(tosort[iter + 1], tosort[r]);

        return iter + 1;
    }
}


TCHAR getch()
{
    DWORD mode, cc; // unsigned 32 bytes, flags for session
    HANDLE h = GetStdHandle(STD_INPUT_HANDLE); // stdin
    if (h == NULL) return 0;

    GetConsoleMode(h, &mode);
    SetConsoleMode(h, mode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT));
    TCHAR c = 0;
    ReadConsole(h, &c, 1, &cc, NULL);
    SetConsoleMode(h, mode);
    return c;
}
void getIntsFromUser(std::vector<int>& in, char terminator)
{
    in.clear();

    std::string input;
    char* token = NULL;
    do
    {
        std::getline(std::cin, input);
        trim(input);
        if (input.length())
        {
            char* ctx = NULL;
            int len = input.length();
            char* line = new char[len + 1];
            memcpy(line, &input[0], sizeof(char) * len);
            line[len] = '\0';

            token = strtok_s(line, " ", &ctx);
            while (token != NULL)
            {
                int a = atoi(token);
                if (terminator == '0' && a == 0)
                {
                    token = &terminator;
                    break;
                }
                in.push_back(a);
                token = strtok_s(nullptr, " ", &ctx);
            }
        }
    } while (token == NULL && terminator != '\n');
}
void trim(std::string& s)
{
    if (s.length() == 0) return;

    bool flipflop = false;
    for (int i = 0; i < s.length(); ++i)
    {
        if (flipflop)
        {
            if (isspace(s[i]))
            {
                flipflop = false;
                continue;
            }
        }
        else
        {
            if (!isspace(s[i]))
            {
                flipflop = true;
                continue;
            }
            s.erase(s.begin() + i);
            i--;
        }
    }
}
void swap(int& a, int& b)
{
    if (a == b) return;
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
}

int quicksort(std::vector<int>& tosort, int l, int r)
{
    if (l < r) {
        int it = MyCommon::partition(tosort, l, r);
        quicksort(tosort, l, it - 1);
        quicksort(tosort, it + 1, r);
    }
    return 0;
}