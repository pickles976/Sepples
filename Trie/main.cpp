#include <iostream>
#include "./src/trie.cpp"

int main() {
    std::cout << "Testing" << "\n";

    Trie trie;
    trie.insert("STUFF");
    trie.insert("STATIC");
    trie.insert("STEWIE GRIFFIN");
    trie.print();

    return 0;
}
