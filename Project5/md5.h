/**
    @file md5.h
    @author Vincent H Lai (vhlai)
    Header file for MD5
  */

#ifndef _MD5_H_
#define _MD5_H_

#include "buffer.h"

/** Number of bytes in a block used int he MD5 calculation. */
#define MD5_BLOCK 64

#define BYTE_BITS 8
#define STATE_BITS 32

/** Representation for the state of the MD5 computation.  It's just 4
    unsigned 32-bit integers. Client code can create an instance
    (statically, on the stack or on the heap), but initState() needs
    to initialize it before it can be used. */
typedef struct {
  /** Field A from the MD5 state.  This comment and the ones below
      aren't particularly meaningful, because there isn't really a
      particular mening for each of these fields. */
  unsigned int A;

  /** Field B from the MD5 state.  */
  unsigned int B;

  /** Field B from the MD5 state.  */
  unsigned int C;

  /** Field B from the MD5 state.  */
  unsigned int D;
} MD5State;
/**
   Sets the initial state of the MD5State
    @param
*MD5State state: the State to initialize.
  */
void initState( MD5State *state );
/**
   Pads the Buffer based on the padding algorithm
    @param
Buffer b: the buffer to pad.
  */
void padBuffer( Buffer* b);
/**
   Processes a 64 byte block of the buffer.
    @param
unsigned char data[64]: the block of dat to process.
    @param
MD%State *state: the current MD5State
  */
void md5Block( unsigned char data[ MD5_BLOCK ], MD5State *state );
/**
   prints the bytes of a value as hex digits. Used on each variable
of MD5State to print out the whole hash state.
    @param
unsigned int val: the value to print
  */
void printBytes(unsigned int val );


#endif
