// Trie (Prefix Tree) Implementation
// Efficiently stores and queries a set of strings
// Supports: insert, search, prefix match
// Time Complexity: O(m) for insert/query, m = string length

#include <iostream>
#include <string>
using namespace std;

class Trie {
public:
    Trie* children[26] = {NULL};  // 26 lowercase letter children
    bool isEnd = false;           // Marks end of a word
    Trie() {}

    // Insert word: create nodes along character path, mark isEnd at end
    void insert(string word) {
        Trie* node = this;
        for(char ch : word) {
            ch -= 'a';
            if(node->children[ch] == NULL)
                node->children[ch] = new Trie();
            node = node->children[ch];
        }
        node->isEnd = true;
    }

    // Search word: traverse to end, check isEnd flag
    bool search(string word) {
        Trie* node = this;
        for(char ch : word) {
            ch -= 'a';
            if(node->children[ch] == NULL)
                return false;
            else node = node->children[ch];
        }
        if(node && node->isEnd)return true;
        return false;
    }

    // Prefix match: only check if prefix path exists, no isEnd needed
    bool startsWith(string prefix) {
        Trie* node = this;
        for(char ch : prefix) {
            ch -= 'a';
            if(node->children[ch] == NULL)
                return false;
            else node = node->children[ch];
        }
        if(node)return true;
        return false;
    }
};