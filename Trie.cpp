#include "Trie.h"

TrieNode::TrieNode() {
    isEndOfWord = false;
    for (int i = 0; i < 26; i++) {
        children[i] = nullptr;
    }
}

Trie::Trie() {
    root = new TrieNode();
}

void Trie::insert(const std::string& word) {
    TrieNode* node = root;
    for (char c : word) {
        if (c < 'a' || c > 'z') {  
            std::cerr << "Error: Invalid character '" << c << "' in word \"" << word << "\"" << std::endl;
            return;
        }
        
        int index = c - 'a';
        if (!node->children[index]) {
            node->children[index] = new TrieNode();
        }
        node = node->children[index];
    }
    node->isEndOfWord = true;
    
}

TrieNode* Trie::searchPrefix(const std::string& prefix) {
    TrieNode* node = root;
    for (char c : prefix) {
        if (c < 'a' || c > 'z') {  
            std::cerr << "Error: Invalid character in prefix \"" << prefix << "\"" << std::endl;
            return nullptr;
        }
        
        int index = c - 'a';
        if (!node->children[index]) {
            return nullptr;
        }
        node = node->children[index];
    }
    return node;
}

void Trie::autocompleteHelper(TrieNode* node, std::string currentPrefix) {
    if (node->isEndOfWord) {
        std::cout << "Suggestion: " << currentPrefix << std::endl;
    }

    for (int i = 0; i < 26; i++) {
        if (node->children[i]) {
            autocompleteHelper(node->children[i], currentPrefix + static_cast<char>('a' + i));
        }
    }
}

void Trie::autocomplete(const std::string& prefix) {
    TrieNode* node = searchPrefix(prefix);
    if (node == nullptr) {
        std::cout << "No suggestions found for \"" << prefix << "\"" << std::endl;
        return;
    }

    autocompleteHelper(node, prefix);
}
