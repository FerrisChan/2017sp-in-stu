/*
 * 单向链表作为字典
 * 
 */

#include <stdio.h>
#include <stdlib.h>

enum {
    emptyPrefix = -1 // 设emptyPrefix为-1（11111111），即ascii
};

// 链表中的链string由上一个链string的字节byte和一个索引组成
struct DictNode { 
    int value; // 链表中的位置
    int prefix; // 字节的前缀
    int character; // 串的最后四位
    struct DictNode *next;   //指向下一个string
};
void dictionaryInit();
void appendNode(struct DictNode *node);
void dictionaryDestroy();
int dictionaryLookup(int prefix, int character);
int dictionaryPrefix(int value);
int dictionaryCharacter(int value);
void dictionaryAdd(int prefix, int character, int value);


struct DictNode *dictionary, *tail;

// 初始化字典
void dictionaryInit() {
    int i;
    struct DictNode *node;
    for (i = 0; i < 256; i++) { // ASCII
        node = (struct DictNode *)malloc(sizeof(struct DictNode));
        node->prefix = emptyPrefix;
        node->character = i;
        appendNode(node);
    }       
}

// 增加一个节点到链string
void appendNode(struct DictNode *node) {
    if (dictionary != NULL) tail->next = node;
    else dictionary = node;
    tail = node;
    node->next = NULL;
}

// 销毁字典
void dictionaryDestroy() {
    while (dictionary != NULL) {
        dictionary = dictionary->next; //只要把下一个字典指向本身，即销毁
    }
}

// 查询是否在字典中
int dictionaryLookup(int prefix, int character) {
    struct DictNode *node;
    for (node = dictionary; node != NULL; node = node->next) { 
        // 直接暴力搜索，找到，返回在字典中的位置
        if (node->prefix == prefix && node->character == character) return node->value;
    }
    return emptyPrefix;
}

int dictionaryPrefix(int value) {
    struct DictNode *node;
    for (node = dictionary; node != NULL; node = node->next) { // 直接暴力搜索
        if (node->value == value) return node->prefix;
    }
    return -1;
}

int dictionaryCharacter(int value) {
    struct DictNode *node;
    for (node = dictionary; node != NULL; node = node->next) { // 直接暴力搜索
        if (node->value == value) {
            
            return node->character;
        }
    }
    return -1;
}

//  增加码元prefix + character到字典中
void dictionaryAdd(int prefix, int character, int value) {
    struct DictNode *node;
    node = (struct DictNode *)malloc(sizeof(struct DictNode));
    node->value = value;
    node->prefix = prefix;
    node->character = character;
    appendNode(node);
}
