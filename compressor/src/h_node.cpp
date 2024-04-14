#include <h_node.h>

h_node::h_node() : val(0), freq(0), isLeaf(false), left(0), right(0) {}

h_node::h_node(char val, int freq, bool isLeaf) : val(val), freq(freq), isLeaf(isLeaf), left(0), right(0) {}

h_node::h_node(char val, int freq, bool isLeaf, int left, int right) : val(val), freq(freq), isLeaf(isLeaf), left(left), right(right) {}

h_node::~h_node() {}
