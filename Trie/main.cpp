#include <iostream>
#include <string>
#include "./src/trie.cpp"

int main() {

    Trie trie;
    trie.insert("STUFF");
    trie.insert("STATIC");
    trie.insert("STEWIE GRIFFIN");

    std::cout << "Trie contains the following words: " << "\n";
    trie.print();
    std::cout << "\n";

    std::cout << "Trie contains string 'STUFF': " << trie.search("STUFF") << "\n";
    std::cout << "Trie contains string 'STEW': " << trie.search("STEW") << "\n";
    std::cout << "\n";

    std::cout << "Words in Trie starting with prefix 'ST': " << "\n";
    std::vector<std::string> words = trie.startsWith("ST");
    for (std::string str: words) {
        std::cout << str << "\n";
    }

    return 0;
}
