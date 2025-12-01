// https://adventofcode.com/2025/day/1

#include <iostream>
#include <fstream>
#define SAMPLE_INPUT

int main()
{
#ifdef SAMPLE_INPUT
    std::ifstream input_file("sample_input.txt");
#else
    std::ifstream input_file("input.txt");
#endif
    if (!input_file)
    {
        std::cerr << "Cannot open file.";
        return 1;
    }
}
