#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <vector>
#include <string>

class TrieNode {
public:
    TrieNode* children[26];
    bool isEndOfWord;

    TrieNode();
};

class Trie {
public:
    TrieNode* root;

    Trie();
    void insert(const std::string& word);
    TrieNode* searchPrefix(const std::string& prefix);
    void autocomplete(const std::string& prefix);
    void autocompleteHelper(TrieNode* node, std::string currentPrefix);
};

#endif // TRIE_H
