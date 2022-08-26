/*--- Day 10: Syntax Scoring ---*/

#include "LineParser.h"

int main()
{
    std::ifstream file{ "input.txt" };
    if (!file.is_open()) { exit(-2); }
    try
    {
        BracketStack b{ 0 };
    }
    catch (const char* str) { std::cout << str << std::endl; }
    std::cout << "Hello World!\n";
}
