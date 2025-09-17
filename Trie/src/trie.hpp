#include <string>
#include <unordered_map>
#include <vector>

class TrieNode {

private:
    std::unordered_map<char, TrieNode> _children;
    bool _isEndOfword;

public:
    bool has(char c);
    void add(char c);
    TrieNode* get(char c);

    void setEndOfWord();

    bool isEndOfWord() const;
    std::unordered_map<char, TrieNode> getChildren() const;

    TrieNode();
    ~TrieNode(){};

};

class Trie {

private:
    TrieNode root;

public:
    void insert(std::string word);
    bool search(std::string word);
    std::vector<std::string> startsWith(std::string prefix);
    void print();

    Trie();
    ~Trie(){};
};