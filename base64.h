#ifndef _BASE64_H_
#define _BASE64_H_
#include"container.h"
//编码第一个参数输出String类型，第二参数输入一个C类型的字符串
void base64Encode(String* ,unsigned char const*);
//解码第一个参数输出String,第二个参数已编码好字符串
void base64Decode(String* , String const *);
#endif
