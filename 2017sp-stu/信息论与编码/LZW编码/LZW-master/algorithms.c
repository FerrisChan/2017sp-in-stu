#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.c"
#include "file.c" // 二进制文件读和写操作
#include "array.c" // 解压需要的队列

enum {
    dictionarySize = 4095, // 字典的容量，取2^12 = 4096个
    codeLength = 12, // 码长，ascii8位加 4位待扩充
    maxValue = dictionarySize - 1
};

// 函数声明
void compress(FILE *inputFile, FILE *outputFile);
void decompress(FILE *inputFile, FILE *outputFile);
int decode(int code, FILE * outputFile);

// 压缩compression 
void compress(FILE *inputFile, FILE *outputFile) {   
    int prefix;   // 前缀
    int character;  // 字符，

    int nextCode;  // 下一个码数，即下一个可使用的码
    int index;     // 索引
    
    // 以255的ascii码的字典开始
    nextCode = 256; 
    dictionaryInit();  // 初始化
    
    //  有数据读入
    while ((character = getc(inputFile)) != (unsigned)EOF) { // ch = 读入一个字符，并且不为 End Of File符号 ;
        
        // 字典包含 前缀和后四位 的 字符
        if ((index = dictionaryLookup(prefix, character)) != -1) prefix = index; // prefix = prefix+character，即更新前缀
        else { // 字典不包含，加入字典
            // 写入字典文件
            writeBinary(outputFile, prefix);
            
            // 加入码 prefix+character 到字典 dictionary
            if (nextCode < dictionarySize) dictionaryAdd(prefix, character, nextCode++);
            
            // prefix = character
            prefix = character; 
        }
    }
    // 编写字典文件
    writeBinary(outputFile, prefix); // 输出最后的码数
    
    if (leftover > 0) fputc(leftoverBits << 4, outputFile);
    
    // 销毁字典
    dictionaryDestroy();
}

// 解压译码decompression
// 从字典中每一个索引重构一个字符串
void decompress(FILE * inputFile, FILE * outputFile) {
    // int prevcode, currcode
    int previousCode; int currentCode;
    int nextCode = 256; // 也从ascii码开始

    int firstChar;
    
    // prevcode 为从lzw文件读入一个码
    previousCode = readBinary(inputFile);
    fputc(previousCode, outputFile);
    
    // 一直读入直到全部读完
    while ((currentCode = readBinary(inputFile)) > 0) { // currcode = 读入一个码
    
        if (currentCode >= nextCode) {
            fputc(firstChar = decode(previousCode, outputFile), outputFile); // 译码
          
        } else firstChar = decode(currentCode, outputFile); // 译第一个码
        
        // 加入一个新的码到待译码的串中
        if (nextCode < dictionarySize) dictionaryArrayAdd(previousCode, firstChar, nextCode++);
        
        // prevcode = currcode
        previousCode = currentCode;
    }
}

int decode(int code, FILE * outputFile) {
    int character; int temp;

    if (code > 255) { // 译码
        character = dictionaryArrayCharacter(code);
        temp = decode(dictionaryArrayPrefix(code), outputFile); // 递归译码
    } else {
        character = code; // ASCII
        temp = code;
    }
    fputc(character, outputFile);
    return temp;
}
