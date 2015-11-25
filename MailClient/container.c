#include"container.h"
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
void IniString(String *ms){
	//ms->str = (char*)malloc(INILENGTH*sizeof(char));
        //while ((ms = (String*)malloc(sizeof(String))) == NULL);
	while ((ms->str = (char*)malloc(INILENGTH*sizeof(char))) == NULL);
    memset(ms->str, 0,INILENGTH*sizeof(char));
	ms->capacity = INILENGTH;
        ms->length=0;

}

void ClearString(String *ms){
     memset(ms->str,0,ms->capacity);

}
void CopyToString(String *ms, char const *string){
	unsigned int strLength = strlen(string);
	if (strLength >= ms->capacity){
		while((ms->str = (char*)realloc(ms->str, 2 * strLength*sizeof(char)))==NULL);
        memset(ms->str + strLength, 0, strLength*sizeof(char));
		ms->capacity = 2 * strLength;
	}
	strcpy(ms->str, string);
        ms->length=strLength;
}

void AddToString(String *ms, char const *string){
    unsigned int strLength = strlen(string);
    ms->length = ms->length+strLength;
	if (ms->length >= ms->capacity){
		while((ms->str = (char*)realloc(ms->str, 2 *ms->length*sizeof(char)))==NULL);
		memset(ms->str +ms->length, 0, ms->length*sizeof(char));
		ms->capacity = 2 * ms->length;
	}
        strcat(ms->str, string);
}

void AddChar(String *ms, char ch){
     char *charToString = (char*)malloc(2*sizeof(char));
     *charToString = ch;
     *(charToString+1) ='\0';
     AddToString(ms,charToString);
}

void FreeString(String* string){
	free(string->str);
}


void IniStrVector(StringVector* strVector,unsigned int len){
	unsigned int i;
	while((strVector->string=(String*)malloc(len*sizeof(String)))==NULL);
	for(i =0; i<len;i++){
		IniString(strVector->string+i);
	}
	strVector->capacity=len;
	strVector->length=0;
}

int InsertString(StringVector* strVector,const char* str){
	if(strVector->length < strVector->capacity ){
		CopyToString((strVector->string+strVector->length),str);
		strVector->length++;
		return 1;
	}
	else{
		return -1;
	}

}

void AssignString(StringVector* strVector,unsigned int inx,const char* str){
	if(inx<=strVector->length){
		CopyToString(strVector->string+inx,str);
	}
	else
		perror("AssignString:inx out of boundary");

}

const char* GetString(StringVector* strVector,unsigned int inx){
     if(inx<=strVector->length){
    	//printf("OK\n");
    	 //puts((strVector->string+inx)->str);
    	 return (strVector->string+inx)->str;

     }

     perror("GetString:inx out of boundary");
     return NULL;
}

void EraseString(StringVector *strVector,unsigned int inx){
	unsigned int j= 0;
	if(inx >= strVector->length)
		return;
	//FreeString(strVector->string+inx);
	for(j = inx;j<strVector->length;j++){
		CopyToString((strVector->string+j),(strVector->string+j+1)->str);
		(strVector->string+j)->length=(strVector->string+j+1)->length;
	    (strVector->string+j)->capacity=(strVector->string+j+1)->capacity;
	}
	strVector->length--;
}

void FreeStrVector(StringVector *strVector){
	unsigned int i = 0;
    for(i = 0; i < strVector->capacity;i++){
    	FreeString(strVector->string+i);
    }
	free(strVector->string);
}
void ClearStrVector(StringVector *strVector){
	strVector->length=0;
}
