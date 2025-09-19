#include <string>
#include <unordered_map>
#include <vector>

class TrieNode {

private:
    std::unordered_map<char, TrieNode> children;
    bool isEndOfword;

public:
    bool has(char c);
    void add(char c);
    TrieNode* get(char c);

    TrieNode();
    ~TrieNode(){};

friend class Trie;

};

class Trie {

private:
    TrieNode root;
    void startsWithHelper(const TrieNode* node, std::string word, std::vector<std::string>* words);
    void printHelper(std::string str, const TrieNode* node);

public:
    void insert(std::string word);
    bool search(std::string word);
    std::vector<std::string> startsWith(std::string prefix);
    void print();

    Trie();
    ~Trie(){};
};