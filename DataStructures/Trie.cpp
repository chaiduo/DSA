// Trie（字典树）实现
// 用于高效存储和查询字符串集合
// 支持：插入、查找、前缀匹配
// 时间复杂度：插入/查询均为 O(m)，m 为字符串长度

#include <iostream>
#include <string>
using namespace std;

class Trie {
public:
    Trie* children[26] = {NULL};  // 26个小写字母子节点
    bool isEnd = false;           // 标记是否为某个单词的结尾
    Trie() {}

    // 插入单词：沿字符路径创建节点，末尾标记 isEnd
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
    
    // 查找单词：沿字符路径走到底，检查 isEnd 标记
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
    
    // 前缀匹配：只需检查前缀路径是否存在，无需 isEnd 标记
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