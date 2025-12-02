// https://adventofcode.com/2025/day/1

#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <string>
//#define SAMPLE_INPUT

enum Direction
{
    LEFT,
    RIGHT,
    INVALID
};

struct Instruction
{
    Direction dir;
    int amount = 0;
};

class Dial
{
public:
    void ConsumeInstruction(const Instruction& instruction)
    {
        int modified_amount = instruction.amount % 100;
        if (instruction.dir == Direction::LEFT)
        {
            modified_amount *= -1;
        }

        value += modified_amount;
        if (value < 0)
        {
            value += 100;
        }
        else if (value >= 100)
        {
            value -= 100;
        }
    }

    int ConsumeInstruction2(const Instruction& instruction)
    {
        int dial_start = value;
        int num_zeroes = instruction.amount / 100;
        //if (num_zeroes > 0)
        //{
        //    std::cout << "hello";
        //}
        int modified_amount = instruction.amount % 100;
        if (instruction.dir == Direction::LEFT)
        {
            modified_amount *= -1;
        }

        value += modified_amount;
        if (value < 0)
        {
            value += 100;
            if (dial_start != 0)
            {
                num_zeroes++;
            }
        }
        else if (value >= 100)
        {
            value -= 100;
            if (dial_start != 0)
            {
                num_zeroes++;
            }
        }
        else if (dial_start != 0)
        {
            num_zeroes += value == 0 ? 1 : 0;
        }
        return num_zeroes;
    }

    int GetValue() const
    {
        return value;
    }

    void Reset()
    {
        value = 50;
    }
private:
    int value = 50;
};

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
    std::string line;
    std::regex pattern("([LR])(\\d+)");
    std::smatch match;

    std::vector<Instruction> instructions;
    while (std::getline(input_file, line))
    {
        if (std::regex_match(line, match, pattern))
        {
            char letter = match[1].str()[0];
            int number = std::stoi(match[2].str());
            instructions.emplace_back(Instruction{ letter == 'L' ? Direction::LEFT : Direction::RIGHT, number});
            //std::cout << "Letter: " << letter << " | Number: " << number << std::endl;
        }
    }
    
    int num_zeroes = 0;
    Dial dial;
    for (const Instruction instruction : instructions)
    {
        dial.ConsumeInstruction(instruction);
        num_zeroes += dial.GetValue() == 0 ? 1 : 0;
    }

    std::cout << num_zeroes << std::endl;

    dial.Reset();
    num_zeroes = 0;
    for (const Instruction instruction : instructions)
    {
        num_zeroes += dial.ConsumeInstruction2(instruction);
    }

    std::cout << num_zeroes << std::endl;
}
