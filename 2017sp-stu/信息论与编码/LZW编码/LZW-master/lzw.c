/*
 * lzw main函数代码  
 * 14通信工程 陈李锋 2014081025
 * 实现lzw的压缩和解压，需要输入待压缩的文件是html格式，
 * 压缩好的文件为.lzw 格式
 * pdf文件可以使用在线转换： http://app.xunjiepdf.com/pdf2html
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "algorithms.c" // LZW 算法实现

FILE *inputFile;
FILE *outputFile;

int main(int argc, char** argv) { // 输入参数数量从1开始计算 输入的字符串
    // 判断输入参数是否正确和选项
    if (argc > 2) {
        if (strcmp(argv[1], "c") == 0) { // 输入压缩选项 "c"
            inputFile = fopen(argv[2], "r"); // 读入压缩文件 (HTML)
            outputFile = fopen(strcat(argv[2], ".lzw"), "w+b"); // 输出二进制文件，lzw格式 
            
            if (outputFile == NULL || inputFile == NULL) {
                printf("Can't open files\n'"); return 0;
            }
            
            compress(inputFile, outputFile);
        } else { // 输入解压选项 "d"
            inputFile = fopen(argv[2], "rb"); // 读入二进制文件，lzw格式 

            char temp[20]; int length = strlen(argv[2])-4;
            strncpy(temp, argv[2], length);
            temp[length] = '\0';
            outputFile = fopen(temp, "w"); // 输出文件 (HTML)
            
            if (outputFile == NULL || inputFile == NULL) {
                printf("Can't open files\n'"); return 0;
            }
            
            decompress(inputFile, outputFile);
        }
        
        fclose(inputFile); fclose(outputFile); // 关闭文件句柄
    } else {
        // 用法说明
        printf("LZW 压缩算法 \n");
        printf("Usage:    lzw <command> <input file>\n\n");
        printf("<Commands>\n  c       Compress压缩 \n  d       Decompress解压\n");
    }
    
    return 0;
}
