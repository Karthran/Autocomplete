#include "Trie.h"

auto Trie::getNewNode() const -> std::shared_ptr<TrieNode>
{
    return std::make_shared<TrieNode>();
}

auto Trie::insert(const std::string& key) -> void
{
    if (!_root) _root = getNewNode();

    auto node{_root};
    int length = (int)key.size();

    for (int i = 0; i < length; i++)
    {
        // вычисляем индекс в алфите через смещение отнсительно первой буквы
        int index{0};
        if (key[i] >= 'a' && key[i] <= 'z')
            index = key[i] - 'a';
        else
            index = key[i] - 'A';
        // если указатель пустрой, т.е. детей с таким префиксом нет
        // создаем новый узел
        if (!node->children[index]) node->children[index] = getNewNode();

        node = node->children[index];
    }

    // помечаем последний узлел как лист, т.е. конец слова
    node->isEndOfWord = true;
}

auto Trie::search(const std::string& key) const -> bool
{
    if (!_root) return false;
    auto node{_root};
    int length = (int)key.size();

    for (int i = 0; i < length; i++)
    {
        int index{0};
        if (key[i] >= 'a' && key[i] <= 'z')
            index = key[i] - 'a';
        else
            index = key[i] - 'A';

        if (!node->children[index]) return false;

        node = node->children[index];
    }

    return (node != nullptr && node->isEndOfWord);
}
// Вохвращает true если root имеет лист, иначе false
auto Trie::isEmpty(std::shared_ptr<TrieNode>& node) -> bool
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (node->children[i]) return false;
    return true;
}

auto Trie::remove(std::string key, int depth) -> std::shared_ptr<TrieNode>&
{
    return remove(_root, key, depth);
}

// Рекурсивная функция удаления ключа из дерева
auto Trie::remove(std::shared_ptr<TrieNode>& node, std::string key, int depth) -> std::shared_ptr<TrieNode>&
{
    // Если дерево пустое
    if (!node) return node;

    // если дошли до конца ключа
    if (depth == key.size())
    {

        // Этот узел больше не конец слова
        if (node->isEndOfWord) node->isEndOfWord = false;

        // Если ключ не евляется префиксом, удаляем его
        if (isEmpty(node))
        {
            node = nullptr;
        }

        return node;
    }

    // Если не дошли до конца ключа, рекурсивно вызываем для ребенка
    // соответствующего символа
    int index{0};
    if (key[depth] >= 'a' && key[depth] <= 'z')
        index = key[depth] - 'a';
    else
        index = key[depth] - 'A';

    node->children[index] = remove(node->children[index], key, depth + 1);

    // Если у корня нет дочернего слова
    // (удален только один его дочерний элемент),
    // и он не заканчивается другим словом.
    if (isEmpty(node) && node->isEndOfWord == false)
    {
        node = nullptr;
    }

    // возвращаем новый корень
    return node;
}

// не изменияйте сигнатуру функции
auto Trie::findMinPrefixes(std::shared_ptr<TrieNode>& root, char buf[], int ind, std::string& res) -> void
{
    if (!root) return;

    int count{0};

    hasEndOfWord(root, count);

    if (count == 1)
    {
        buf[ind] = '\0';
        res += std::string(buf) + " ";
        return;
    }
    for (auto i{0}; i < ALPHABET_SIZE; ++i)
    {
        if (!root->children[i]) continue;
        buf[ind] = i + 'a';
        findMinPrefixes(root->children[i], buf, ind + 1, res);
    }
}

auto Trie::hasEndOfWord(std::shared_ptr<TrieNode>& node, int& count) -> void
{
    if (node->isEndOfWord) ++count;

    for (auto i{0}; i < ALPHABET_SIZE; ++i)
    {
        if (node->children[i]) hasEndOfWord(node->children[i], count);
    }
}

auto Trie::getAutocomplete(const std::string& preffix, int& words_number, std::string* words_array) const -> void
{
    if (!_root) return;

    auto preffix_length{(int)preffix.size()};
    auto node{_root};
    for (auto i{0}; i < preffix_length; ++i)
    {
        int index{0};

        if (preffix[i] >= 'a' && preffix[i] <= 'z')
            index = preffix[i] - 'a';
        else
            index = preffix[i] - 'A';

        if (!node->children[index])
        {
            words_number = 0;
            return;
        }
        node = node->children[index];
    }
    char buf[MAX_STRING_LENGTH];
    words_number = getAutocomplete_internal(node, words_array, buf, 0, words_number);
}

auto Trie::getAutocomplete_internal(std::shared_ptr<TrieNode>& node, std::string* words_array, char buf[], int index, int& words_number) const -> int
{
    static auto word_index{0};  // index string in the words_array
    if (!index) word_index = 0;

    if (words_number == word_index) return word_index;  // if all words found

    if (node->isEndOfWord)
    {
        buf[index] = '\0';

        words_array[word_index] = std::string(buf);

        ++word_index;
    }

    for (auto i{0}; i < ALPHABET_SIZE; ++i)
    {
        if (!node->children[i]) continue;

        buf[index] = i + 'a';

        getAutocomplete_internal(node->children[i], words_array, buf, index + 1, words_number);
    }
    return word_index;
}
