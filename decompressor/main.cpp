#include <iostream>
#include <fstream>
#include "decompressor.h"

int main(int argc, char const *argv[])
{
    /*如果参数小于四个则报错退出*/
    if (argc < 4)
    {
        std::cerr << "Usage: compressor <zip_file> <destination_file> <key_file>." << std::endl;
        exit(1);
    }

    /* 打开待解压文件 */
    std::ifstream zip_file(argv[1]);
    if (!zip_file.is_open())
    {
        std::cerr << "Fail in opening zip_file." << std::endl;
        exit(1);
    }

    /* 打开目标文件 */
    std::ofstream destination_file(argv[2]);
    if (!destination_file.is_open())
    {
        std::cerr << "Fail in opening destination_file." << std::endl;
        zip_file.close();
        exit(1);
    }

    /* 打开密钥文件 */
    std::ifstream key_file(argv[3]);
    if (!key_file.is_open())
    {
        std::cerr << "Fail in opening key_file." << std::endl;
        zip_file.close();
        destination_file.close();
        exit(1);
    }

    /*压缩*/
    decompressor dp(key_file);
    dp.unzip(zip_file, destination_file);

    /*关闭文件流*/
    zip_file.close();
    destination_file.close();
    key_file.close();

    return 0;
}
