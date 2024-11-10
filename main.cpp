#include "Trie.h"
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <cctype>

// Function to convert a string to lowercase
std::string toLower(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),[](unsigned char c){ return std::tolower(c); });
    return lowerStr;
}

// Function to load words from a file into the Trie
void loadWordsFromFile(Trie& trie, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string word;
    while (file >> word) {
        trie.insert(toLower(word));
    }

    file.close();
}

int main() {
    Trie trie;

    // Load words from file
    const std::string filename = "words.txt";  // Replace with your file name
    loadWordsFromFile(trie, filename);

    // Autocomplete loop
    while(true){
    std::string prefix;
    std::cout << "Enter a prefix to autocomplete (or type 'exit' to quit):" << std::endl;
    while (true) {
        std::cout << "> ";
        std::cin >> prefix;

        if (prefix == "exit") {
            break;
        }

        std::cout << "Suggestions for \"" << prefix << "\":" << std::endl;
        trie.autocomplete(prefix);
    }
    }

    return 0;
}
