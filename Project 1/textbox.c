/**
    @file textbox.c
    @author Vincent Lai (vhlai)
    This program prints a box of asteriks filled with text taken from input. 
  */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/** Width of each line of text in the box. */
#define LINE_WIDTH 60

/** Symbol used to draw the border around the box. */
#define BORDER '*'

/**
    Prints the input, followed by spaces as padding if the length of the input for the line is less than 60.
    @return 
returns false when EOF is read. Otherwise returns true
  */
bool paddedLine()
{
    //reads the first character in the line
    int ch = getchar();
    
    //checks for EOF
    if (ch == EOF){
        return false;
    }
    
    else{
        //prints left border
        putchar(BORDER);
    //writes the line, will stop printing after printing 60 characters
        for(int x = 0; x < LINE_WIDTH; x++){
            //checks for start of a new line
            if(ch == '\n'){
                putchar(' ');
            }
            //prints character if not at the start of a new line
            else{
                putchar(ch);
                ch = getchar();
            }
        }
        //prints right border and starts a new line
        putchar(BORDER);
        putchar('\n');
        //discards extra characters in a line
        while(ch != '\n'){
            ch = getchar();
        }
        return true;
    }
}

/**
    prints copies of a character, followed by a newline.
    @param ch: the character to be printed
    @param count: number of times to print character ch
  */
void lineOfChars( char ch, int count )
{
    for(int x = 0; x < count; x++){
        putchar(ch);
    }
    putchar('\n');
}

/**
    Prints the input surrounded with asteriks creating a text box.
    @return 0 if program runs succesfully
  */
int main()
{
    //writes the top border, +2 accounts for the extra asteriks needed to match left and right border
    lineOfChars(BORDER, LINE_WIDTH + 2);
    
    while(paddedLine() == true){
        //prints line of text
        paddedLine();
    }
    
    //writes the bottom border
    lineOfChars(BORDER, LINE_WIDTH + 2);
    
    return 0;
}
