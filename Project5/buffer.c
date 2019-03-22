/**
    @file bufferc
    @author Vincent H Lai (vhlai)
    Main implementation file for buffer functions
  */

#include "md5.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define START_CAP 3

Buffer *makeBuffer(){
    Buffer *b = (Buffer*)malloc(sizeof(Buffer));

    b->len = 0;
    b->cap = START_CAP;

    b->data = (unsigned char *)malloc( (b->cap)*sizeof(char));

    return b;
}

void appendBuffer(Buffer *b, unsigned char byte){

    b->data[(b->len)] = byte;

    (b->len)++;

    if ((b->len) == (b->cap)){
        b->cap *= 2;
        b->data = (unsigned char*)realloc((b->data), (b->cap) * sizeof(char));
    }
}

void freeBuffer (Buffer *b){
    free(b->data);
    free(b);
}

Buffer *readFile(const char *filename){

    FILE *fp = fopen( filename, "r" );
    if ( !fp ) {
        fprintf( stderr, "Can't open file: %s\n", filename);
        return NULL;
    }

    Buffer *buffer = makeBuffer();
    char ch;

    while (fscanf(fp, "%c", &ch) == 1){ //might need to change this check for EOF
        appendBuffer(buffer, ch);
    }

    return buffer;
}
