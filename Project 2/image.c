/**
    @file image.c
    @author Vincent H Lai (vhlai)
    Creates a PGM image of text based on input.
  */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "util.h"
#include "glyph.h"

#define MAXINTENSITY 9


/**
    Writes the image based on an array bassed by main
    @param
rows: rows in the picture
    @param
cols: columns in the picture
    @param
img: Array representing the image
  */
void writeImage(int rows, int cols, short img[rows][cols]){
    printf("%s\n", "P2"); //Announces format of the image
    printf("%d %d\n", cols, rows); //Declares dimensions of the image
    printf("%d\n", MAXINTENSITY); //Declares max intensity
    for (int row = 0; row < rows; row++){
        for (int col = 0; col < cols; col++){
            printf("%d", img[row][col]);//Prints the intensity value of each pixel
            if (col < cols-1){
                //places a space after every intensity value except after the last intensity value for every row.
                putchar(' ');
            }
        }
    putchar('\n');
    }
}
/**
    The main program.
    uses readMessage() to read input.
    Each character is converted into a glyph and put into a large array that contains intensity values for every pixel in the whole image.
    @return
    success/error code
  */
int main(){
    char message[MAX_MESSAGE]; //array that will store the message from input
    int length = readMessage(message); //calls read message to read a message, records the length of the message
    short imgArray[GLYPH_HEIGHT][GLYPH_WIDTH*length]; //creates the array corresponding to the size of the message
    if (length > MAX_MESSAGE){//returns error code if needed, ends the program
        return length;
    }
    for (int ch = 0; ch < length; ch++){//places the glyphs in the correct spot in the image array
        short glyph[GLYPH_HEIGHT][GLYPH_WIDTH];
        getGlyph(message[ch], glyph);
        for (int row = 0; row < GLYPH_HEIGHT; row++){
            for (int pixel = 0; pixel < GLYPH_WIDTH; pixel++){
                imgArray[row][ch*GLYPH_WIDTH+pixel] = glyph[row][pixel];
            }
        }
    }
    writeImage(GLYPH_HEIGHT, GLYPH_WIDTH*length, imgArray);
    //calls image array to translate the glyph into and image
}