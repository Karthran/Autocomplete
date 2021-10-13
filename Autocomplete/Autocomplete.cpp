
#include <iostream>
#include <conio.h>
#include <fstream>
#include <iomanip>

#include "Trie.h"

const int AUTOCOMPLETE_WORD_NUMBER = 7;

int main()
{
    Trie trie;

    std::string filename = "eng.txt";
    std::fstream fs;
    fs.open(filename, std::fstream::in);

    std::string word;
    if (!fs.is_open()) return 1;
    while (!fs.eof())
    {
        fs >> word;
        if (word.size() > 1) trie.insert(word);
    }
    fs.close();

    auto auto_word{new std::string[AUTOCOMPLETE_WORD_NUMBER]};

    std::string string;
    std::string current_word;
    char buf[2]{};

    for (auto i{0}; i < MAX_WORD_LENGTH; ++i)
    {
        system("cls");
        auto word_number{0};
        std::cout << "Press Ctrl + Character(for example Ctrl + A) for autocomplete." << std::endl;
        if (current_word.size())
        {
            word_number = AUTOCOMPLETE_WORD_NUMBER;

            trie.getAutocomplete(current_word, word_number, auto_word);

            for (auto i{0}; i < AUTOCOMPLETE_WORD_NUMBER; ++i)
            {
                auto dif{AUTOCOMPLETE_WORD_NUMBER - word_number};
                if (i < dif)
                    std::cout << std::endl;
                else
                    std::cout << std::setw(3) << char(i - dif + 65) << "." << current_word << auto_word[i - dif] << std::endl;
            }
        }
        else
        {
            for (auto i{0}; i < AUTOCOMPLETE_WORD_NUMBER; ++i)
            {
                std::cout << std::endl;
            }
        }
        std::cout << "Enter string (Press BackSpace for delete previous character):" << std::endl;
        std::cout << string << current_word;
        auto chr = _getch();
        buf[0] = chr;

        if (chr >= 1 && chr <= word_number)
        {
            current_word += auto_word[chr - 1];
            continue;
        }

        if (chr == '\b')
        {
            if (current_word.size())
                current_word.pop_back();

            else if (string.size())
            {
                string.pop_back();
                auto str_length{string.size()};
                while (str_length)
                {
                    char chr = string.back();
                    if (!(chr >= 'a' && chr <= 'z')) break;

                    current_word.push_back(chr);
                    string.pop_back();
                    --str_length;
                }
                std::reverse(current_word.begin(), current_word.end());
            }
            i -= 2;
            continue;
        }
        current_word += std::string(buf);

        if (!(chr >= 'a' && chr <= 'z') && !(chr >= 'A' && chr <= 'Z'))
        {
            string += current_word;
            current_word.clear();

            if (chr == '\r')
            {
                break;
            }
        }
    }

    std::cout << std::endl << string << std::endl;
}
