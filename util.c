/**
    @file util.c
    @author Vincent H Lai (vhlai)
    Houses the readMessage and getGlyph functions used in banner.c and image.c
  */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "util.h"
#include "glyph.h"

#define INVALIDCHAR 100 //Error code for an invalid character
#define INVALIDLENGTH 101 //Error code for an input that is too long or too short


int readMessage(char message[MAX_MESSAGE]){
    int counter = 0; //used to count the length of the character
    char ch;
    while ((ch = getchar())!= EOF && ch != '\n'){
        if ((ch < ' ' || ch > '~') && (ch != '\n')){ //check for invalid character error
            return INVALIDCHAR;
        }
        message[counter] = ch;
        counter++;
        if (counter > MAX_MESSAGE){ //check for message too long
            return INVALIDLENGTH;
        }
    }
    if (counter == 0){ //check for message too short (no message)
        return INVALIDLENGTH;
    }
    else {
        return counter;//return length of the message
    }
}

void getGlyph(char ch, short glyph[GLYPH_HEIGHT][GLYPH_WIDTH]){
    for (int row = 0; row < GLYPH_HEIGHT; row++){
        for (int col = 0; col < GLYPH_WIDTH; col++){
            glyph[row][col] = shapes[((ch-' ')*GLYPH_HEIGHT)+row][col];
            //retrives the corresponding pixel intensity value for each pixel in the glyph
        }
    }
}
