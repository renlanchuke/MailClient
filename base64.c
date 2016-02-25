/************************************************************
 * 2015.9 modified by renlanchuke
 ************************************************************/


/*
   base64.cpp and base64.h

   Copyright (C) 2004-2008 René Nyffenegger

   This source code is provided 'as-is', without any express or implied
   warranty. In no event will the author be held liable for any damages
   arising from the use of this software.

   Permission is granted to anyone to use this software for any purpose,
   including commercial applications, and to alter it and redistribute it
   freely, subject to the following restrictions:

   1. The origin of this source code must not be misrepresented; you must not
      claim that you wrote the original source code. If you use this source code
      in a product, an acknowledgment in the product documentation would be
      appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and must not be
      misrepresented as being the original source code.

   3. This notice may not be removed or altered from any source distribution.

   René Nyffenegger rene.nyffenegger@adp-gmbh.ch

*/



/*********
 *base64编码和解码
 * 邮件协议只能传输64个可见的ASCII码字符，特点是左边两位为0
 * base64需要把3个八位字节映射为4个6位字节， 不足3个并在末尾补零构成完整字节
 *********/
#include "base64.h"
#include "container.h"
#include<string.h>
#include<stdio.h>
#include<ctype.h>
typedef int bool;
static const char base64_chars[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                                   "abcdefghijklmnopqrstuvwxyz"
                                                    "0123456789+/";

void base64Encode(String *output, unsigned char const* bytesEncode) {
    //debug
    //printf("inStringLength %d\n\n",inStringLength);
    //String output;
    //IniString(&output);
    int i = 0, j = 0;
    int inBytesLength=strlen(bytesEncode);
    unsigned char char3Array[3], char4Array[4];

    while (inBytesLength--) {
        char3Array[i++] = *(bytesEncode++);
        if (i == 3) {
            char4Array[0] = (char3Array[0] & 0xfc) >> 2;
            char4Array[1] = ((char3Array[0] & 0x03) << 4) + ((char3Array[1] & 0xf0) >> 4);
            char4Array[2] = ((char3Array[1] & 0x0f) << 2) + ((char3Array[2] & 0xc0) >> 6);
            char4Array[3] = char3Array[2] & 0x3f;

            for (j = 0; j < 4; j++)
                AddChar(output, base64_chars[char4Array[j]]);
            i = 0;
        }
    }

    if (i) {
        for (j = i; j < 3; j++)
            char3Array[j] = '\0';
        //debug
        //printf("char3Array %s\n",char3Array);
        char4Array[0] = (char3Array[0] & 0xfc) >> 2;
        char4Array[1] = ((char3Array[0] & 0x03) << 4) + ((char3Array[1] & 0xf0) >> 4);
        char4Array[2] = ((char3Array[1] & 0x0f) << 2) + ((char3Array[2] & 0xc0) >> 6);
        char4Array[3] = char3Array[2] & 0x3f;
         //printf("char4Array %d\n",char4Array[0]);
        for (j = 0; (j < i + 1); j++){
            //printf("base64_chars %c\n",);
            AddChar(output, base64_chars[char4Array[j]]);
           // printf("%s \n",output.str);

        }

        while ((i++ < 3))
             AddChar(output,'=');

    }

    //outputurn &output;

}

void base64Decode(String* output, String const *encodedString) {
    int inStringLength = encodedString->length;
    int i = 0, j = 0, index = 0;
    unsigned char char4Array[4], char3Array[3];
    //String output;
    //IniString(&output);

    while (inStringLength-- && (encodedString->str[index] != '=') && is_base64(encodedString->str[index])) {
        char4Array[i++] = encodedString->str[index];
        index++;
        if (i == 4) {
            for (i = 0; i < 4; i++)
                char4Array[i] = strchr(base64_chars,char4Array[i]) - base64_chars;

            char3Array[0] = (char4Array[0] << 2) + ((char4Array[1] & 0x30) >> 4);
            char3Array[1] = ((char4Array[1] & 0xf) << 4) + ((char4Array[2] & 0x3c) >> 2);
            char3Array[2] = ((char4Array[2] & 0x3) << 6) + char4Array[3];

            for (i = 0; (i < 3); i++)
                AddChar(output, char3Array[i]);
            i = 0;
        }
    }
    //debug
    //printf("%d %s\n", i, char4Array);
    if (i) {
        for (j = i; j < 4; j++)
            char4Array[j] = 0;
        //printf("%d %s\n", i, char4Array);
        for (j = 0; j < 4; j++)
            char4Array[j] = strchr(base64_chars,char4Array[j]) - base64_chars;
        //printf("char4Array=%d %s\n", i, char4Array);
        char3Array[0] = (char4Array[0] << 2) + ((char4Array[1] & 0x30) >> 4);
        //printf("char3Array[0]= %c\n",char3Array[0]);
        char3Array[1] = ((char4Array[1] & 0xf) << 4) + ((char4Array[2] & 0x3c) >> 2);
        char3Array[2] = ((char4Array[2] & 0x3) << 6) + char4Array[3];

        for (j = 0; (j < i - 1); j++)
            AddChar(output, char3Array[j]);
    }

    //outputurn &output;
}
