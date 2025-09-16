#include <iostream>
#include "trie.hpp"


TrieNode::TrieNode () { 
    this->children = {};
    this->isEndOfword = false;
}

bool TrieNode::has(char c) {
    return this->children.count(c);
}

TrieNode* TrieNode::get(char c) {
    return &this->children[c];
}

void TrieNode::add(char c) {
    this->children[c] = TrieNode();
}


Trie::Trie() {
    this->root = TrieNode();
}


void Trie::insert(std::string word) {

    TrieNode* current_node = &this->root;
    for (char c: word) {
        if (!current_node->has(c)) {
            current_node->add(c);
        }
        current_node = current_node->get(c);
    }
    current_node->isEndOfword = true;

}

// std::vector<std::string> Trie::search(std::string word) {

// }

// std::vector<std::string> Trie::startsWith(std::string prefix) {

// }

void printHelper(std::string str, const TrieNode* node) {

    if (node->isEndOfword) {
        std::cout << str << "\n";
    }

    for (const auto& pair: node->children) {
        printHelper(str+pair.first, &pair.second);
    }
}

void Trie::print() {
    printHelper("", &this->root);
}