#include "compressor.h"

compressor::compressor()
{
    this->tree = nullptr;
}

void compressor::parse_inputfile(std::ifstream &inputFile)
{
    char ch;
    while (inputFile.get(ch))
    {
        if (this->freq.find(ch) != this->freq.end())
        {
            this->freq[ch]++;
        }
        else
        {
            this->freq[ch] = 1;
        }
    }
    return;
}

void compressor::write_zip(std::ifstream &input_file, std::ofstream &zip_file)
{
    char ch = 0;        /*缓冲读入的字符*/
    char buf = 0;       /*缓存要写入的数据*/
    int num_of_buf = 0; /*记录已缓存的位数*/
    while (input_file.get(ch))
    {
        for (auto &entry : this->tree->huffman_codes[ch])
        {
            if (entry == '0')
            {
                buf <<= 1;
            }
            else
            {
                buf = (buf << 1) | (char)1;
            }
            num_of_buf++;
            if (num_of_buf == sizeof(char) * 8)
            {
                zip_file.put(buf);
                buf = 0;
                num_of_buf = 0;
            }
        }
    }
    if (num_of_buf)
    {
        buf <<= (sizeof(char) * 8 - num_of_buf);
        zip_file.put(buf);
    }

    return;
}

void compressor::write_key_file()
{
    std::ofstream key_file("../key.txt");
    /*先写入一共有多少词*/
    key_file << this->tree->get_total_freq() << std::endl;
    for (const auto &pair : this->tree->huffman_codes)
    {
        key_file << pair.first << " " << pair.second << std::endl;
    }
    key_file.close();
    return;
}

void compressor::zip(std::ifstream &inputFile, std::ofstream &outputFile)
{

    /* 解析文件，计算每个字符的频次 */
    this->parse_inputfile(inputFile);

    /*构造根据字符频次构造Huffman_Tree,生成Huffman_Code*/
    this->tree = new huffman_tree(this->freq);

    /* 根据Huffman_Code生成压缩文件*/
    inputFile.clear();  // 清除错误状态标志
    inputFile.seekg(0); // 将文件指针定位到文件的起始位置
    this->write_zip(inputFile, outputFile);

    /*生成密钥文件*/
    this->write_key_file();

    return;
}

compressor::~compressor()
{
    delete this->tree;
}