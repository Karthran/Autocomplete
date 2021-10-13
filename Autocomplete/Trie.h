#pragma once
#include <string>
#include <memory>

const int ALPHABET_SIZE = 26;
const int MAX_WORD_LENGTH = 100;
class Trie
{
public:
    struct TrieNode
    {
        TrieNode* children[ALPHABET_SIZE]{};
        bool isEndOfWord{false};
    };
    auto getNewNode() const -> TrieNode*;
    auto insert(const std::string& key) -> void;
    auto search(const std::string& key) const -> bool;
    auto isEmpty(TrieNode* node) -> bool;
    auto remove(std::string key, int depth) -> TrieNode*;
    auto findMinPrefixes(TrieNode* root, char buf[], int ind, std::string& res) -> void;
    auto hasEndOfWord(TrieNode* node, int& count) -> void;

    auto getAutocomplete(const std::string& preffix, int& word_number, std::string* word_array)const -> void;

private:
    TrieNode* _root{nullptr};
    auto remove(TrieNode* node, std::string key, int depth) -> TrieNode*;
    auto getAutocomplete_internal(TrieNode* node, std::string* word_array, char buf[], int index, int& word_number) const -> int;
};
