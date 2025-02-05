# Compressor  

---  

这是一个基于哈夫曼编码的文本压缩/解压器，[参考视频](https://www.bilibili.com/video/BV18V411v7px/?spm_id_from=333.337.search-card.all.click&vd_source=c5f2a2773d02bf2b81c008b900c8461b)  

## 哈夫曼编码算法  

哈夫曼编码算法是一种可变长度编码算法，下面用一个例子进行讲解：  

假设现在有一段很长的字符串，由a-f英文字母组成，一共有10万个字符，对每个字符出现的频率进行统计如下，计算机需要把它以二进制的形式保存，什么样的编码方式最节省空间  

|              | a   | b   | c   | d   | e   | f   |
| ------------ | --- | --- | --- | --- | --- | --- |
| 频率（千字） | 45  | 13  | 12  | 16  | 9   | 5   |  

---  

### 固定长度编码  

让我们先来引入固定长度编码，如下表：  

|              | a   | b   | c   | d   | e   | f   |
| ------------ | --- | --- | --- | --- | --- | --- |
| 固定长度编码 | 000 | 001 | 010 | 011 | 100 | 101 |  

长度为 3 * 10万 = 30万  

#### 优点  

1. 算法简单，编码和解码的时间复杂度都是O(n)  

#### 缺点  

2. 浪费空间  

---  

### 可变长度编码  

有没有优化的空间呢，观察频率表可知，a出现的频率是最多的，f是最少的，所以让出现次数多的a对应的编号短一点，而出现次数少的e和f长一点似乎会更好些，剩下的处于中间，得到下表：  

|              | a   | b   | c   | d   | e    | f    |
| ------------ | --- | --- | --- | --- | ---- | ---- |
| 可变长度编码 | 1   | 101 | 100 | 111 | 1101 | 1100 |  

长度为 45 * 1 + 13 * 3 + 12 * 3 + 16 * 3 + 9 * 4 + 5 * 4 = 224(千)=22.4万  

---

可以看到已经少了不少了，至于可变长度编码怎么来的，我们下面会介绍，现在我们先来分析上表存在什么问题  

假设现在有一二进制序列**1101**，依照上表，可拆分成这样：  

| a   | b   |
| --- | --- |
| 1   | 101 |  

但是如果看成整体的话则是e的编号：  

| e    |
| ---- |
| 1101 |  

---

可以看到，这样就有歧义了，原因就在与我们在解码的时候出现了**一个字母的编码是另一个字母的编码的前缀**，而如果a本身是0的话，比如解码这个字符串，第一个0一定是a，剩下一定是b，没有其他可能，所以没有一个编码是其他编码的前缀，称为**前缀编码**，其实叫无前缀编码可能更合适一些，总之就一个意思，可变长度的编码就需要这样的要求，为了方便解码，我们引入了**哈夫曼二叉树**  

---

#### 哈夫曼二叉树  

##### 构建哈夫曼二叉树的规则  

若是0，则左子节点，若是1，则右子节点，若按照下表构建则为下图所示：  

|              | a   | b   | c   | d   | e    | f    |
| ------------ | --- | --- | --- | --- | ---- | ---- |
| 可变长度编码 | 0   | 101 | 100 | 111 | 1101 | 1100 |  

![HuffmanTree.png](/pic/HuffmanTree.png)  

---

##### 哈夫曼树的一些性质  

1. 哈夫曼树仅对叶子节点进行编码，这样就可以保证**一个字母的编码不会是另一个字母的编码的前缀**，因为**任意一个叶子节点都不会出现在从根节点到其他叶子节点的路径上**  

2. 在不出现歧义的情况下，通过哈夫曼树编出来的码长度最短，这一点与我们下面讲到的构造策略有关  

---

##### 构造哈夫曼二叉树算法  

我们采用贪心的思想构造哈夫曼二叉树：  

1. 首先我们把所有字符组成的集合称为大写的C，然后把当前所有的字符都加入一个叫做Q的**最小优先队列**，也就是在这个队列中，按照每个字符的频次永远保持从小到大的顺序，如下图：  

![优先队列.png](/pic/queue.png)  

2. 接下来我们取出队列中的前两个元素，分别作为左子节点和右子节点，接着将左右节点的频数相加，生成一个新的节点Z，作为根节点的频数是14，如图：  

![merge.png](/pic/merge.png)  

3. 再把Z插入队列Q中，如图：  

![resort.png](/pic/resort.png)  

4. 重复2、3步骤，直到队列为空，构造完毕，如图：  

![result.png](/pic/result.png)  

5. 根据哈夫曼编码的规则，为每个节点编码，如图：  

![HuffmanTree.png](/pic/HuffmanTree.png)  

6. 根据哈夫曼树写出哈夫曼编码，如下表：  

|            | a   | b   | c   | d   | e    | f    |
| ---------- | --- | --- | --- | --- | ---- | ---- |
| 哈夫曼编码 | 0   | 101 | 100 | 111 | 1101 | 1100 |  

---

在了解过整个过程之后，我们便可以解释为什么通过哈夫曼树编出来的码长度最短，因为每次我们都合并出现次数最少的两个字母，所以说出现次数越少的字母一定会越早被合并，越早合并那么它在树中深度就越深，它的编码长度就越长，反之，出现次数越多的字母，它编的码就越短，那这样就能尽可能的让整个字符串编出来的二进制序列更短。  

---

## 程序核心接口设计  

---  

### huffman_tree.h  

```cpp
/*通过深度优先遍历构造huffman_code*/
void dfs_code(h_node *node, const std::string &code);
/*根据频次表构建huffman_tree*/
void build_huffman_tree(std::unordered_map<char, int> &freq);
/*根据频次表构建优先队列*/
void build_minHeap(std::unordered_map<char, int> &freq);
```    

---  

### compressor.h  

```cpp
/*存放每个字符所对应的词频*/
std::unordered_map<char, int> freq;
/*解析文件，统计词频*/
void parse_inputfile(std::ifstream &inputFile);
/*生成压缩文件*/
void write_zip(std::ifstream &input_file, std::ofstream &zip_file);
/*生成密钥文件，解压的时候有用*/
void write_key_file();
// 压缩文件
void zip(std::ifstream &inputFile, std::ofstream &outputFile);
```