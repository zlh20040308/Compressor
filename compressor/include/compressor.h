#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <unordered_map>
#include "huffman_tree.h"

class compressor
{
private:
    /*存放每个字符所对应的词频*/
    std::unordered_map<char, int> freq;
    /*解析文件，统计词频*/
    void parse_inputfile(std::ifstream &inputFile);
    /*生成压缩文件*/
    void write_zip(std::ifstream &input_file, std::ofstream &zip_file);
    /*生成密钥文件，解压的时候有用*/
    void write_key_file();

public:
    huffman_tree *tree;
    compressor();
    // 压缩文件
    void zip(std::ifstream &inputFile, std::ofstream &outputFile);
    ~compressor();
};

#endif