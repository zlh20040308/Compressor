#include "decompressor.h"

decompressor::decompressor()
{
}

decompressor::decompressor(std::ifstream &key_file)
{

    char buf;               /*用于缓存读入的字符*/
    char key;               /*用于保存读入的键*/
    std::string value;      /*用于保存读入的值*/
    bool count_key = false; /*用于判断是否已经读入过键*/
    std::getline(key_file, value);
    this->total_freq = std::stoi(value);
    value.clear();
    while (key_file.get(buf))
    {
        if (!count_key)
        {
            key = buf;
            count_key = true;
        }
        else if (buf == ' ')
        {
            continue;
        }
        else if (buf == '\n')
        {
            this->huffman_decode[value] = key;
            count_key = false;
            value.clear();
        }
        else
        {
            value += buf;
        }
    }
    return;
}

// decompressor::decompressor(std::ifstream &key_file)
// {
//     char key;          /*用于保存读入的键*/
//     std::string value; /*用于保存读入的值*/
//     key_file >> this->total_freq >> key;
//     while (key_file >> key >> value)
//     {
//         this->huffman_decode[value] = key;
//         value.clear();
//     }
//     return;
// }

void decompressor::unzip(std::ifstream &inputFile, std::ofstream &outputFile)
{
    int count = 0;
    /* 判断文件是否正确打开 */
    if (!inputFile.is_open() || !outputFile.is_open())
    {
        std::cerr << "Fail in opening file" << std::endl;
        return;
    }
    int count_written = 0;
    char ch = 0;
    std::string buf = "";
    char buffer[1];
    // 每次读取一个字节
    while (inputFile.read(buffer, 1))
    {
        ch = buffer[0];
        /*从高到低依次取出这个字中所有的位*/
        for (size_t i = 0; i < sizeof(char) * 8; i++)
        {
            /*根据当前最高位来拼接缓冲字符串*/
            if (ch & 0x80)
            {
                buf += "1";
            }
            else
            {
                buf += "0";
            }
            /*如果当前缓冲字符串已经找到了对应的字符，就写入并清空*/
            if (this->huffman_decode.find(buf) != this->huffman_decode.end())
            {
                outputFile.put(this->huffman_decode[buf]);
                buf.clear();
                count_written++;
                if (count_written == this->total_freq)
                {
                    return;
                }
            }
            /*继续解析下一个字符*/
            ch <<= 1;
        }
    }
    return;
}

decompressor::~decompressor()
{
}