#include "huffman_tree.h"

huffman_tree::huffman_tree() : _size(0), minHeap(cmp) {}

huffman_tree::huffman_tree(std::unordered_map<char, int> &freq) : _size(0), minHeap(cmp)
{
    int count = 0;
    this->set_tree_size(2 * freq.size() - 1);
    for (auto &entry : freq)
    {
        count += entry.second;
    }
    this->total_freq = count;
    build_huffman_tree(freq);
    get_huffman_codes();
}

int huffman_tree::get_total_freq()
{
    return this->total_freq;
}

void huffman_tree::set_tree_size(int size)
{
    this->nodes.resize(size + 1);
    this->_size = size;
    for (size_t i = 0; i < size + 1; i++)
    {
        this->nodes[i] = nullptr;
    }
    return;
}

void huffman_tree::build_minHeap(std::unordered_map<char, int> &freq)
{
    for (auto [val, freq] : freq)
    {
        this->minHeap.push(Elem{val, freq, true, 0, 0});
    }
    return;
}

void huffman_tree::build_huffman_tree(std::unordered_map<char, int> &freq)
{
    int count = 0;
    /*根据字符频次构建优先队列*/
    this->build_minHeap(freq);

    /* 构造huffman_tree*/
    /*如果堆不为空*/
    while (this->minHeap.size() > 1)
    {
        /*取出前两个元素*/
        auto [val1, freq1, isLeaf1, left1, rigth1] = minHeap.top();
        minHeap.pop();
        auto [val2, freq2, isLeaf2, left2, rigth2] = minHeap.top();
        minHeap.pop();

        this->nodes[count * 2 + 1] = new h_node(val1, freq1, isLeaf1, left1, rigth1);
        this->nodes[count * 2 + 2] = new h_node(val2, freq2, isLeaf2, left2, rigth2);
        /*生成父节点，其左右指针指向这两元素*/
        this->minHeap.push(Elem{static_cast<char>(val1 + val2), freq1 + freq2, false, count * 2 + 1, count * 2 + 2});

        count++;
    }

    // 处理剩下的最后一个节点
    if (!this->minHeap.empty())
    {
        auto [val, freq, isLeaf, left, rigth] = minHeap.top();
        minHeap.pop();
        this->tree = this->nodes[count * 2 + 1] = new h_node(val, freq, isLeaf, left, rigth);
    }
    return;
}

void huffman_tree::dfs_code(h_node *node, const std::string &code)
{
    if (node == nullptr)
    {
        return;
    }
    if (node->isLeaf)
    {
        this->huffman_codes[node->val] = code;
        return;
    }
    dfs_code(this->nodes[node->left], code + '0');
    dfs_code(this->nodes[node->right], code + '1');
    return;
}

void huffman_tree::get_huffman_codes()
{
    dfs_code(this->tree, "");
    return;
}

int huffman_tree::size()
{
    return this->_size;
}

void huffman_tree::destory_huffman_tree()
{
}

huffman_tree::~huffman_tree()
{
}