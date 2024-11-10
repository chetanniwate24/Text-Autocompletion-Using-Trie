class TrieNode {
    constructor() {
        this.children = {};
        this.isEndOfWord = false;
    }
}

class Trie {
    constructor() {
        this.root = new TrieNode();
    }

    insert(word) {
        let node = this.root;
        for (let char of word) {
            if (!node.children[char]) {
                node.children[char] = new TrieNode();
            }
            node = node.children[char];
        }
        node.isEndOfWord = true;
    }

    autocomplete(prefix, limit = 10) {
        let node = this.root;
        for (let char of prefix) {
            if (!node.children[char]) {
                return [];
            }
            node = node.children[char];
        }
        let suggestions = [];
        this.autocompleteHelper(node, prefix, suggestions, limit);
        return suggestions;
    }

    autocompleteHelper(node, prefix, suggestions, limit) {
        if (suggestions.length >= limit) return;
        if (node.isEndOfWord) {
            suggestions.push(prefix);
        }
        for (let char in node.children) {
            this.autocompleteHelper(node.children[char], prefix + char, suggestions, limit);
        }
    }
}

let trie = new Trie();
let fileInput = document.getElementById("file-input");
let inputField = document.getElementById("input-field");
let suggestionsDiv = document.getElementById("suggestions-div");

function debounce(fn, delay) {
    let timeout;
    return function (...args) {
        clearTimeout(timeout);
        timeout = setTimeout(() => fn(...args), delay);
    };
}

fileInput.addEventListener("change", function() {
    let file = fileInput.files[0];
    let reader = new FileReader();
    reader.onload = function() {
        let fileContent = reader.result;
        let words = fileContent.split("\n");
        for (let word of words) {
            trie.insert(word.trim().toLowerCase());
        }
    };
    reader.readAsText(file);
});

inputField.addEventListener("input", debounce(function() {
    let prefix = inputField.value.toLowerCase();
    let suggestions = trie.autocomplete(prefix, 10); 

    suggestionsDiv.innerHTML = "";

    if (suggestions.length === 0) {
        let noSuggestionSpan = document.createElement("span");
        noSuggestionSpan.textContent = "No suggestions";
        suggestionsDiv.appendChild(noSuggestionSpan);
    } else {
        for (let suggestion of suggestions) {
            let suggestionSpan = document.createElement("span");
            suggestionSpan.textContent = suggestion;
            suggestionsDiv.appendChild(suggestionSpan);
            suggestionSpan.addEventListener("click", function() {
                inputField.value = suggestion;
                suggestionsDiv.style.display = "none";
            });
        }
    }

    suggestionsDiv.style.display = suggestions.length || prefix ? "block" : "none";
}, 300)); 


document.addEventListener("click", function(event) {
    if (event.target !== inputField && event.target !== suggestionsDiv) {
        suggestionsDiv.style.display = "none";
    }
});