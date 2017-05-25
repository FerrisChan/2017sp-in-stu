/*
 * 文件的读写函数，主要是把十二位的码元分为前八位和后四位，前八位用来写到输出文件中译码，后四位用来下一次译码
 * 下一次译码的时候，是将上一次的后四位和当前的码结合一起译码
 */

#include <stdio.h>

void writeBinary(FILE * output, int code);
int readBinary(FILE * input);

int leftover = 0;
int leftoverBits;

void writeBinary(FILE * output, int code) {  // 写入文件函数
    if (leftover > 0) {
        int previousCode = (leftoverBits << 4) + (code >> 8);
        
        fputc(previousCode, output);
        fputc(code, output);
        
        leftover = 0;
    } else {
        leftoverBits = code & 0xF;
        leftover = 1;
        
        fputc(code >> 4, output);
    }
}

int readBinary(FILE * input) {  //读入文件函数
    int code = fgetc(input);    
    if (code == EOF) return 0;

    if (leftover > 0) {
        code = (leftoverBits << 8) + code;
        
        leftover = 0;
    } else {
        int nextCode = fgetc(input);
        
        leftoverBits = nextCode & 0xF; 
        leftover = 1;
        
        code = (code << 4) + (nextCode >> 4);
    }
    return code;
}
