#pragma once
#include <string>
#include <memory>

const int ALPHABET_SIZE = 26;
const int MAX_STRING_LENGTH = 100;
class Trie
{
public:
    struct TrieNode
    {
        TrieNode() : children(new std::shared_ptr<TrieNode>[ALPHABET_SIZE]) {}
        std::shared_ptr<std::shared_ptr<TrieNode>[]> children;
        bool isEndOfWord{false};
    };
    auto getNewNode() const -> std::shared_ptr<TrieNode>;
    auto insert(const std::string& key) -> void;
    auto search(const std::string& key) const -> bool;
    auto isEmpty(std::shared_ptr<TrieNode>& node) -> bool;
    auto remove(std::string key, int depth) -> std::shared_ptr<TrieNode>&;
    auto findMinPrefixes(std::shared_ptr<TrieNode>& root, char buf[], int ind, std::string& res) -> void;
    auto hasEndOfWord(std::shared_ptr<TrieNode>& node, int& count) -> void;

    auto getAutocomplete(const std::string& preffix, int& words_number, std::string* word_array) const -> void;

private:
    std::shared_ptr<TrieNode> _root{nullptr};
    auto remove(std::shared_ptr<TrieNode>& node, std::string key, int depth) -> std::shared_ptr<TrieNode>&;
    auto getAutocomplete_internal(std::shared_ptr<TrieNode>& node, std::string* words_array, char buf[], int index, int& word_number) const -> int;
};
