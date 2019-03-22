/**
    @file banner.c
    @author Vincent H Lai (vhlai)
    Scrolls a banner down the console based on input taken from input.
  */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "util.h"
#include "glyph.h"

//Wait time between printed lines, used with usleep
#define WAIT 27778

//Symbols that correspond to intensity
#define intensity0 0
#define intensity1 1
#define intensity2 2
#define intensity3 3
#define intensity4 4
#define intensity5 5
#define intensity6 6
#define intensity7 7
#define intensity8 8
#define intensity9 9

/**
    Retrives a glyph and scrolls the glyph
    @param
sym the symbol to be converted and scrolled
  */
void scrollGlyph(char sym){
    short glyph[GLYPH_HEIGHT][GLYPH_WIDTH];//Contains the glyph
    getGlyph(sym, glyph); //Calls get glyph to get the glyph for the passed character
    for (int line = 0; line < GLYPH_WIDTH; line++){
        for (int ch = GLYPH_HEIGHT-1; ch >= 0 ; ch--){
            //if-else block replaces intensity values with symbols per intensity
            if (glyph[ch][line] == intensity0){
                glyph[ch][line] = ' ';
            }
            else if (glyph[ch][line] == intensity1){
                glyph[ch][line] = '.';
            }
            else if (glyph[ch][line] == intensity2){
                glyph[ch][line] = ':';
            }
            else if (glyph[ch][line] == intensity3){
                glyph[ch][line] = '-';
            }
            else if (glyph[ch][line] == intensity4){
                glyph[ch][line] = '=';
            }
            else if (glyph[ch][line] == intensity5){
                glyph[ch][line] = '+';
            }
            else if (glyph[ch][line] == intensity6){
                glyph[ch][line] = '*';
            }
            else if (glyph[ch][line] == intensity7){
                glyph[ch][line] = '#';
            }
            else if (glyph[ch][line] == intensity8){
                glyph[ch][line] = '%';
            }
            else if (glyph[ch][line] == intensity9){
                glyph[ch][line] = '@';
            }
            putchar(glyph[ch][line]); //Prints the glyph
        }
        printf("\n"); //Starts a new line
        usleep(WAIT); //Wait command creating the "scrolling" effect
    }
}
/**
    The main program. Uses retrives input and scrolls each character as a glyph
    @return
    Success or Error Code
**/
int main(){
    char message[MAX_MESSAGE]; //create an array that will contain the message
    int length = readMessage(message); //calls readMessage to read a message from input. Length is the length of the input
    if (length > MAX_MESSAGE){ //Will return an error message if needed and stop the program
        return length;
    }
    for (int ch = 0; ch < length; ch++){ //otherwise, continue scrolling the glyph
        scrollGlyph(message[ch]);
    }
}