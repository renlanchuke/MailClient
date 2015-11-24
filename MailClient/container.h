/***************
 * This file is the header file of container.c
 * This include the function to manipunate the String
 * which is a structure to store the string.
 *
 * * ******************/

#ifndef CONTAINER
#define CONTAINER
//定义字符串的初始长度
#define INILENGTH 10
/***************************************
 * String结构及后面添加字符串操作
 * 实现了一个动态的字符串数组
 * *************************************/
typedef struct MyString{
	char *str;
	//字符串长度
	unsigned int length;
	//字符串容器的容量
	unsigned int capacity;
}String;
//初始化字符串结构体，分配初始长度
void IniString(String *);
//清空字符串结构体，但不释放内存
void ClearString(String *);
//将一个字符串赋值给字符串结构体
void CopyString(String *, char const*);
//将C类型的字符串添加到字符串结构中字符串的后面
void AddString(String *, char const*);
//将一个字符添加到字符串结构中字符串的后面
void AddChar(String *, char);
//释放字符串内存
void FreeString(String *string);

/******************************
 * MyVector结构体是一个定长的数组，
 * 每个数组元素一个String结构体
 * ****************************/
typedef struct MyVector{
	String *string;
	unsigned int length;
	unsigned int capacity;
}StringVector;

void IniStrVector(StringVector* strVector,unsigned int len);
int InsertString(StringVector* strVector,const char* string);
void AssignString(StringVector* strVector,unsigned int inx,const char* string);
void FreeStrVector(StringVector* strVector);
char* GetString(StringVector* strVector,unsigned int inx);
void EraseString(StringVector *strVector,unsigned int inx);
void ClearStrVector(StringVector *strVector);
#endif
