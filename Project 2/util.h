/**
    @file util.h
    @author Vincent H Lai (vhlai)
    Header file for util.c
  */
#include "glyph.h"
#define MAX_MESSAGE 60 //Maximum length of Message to be used in util.c
/**
    Reads input from standard input and places it in a character array (without null terminator)
    @param
message: an array passed by reference that will contain the message
**/
int readMessage(char[]);
/**
    Retrieves the glyph (by intensity) for a character and puts it into an array
    @param
ch: the character to be converted
    @param
glyph: an array passed by referemce that contains pixels of the glyph
  */
void getGlyph(char, short[][GLYPH_WIDTH]);