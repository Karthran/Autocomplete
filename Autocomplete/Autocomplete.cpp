
#include <iostream>
#include <fstream>
#include <iomanip>

#include "Trie.h"

const int AUTOCOMPLETE_WORD_NUMBER = 7;

auto main() -> int
{
    Trie trie;

    std::string filename = "eng.txt";
    std::fstream fs;
    fs.open(filename, std::fstream::in);

    std::string word; // Loading dictionary
    if (!fs.is_open()) return 1;
    while (!fs.eof())
    {
        fs >> word;
        if (word.size() > 1) trie.insert(word);
    }
    fs.close();

    auto auto_words{new std::string[AUTOCOMPLETE_WORD_NUMBER]};

    std::string string;
    std::string current_word;
    char buf[2]{};

    for (auto i{0}; i < MAX_STRING_LENGTH; ++i) //Input string
    {
        system("cls");
        auto words_number{0};
        std::cout << "Press Ctrl + Character(for example Ctrl + A) for autocomplete." << std::endl;
        if (current_word.size()) // Check if autocomplete array empty
        {
            words_number = AUTOCOMPLETE_WORD_NUMBER;

            trie.getAutocomplete(current_word, words_number, auto_words);

            for (auto i{0}; i < AUTOCOMPLETE_WORD_NUMBER; ++i)
            {
                auto dif{AUTOCOMPLETE_WORD_NUMBER - words_number};
                if (i < dif)
                    std::cout << std::endl;
                else
                    std::cout << std::setw(3) << char(i - dif + 65) << "." << current_word << auto_words[i - dif] << std::endl; //65 ASCII code 'A'
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

        if (chr >= 1 && chr <= words_number) // Check pressed Ctrl + 
        {
            current_word += auto_words[chr - 1];
            continue;
        }

        if (chr == '\b') // Check pressed Backspace
        {
            if (current_word.size())
                current_word.pop_back();

            else if (string.size())
            {
                string.pop_back();
                auto str_length{string.size()};
                while (str_length) // copy last word from string to current_word in reverse order
                {
                    char chr = string.back();
                    if (!(chr >= 'a' && chr <= 'z')) break;

                    current_word.push_back(chr);
                    string.pop_back();
                    --str_length;
                }
                std::reverse(current_word.begin(), current_word.end()); // 
            }
            i -= 2; // correct index 
            continue;
        }
        current_word += std::string(buf);

        if (!(chr >= 'a' && chr <= 'z') && !(chr >= 'A' && chr <= 'Z')) // check inputs separator
        {
            string += current_word;
            current_word.clear();

            if (chr == '\r') // check pressed Enter
            {
                break;
            }
        }
    }
    system("cls");
    std::cout << "You enter the string: " << string << std::endl;
    return 0;
}
