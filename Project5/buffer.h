/**
    @file buffer.h
    @author Vincent H Lai (vhlai)
    Header file for buffer
  */
#ifndef _BUFFER_H_
#define _BUFFER_H_

/** Representation for the contents of an input file, copied to memory. */
typedef struct {
  /** Array of bytes from the file (not a string). */
  unsigned char *data;

  /** Number of currently used bytes in the data array. */
  unsigned int len;

  /** Capacity of the data array (it's typically over-allocated. */
  unsigned int cap;
} Buffer;

/**
   Dynamically allocates an empty Buffer and stores it.
    @return
Buffer: the newly allocated buffer
  */
Buffer *makeBuffer();
/**
   Appends a byte to the bbuffer
    @param
Buffer *b: pointer to the buffer to append to
    @param
unsigned char byte: the valiue of the byte to append
  */
void appendBuffer( Buffer *b, unsigned char byte );

/**
   Frees the Buffer. First freeing the data block, then the other struct fields.
    @param
Buffer *b: pointer to the buffer to clear.
  */
void freeBuffer( Buffer *b );
/**
   Reads a file into a new Buffer
    @param
const char *filename: the file to read from
    @return
returns the buffer after reading is done.
  */
Buffer *readFile( const char *filename );
#endif
