#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <string>

#include "base64.h"

using namespace std;

static void
test(unsigned char *encode, unsigned int encodelen,
     const char *decode, unsigned int decodelen)
{
	char *encode_out;;
	unsigned char *decode_out;

	encode_out = (char*) malloc(BASE64_ENCODE_OUT_SIZE(encodelen));
	decode_out = (unsigned char *) malloc(BASE64_DECODE_OUT_SIZE(decodelen));
	assert(encode_out);
	assert(decode_out);

	assert(base64_encode(encode, encodelen, encode_out) == decodelen);
	assert(memcmp(encode_out, decode, decodelen) == 0);
	assert(base64_decode(decode, decodelen, decode_out) == encodelen);
	assert(memcmp(decode_out, encode, encodelen) == 0);

	free(encode_out);
	free(decode_out);
}

// #define PRINT_DEBUG

int
main(void)
{
	test((unsigned char *)"", 0, "", 0);
	test((unsigned char *)"f", 1, "Zg==", 4);
	test((unsigned char *)"fo", 2, "Zm8=", 4);
	test((unsigned char *)"foo", 3, "Zm9v", 4);
	test((unsigned char *)"foob", 4, "Zm9vYg==", 8);
	test((unsigned char *)"fooba", 5, "Zm9vYmE=", 8);
	test((unsigned char *)"foobar", 6, "Zm9vYmFy", 8);

  string in;
  cin>>in;
  unsigned int decodeLen = BASE64_DECODE_OUT_SIZE(in.length());

#ifdef PRINT_DEBUG
  unsigned char* out = new unsigned char[decodeLen + 1];
  out[decodeLen] = 0;
#else
  unsigned char* out = new unsigned char[decodeLen];
#endif

  base64_decode(in.c_str(), in.length(), out);

#ifdef PRINT_DEBUG
  cout<<(char*)out<<endl;
#endif
  
  ofstream file("decode.bin", ios::out | ios::binary);
  file.write((const char*)out, decodeLen);
  file.close();

  delete[] out;

	return 0;
}
