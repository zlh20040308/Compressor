#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#include <iostream>
#include <queue>
#include <cctype>
#include <string>
#include <unordered_map>
#include "h_node.h"

typedef struct
{
    char val;    /* 该节点所表示的字符 */
    int freq;    /* 该节点所出现的频次 */
    bool isLeaf; /* 该节点是否为叶子节点 */
    int left;    /* 该节点的左孩子 */
    int right;   /* 该节点的左孩子 */
} Elem;

class huffman_tree
{
private:
    h_node *tree; /*指向huffman_tree的头节点*/
    int _size;    /*整棵树的节点个数*/
    std::vector<h_node *> nodes;
    int total_freq;
    static bool cmp(const Elem &a, const Elem &b)
    {
        return a.freq > b.freq;
    };
    /*存放每个节点对应的频次*/
    std::priority_queue<
        Elem,
        std::deque<Elem>,
        decltype(&cmp)>
        minHeap{cmp};
    /*通过深度优先遍历构造huffman_code*/
    void dfs_code(h_node *node, const std::string &code);
    /*根据频次表构建huffman_tree*/
    void build_huffman_tree(std::unordered_map<char, int> &freq);
    /*根据频次表构建优先队列*/
    void build_minHeap(std::unordered_map<char, int> &freq);
    void get_huffman_codes();
    void set_tree_size(int size);
    void destory_huffman_tree();

public:
    std::unordered_map<char, std::string> huffman_codes; /*存放每个字符对应的huffman_code*/
    huffman_tree();
    huffman_tree(std::unordered_map<char, int> &freq);
    int get_total_freq();
    int size();
    ~huffman_tree();
};

#endif