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
//构建一个长为len，元素为String类型的数组
void IniStrVector(StringVector* strVector,unsigned int len);

//将一个c类型的字符串插入到StringVector的末尾，如果已满，则返回错误-1,否则返回1
int InsertString(StringVector* strVector,const char* string);

//将c类型的字符串赋值给索引值inx位置的String
void AssignString(StringVector* strVector,unsigned int inx,const char* string);

//取出StringVector索引inx处的字符串，以c类型字符串返回,若数组越界，怎输出错误，返回空字符串
char* GetString(StringVector* strVector,unsigned int inx);

//删除索引位置inx处的字符串,后面的字符串前移，若数组越界，则什么也不做
void EraseString(StringVector *strVector,unsigned int inx);

//清空数组，length置0
void ClearStrVector(StringVector *strVector);

//释放StringVector的全部内存
void FreeStrVector(StringVector* strVector);

#endif
