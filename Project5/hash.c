/**
    @file hash.c
    @author Vincent H Lai (vhlai)
    Main program file for Project 5. Calls on functions from md5.c and buffer.c
    to calculate the hash value given an input file.
  */


#include "md5.h"
#include "buffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define BLOCK_SIZE 64

/**
    Function to print error message in case of invalid arguments
  */
static void usage()
{
  fprintf( stderr, "usage: hash <filename>\n" );
  exit( EXIT_FAILURE );
}

/**
    Main function of the program. First checks arguments for validity.
Then creates the buffer and initializes the MD5 State. Calls on padBuffer
and initState to pad the Buffer, then initialize the state. Function then passes
64 byte blocks of the buffer to MD5Block for processing. Program then uses printBytes
to print the resulting hash, then frees the MD5State and the buffer.
    @param
int argc: number of command line arguments recieved.
    @param
*char argv: an array of the command line arguments.
    @return
int: the success value of the program. 1 if the buffer was empty after reading, 0 if program runs successfuly
  */
int main (int argc, char *argv[]){

    if ( argc != 2 )
    usage();

    Buffer *buff = readFile(argv[ 1 ]);

    MD5State *state = (MD5State *)malloc(sizeof(MD5State));

    if (buff == NULL){
        return EXIT_FAILURE;
    }

    padBuffer(buff);
    initState(state);

    int blocks = (buff->len)/BLOCK_SIZE;
    unsigned char currBlock[BLOCK_SIZE];


    for (int x = 0; x < blocks; x++){
        for (int y = 0; y < BLOCK_SIZE; y++){
            currBlock[y] = buff->data[BLOCK_SIZE*x+y];
        }
        md5Block(currBlock, state);
    }

    printBytes(state->A);
    printBytes(state->B);
    printBytes(state->C);
    printBytes(state->D);
    printf("\n");

    free(state);
    freeBuffer(buff);

    return EXIT_SUCCESS;
}