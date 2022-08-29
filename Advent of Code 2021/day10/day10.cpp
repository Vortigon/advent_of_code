/*--- Day 10: Syntax Scoring ---*/

#include "LineParser.h"

int main()
{
    std::ifstream file{ "input.txt" };
    if (!file.is_open()) { exit(-2); }

    LineParser parser;
    if (parser.getInput(file))
    {
        std::cout << "Syntax score: " << parser.getSyntaxScore() << 
            "\nAutocomplete score: " << parser.getAutoScore() << std::endl;
    }
}