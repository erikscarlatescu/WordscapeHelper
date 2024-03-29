#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <algorithm>

int main()
{
    bool looping_levels = true;
    while (looping_levels)
    {
        std::cout << "Enter letters in the level: ";
        std::string chars;
        std::cin >> chars;

        std::ifstream file{"dictionary"};

        auto start = std::chrono::steady_clock::now();

        std::vector<std::string> relevant;
        std::string line;
        while (std::getline(file, line))
        {
            if (line.size() < 3)
                continue;

            bool word_valid = true;
            std::vector<char> chars_copy;
            for (char c : chars)
                chars_copy.push_back(c);

            for (char c : line)
            {
                auto index = std::find(chars_copy.begin(), chars_copy.end(), c);
                if (index != chars_copy.end())
                    chars_copy.erase(index);
                else
                    word_valid = false;
            }
            if (word_valid)
                relevant.push_back(line);
        }

        auto end = std::chrono::steady_clock::now();
        auto time_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        std::cout << time_elapsed << " milliseconds elapsed to traverse dictionary" << std::endl;

        bool looping_template = true;
        while (looping_template)
        {
            std::cout << '\n' << "Enter template of word (Q to quit or L to enter new level): ";
            std::string temp;
            std::cin >> temp;

            if (temp == "Q")
            {
                looping_template = false;
                looping_levels = false;
            }
            else if (temp == "L")
            {
                looping_template = false;
            }
            else
            {
                std::cout << "Relevant words are: " << std::endl;
                for (auto s : relevant)
                {
                    if (s.size() != temp.size())
                        continue;

                    bool rel = true;
                    for (int i = 0; i < s.size(); i++)
                    {
                        if (temp[i] != '-' && temp[i] != s[i])
                            rel = false;
                    }

                    if (rel)
                        std::cout << s << std::endl;
                }
            }
        }
    }
    return 0;
}