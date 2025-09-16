#include <string>
#include <unordered_map>
#include <vector>

class TrieNode {

public:
    std::unordered_map<char, TrieNode> children;
    bool isEndOfword;

    bool has(char c);
    TrieNode* get(char c);
    void add(char c);

    TrieNode();
    ~TrieNode(){};

};

class Trie {
public:
    TrieNode root;

    void insert(std::string word);
    std::vector<std::string> search(std::string word);
    std::vector<std::string> startsWith(std::string prefix);
    void print();

    Trie();
    ~Trie(){};
};