#pragma once
#ifndef _MD5_H_
#define _MD5_H_

#include <stdio.h>

// first, some types:
  typedef unsigned       int uint4; // assumes integer is 4 words long
  typedef unsigned short int uint2; // assumes short integer is 2 words long
  typedef unsigned       char uint1; // assumes char is 1 word long

//
  void  MD5Update     (unsigned char *input, unsigned int input_length);
  void  MD5UpdateString (unsigned char *input);
  void  MD5UpdateFile     (FILE *file);
  void  MD5Finalize   ();

//将字符串转化为MD5值
  void MD5String             (unsigned char *string); // digest string, finalize

//将文件转化成MD5值
  void MD5File              (FILE *file);            // digest file, close, finalize


// methods to acquire finalized result
//返回16字节二进制数组
  unsigned char    *MD5RawDigest ();  // digest as a 16-byte binary array
  //返回33字节字符串，表示MD5值十六进制形式
  char             *MD5HexDigest ();  // digest as a 33-byte ascii-hex string


// last, the private methods, mostly static:
  void MD5Init             ();               // called by all constructors
  void MD5Transform        (uint1 *buffer);  // does the real update work.  Note
                                          // that length is implied to be 64.

  void encode    (uint1 *dest, uint4 *src, uint4 length);
  void decode    (uint4 *dest, uint1 *src, uint4 length);
  void MD5Memcpy    (uint1 *dest, uint1 *src, uint4 length);
  void MD5Memset    (uint1 *start, uint1 val, uint4 length);

  uint4  RotateLeft (uint4 x, uint4 n);
  uint4  F           (uint4 x, uint4 y, uint4 z);
  uint4  G           (uint4 x, uint4 y, uint4 z);
  uint4  H           (uint4 x, uint4 y, uint4 z);
  uint4  I           (uint4 x, uint4 y, uint4 z);
  void   FF  (uint4* a, uint4 b, uint4 c, uint4 d, uint4 x,
			    uint4 s, uint4 ac);
  void   GG  (uint4* a, uint4 b, uint4 c, uint4 d, uint4 x,
			    uint4 s, uint4 ac);
  void   HH  (uint4* a, uint4 b, uint4 c, uint4 d, uint4 x,
			    uint4 s, uint4 ac);
  void   II  (uint4* a, uint4 b, uint4 c, uint4 d, uint4 x,
			    uint4 s, uint4 ac);

#endif // __MD5_H__
