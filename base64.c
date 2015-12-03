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


//判断字符是否为64个可见字符

static bool is_base64(unsigned char c) {
    return (isalnum(c) || (c == '+') || (c == '/'));
}

void base64_encode(String *ret, unsigned char const* bytes_to_encode, unsigned int in_len) {
    //debug
    //printf("in_len %d\n\n",in_len);
    //String ret;
    //IniString(&ret);
    int i = 0, j = 0;
    unsigned char char_array_3[3], char_array_4[4];

    while (in_len--) {
        char_array_3[i++] = *(bytes_to_encode++);
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for (j = 0; j < 4; j++)
                AddChar(ret, base64_chars[char_array_4[j]]);
            i = 0;
        }
    }

    if (i) {
        for (j = i; j < 3; j++)
            char_array_3[j] = '\0';
        //debug
        //printf("char_array_3 %s\n",char_array_3);
        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;
         //printf("char_array_4 %d\n",char_array_4[0]);
        for (j = 0; (j < i + 1); j++){
            //printf("base64_chars %c\n",);
            AddChar(ret, base64_chars[char_array_4[j]]);
           // printf("%s \n",ret.str);

        }





        while ((i++ < 3))
             AddChar(ret,'=');

    }

    //return &ret;

}

void base64_decode(String* ret, String const *encoded_string) {
    int in_len = encoded_string->length;
    int i = 0, j = 0, in_ = 0;
    unsigned char char_array_4[4], char_array_3[3];
    //String ret;
    //IniString(&ret);

    while (in_len-- && (encoded_string->str[in_] != '=') && is_base64(encoded_string->str[in_])) {
        char_array_4[i++] = encoded_string->str[in_];
        in_++;
        if (i == 4) {
            for (i = 0; i < 4; i++)
                char_array_4[i] = strchr(base64_chars,char_array_4[i]) - base64_chars;

            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

            for (i = 0; (i < 3); i++)
                AddChar(ret, char_array_3[i]);
            i = 0;
        }
    }
    //debug
    //printf("%d %s\n", i, char_array_4);
    if (i) {
        for (j = i; j < 4; j++)
            char_array_4[j] = 0;
        //printf("%d %s\n", i, char_array_4);
        for (j = 0; j < 4; j++)
            char_array_4[j] = strchr(base64_chars,char_array_4[j]) - base64_chars;
        //printf("char_array_4=%d %s\n", i, char_array_4);
        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        //printf("char_array_3[0]= %c\n",char_array_3[0]);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

        for (j = 0; (j < i - 1); j++)
            AddChar(ret, char_array_3[j]);
    }

    //return &ret;
}
