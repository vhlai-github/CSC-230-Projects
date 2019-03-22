/**
    @file md5.c
    @author Vincent H Lai (vhlai)
    Main implementation file for md5.c. Also includes F and G functions, and MD5 iteration.
  */

#include "md5.h"
#include "buffer.h"
#include <stdio.h>

/* Mechanism to conditionally expose static functions to other components.  For
   production, we can make make them static, but for testing we can disable
   the static keyword and expose functions to the test driver. */
#ifdef TESTABLE
#define test_static
#else
#define test_static static
#endif

/** Within each iteration, how many bits left do we rotate the a value? */
static int shift[ 64 ] =
  { 7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
    5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
    4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
    6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21 };

/** Constants, to mix in some random-looking bits during the MD5
    calculation.  These are computed from the sin() function.  They're
    examples of what might be called "Nothing-Up-My-Sleeve"
    numbers. */
static unsigned int noise[ 64 ] =
  { 0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
    0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
    0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
    0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
    0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
    0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
    0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
    0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
    0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
    0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
    0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
    0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
    0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391 };

void initState( MD5State *state ){
    state->A = 0x67452301;
    state->B = 0xefcdab89;
    state->C = 0x98badcfe;
    state->D = 0x10325476;
}

void padBuffer( Buffer* b){

    int oLen = (b->len)*BYTE_BITS;

    appendBuffer(b, 0x80);

    int pad = (b->len)%MD5_BLOCK;

    pad = MD5_BLOCK-pad;

    if (pad > BYTE_BITS){

        for (int x = pad; x > BYTE_BITS; x--){
            appendBuffer(b, 0x00);
            pad--;
        }
    }

    char extract;

    for (int x = pad; x > 0; x--){
        extract = 0xFF & oLen;
        appendBuffer(b, extract);
        oLen = oLen >> BYTE_BITS;
        pad--;
    }

}

void printBytes(unsigned int val ){
    for (int i = 0; i < 4; i++){
        printf("%02X", val & 0xff);
        val = val >> BYTE_BITS;
    }
}

/**
   The next 4 functions are different iterations of the F functions used in
each iteration of the hash algorithm.
    @param
unsigned char b, c, d: the values of MD5State b, c, and d used to perform the function.
    @return
unsigned int func: the calculated value to add to the hash state A.
  */
test_static unsigned int fVersion0( unsigned int b, unsigned int c, unsigned int d){
    unsigned int func;
    func = (b&c) | (~b & d);
    return func;
}

test_static unsigned int fVersion1( unsigned int b, unsigned int c, unsigned int d){
    unsigned int func;
    func = (b&d) | (c & ~d);
    return func;
}

test_static unsigned int fVersion2( unsigned int b, unsigned int c, unsigned int d){
    unsigned int func;
    func = (b^c^d);
    return func;
}

test_static unsigned int fVersion3( unsigned int b, unsigned int c, unsigned int d){
    unsigned int func;
    func = c^ (b|~d);
    return func;
}
/**
   The next 4 functions are different iterations of the G functions used to find the index
of the data block to add to the hash state a.
    @param
int idx: the current iteration of the has algorithm
    @return
int idx, i: the calculated index to use.
  */
test_static int gVersion0( int idx ){
    return idx;
}

test_static int gVersion1( int idx ){
    int i = (5*idx+1)%16;
    return i;
}

test_static int gVersion2( int idx ){
    int i = (3*idx+5)%16;
    return i;
}


test_static int gVersion3( int idx ){
    int i = (7*idx)%16;
    return i;
}
/**
   Implements a left bit rotation.
    @param
unsigned int value: the value to rotate
    @param
int s: the amount of bits to rotate
    @return
unsigned int new: the rotated value
  */
test_static unsigned int rotateLeft( unsigned int value, int s ){
    unsigned int new = value;
    int right = STATE_BITS - s;
    for(int i = 0; i < right; i++){
        new = new >> 1;
    }
    for (int i = 0; i < s; i++){
        value = value << 1;
    }
    new = new | value;

    return new;
}

/**
   Array of pointers to the F functions. Takes parameters for F functions and
passes it to the appropriate F functions depending on the round
    @param
unsigned char b, c, d: the values of MD5State b, c, and d used to perform the function.
    @return
unsigned int func: the calculated value to add to the hash state A.
  */
unsigned int (*fFunc[4]) (unsigned int b, unsigned int c, unsigned int d);
/**
   Array of pointers to the G Functions. Takes parameters for G functions and
passes it to the appropriate G function based on the round.
    @param
int idx: the current iteration of the has algorithm
    @return
int idx, i: the calculated index to use.
  */
int (*gFunc[4]) (int idx);
/**
   A single iteration of the hash algorithm.
    @param
unsigned int data: the current 64 byte block converted to 16 ints.
    @param
unsigned int a, b, c, d: the current values of the MD5State, passed as pointeres to local variables in MD5Block
    @param
int i: the number of the current iteration
  */

test_static void md5Iteration( unsigned int data[ 16 ], unsigned int *a, unsigned int *b, unsigned int *c, unsigned int *d, int i ){


    int round = i/16;

    fFunc[0] = fVersion0;
    fFunc[1] = fVersion1;
    fFunc[2] = fVersion2;
    fFunc[3] = fVersion3;

    gFunc[0] = gVersion0;
    gFunc[1] = gVersion1;
    gFunc[2] = gVersion2;
    gFunc[3] = gVersion3;

    *a = *a+(fFunc[round]) (*b, *c, *d);
    *a = *a+ data[(gFunc[round]) (i)];

/*
    if (i < 16){
        *a = *a + fVersion0(*b, *c, *d);
        *a = *a + data[gVersion0(i)];
    }

    else if(i < 32){
        *a = *a + fVersion1(*b, *c, *d);
        *a = *a + data[gVersion1(i)];
    }

    else if(i < 48){
        *a = *a + fVersion2(*b, *c, *d);
        *a = *a + data[gVersion2(i)];
    }

    else {
        *a = *a + fVersion3(*b, *c, *d);
        *a = *a + data[gVersion3(i)];
    }
 */

    *a = *a + noise[i];

    unsigned int tempVal = *a;

    *a = rotateLeft(tempVal, shift[i]);

    *a = *a + *b;

    unsigned int temp = *d;
    *d = *c;
    *c = *b;
    *b = *a;
    *a = temp;
}


void md5Block( unsigned char data[ MD5_BLOCK ], MD5State *state ){
    unsigned int a = state->A;
    unsigned int b = state->B;
    unsigned int c = state->C;
    unsigned int d = state->D;

    for (int i = 0; i < MD5_BLOCK; i++){
        md5Iteration((unsigned int*)data , &a, &b, &c, &d, i);
    }

    state->A += a;
    state->B += b;
    state->C += c;
    state->D += d;
}