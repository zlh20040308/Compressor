#include <iostream>
#include <fstream>
#include "compressor.h"

int main(int argc, char const *argv[])
{
    /*如果参数小于三个则报错退出*/
    if (argc < 3)
    {
        std::cerr << "Usage: compressor <input_file> <destination_file>." << std::endl;
        exit(1);
    }

    /* 打开待压缩文件 */
    std::ifstream input_file(argv[1]);
    if (!input_file.is_open())
    {
        std::cerr << "Fail in opening input_file." << std::endl;
        exit(1);
    }

    /* 打开目标文件 */
    std::ofstream destination_file(argv[2]);
    if (!destination_file.is_open())
    {
        std::cerr << "Fail in opening destination_file." << std::endl;
        input_file.close();
        exit(1);
    }

    /*压缩*/
    compressor cp;
    cp.zip(input_file, destination_file);

    /*关闭文件流*/
    input_file.close();
    destination_file.close();

    return 0;
}
