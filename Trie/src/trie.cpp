#include <iostream>
#include "trie.hpp"


TrieNode::TrieNode () { 
    this->_children;
    this->_isEndOfword = false;
}

bool TrieNode::has(char c) {
    return this->_children.count(c);
}

TrieNode* TrieNode::get(char c) {
    return &this->_children[c];
}

void TrieNode::add(char c) {
    this->_children[c] = TrieNode();
}

bool TrieNode::isEndOfWord() const {
    return _isEndOfword;
}

void TrieNode::setEndOfWord() {
    _isEndOfword = true;
}

std::unordered_map<char, TrieNode> TrieNode::getChildren() const {
    return _children;
}

Trie::Trie() {}


void Trie::insert(std::string word) {

    TrieNode* current_node = &this->root;
    for (char c: word) {
        if (!current_node->has(c)) {
            current_node->add(c);
        }
        current_node = current_node->get(c);
    }
    current_node->setEndOfWord();

}

bool Trie::search(std::string word) {

    TrieNode* current_node = &this->root;

    while (word.length() > 0) {
        char c = word.at(0);
        word.erase(0, 1);

        if (current_node->has(c)) {
            current_node = current_node->get(c);
        } else {
            return false;
        }
    }

    return current_node->isEndOfWord();

}

void startsWithHelper(const TrieNode* node, std::string word, std::vector<std::string>* words) {

    if (node->isEndOfWord()) {
        words->push_back(word);
    }

    for (const auto& pair: node->getChildren()) {
        startsWithHelper(&pair.second, word + pair.first, words);
    }

}

std::vector<std::string> Trie::startsWith(std::string prefix) {

    // Iterate to end of prefix
    std::string word = prefix;
    TrieNode* current_node = &this->root;

    while (prefix.length() > 0) {
        char c = prefix.at(0);
        prefix.erase(0, 1);

        if (current_node->has(c)) {
            current_node = current_node->get(c);
        } else {
            return {};
        }
    }

    std::vector<std::string> words;
    startsWithHelper(current_node, word, &words);

    return words;

}

void printHelper(std::string str, const TrieNode* node) {

    if (node->isEndOfWord()) {
        std::cout << str << "\n";
    }

    for (const auto& pair: node->getChildren()) {
        printHelper(str+pair.first, &pair.second);
    }
}

void Trie::print() {
    printHelper("", &this->root);
}