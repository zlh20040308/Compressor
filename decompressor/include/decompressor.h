#ifndef DECOMPRESSOR_H
#define DECOMPRESSOR_H

#include <iostream>
#include <fstream>
#include <unordered_map>
class decompressor
{
private:
    std::unordered_map<std::string, char> huffman_decode;

public:
    int total_freq;
    decompressor();
    decompressor(std::ifstream &key_file);
    // 解压文件
    void unzip(std::ifstream &inputFile, std::ofstream &outputFile);
    ~decompressor();
};

#endif
