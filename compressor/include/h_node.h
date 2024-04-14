#ifndef H_NODE_H
#define H_NODE_H

class h_node
{
private:
public:
    char val;    /* 该节点所表示的字符 */
    int freq;    /* 该节点所出现的频次 */
    bool isLeaf; /* 该节点是否为叶子节点 */
    int left;    /* 该节点的左孩子 */
    int right;   /* 该节点的左孩子 */
    h_node();
    h_node(char val, int freq, bool isLeaf);
    h_node(char val, int fre, bool isLeaf, int left, int right);
    ~h_node();
};

#endif
