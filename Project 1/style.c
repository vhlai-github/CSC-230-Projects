/**
    @file style.c
    @author Vincent H Lai (vhlai)
    This is an excercise in correcting style for CSC230.
*/
#include <stdio.h>
#include <stdlib.h>

//Line character limit

#define SEVENTY 72

/**
    prints a random "word" made of random lowercase letters
    @param 
x: indicates the length of the word
*/
void printWord( int x )
{
    for ( int i = 0; i < x; i++ )
    {
            // Print a random lower-case letter.
            printf( "%c", 97 + rand() % 26 );
    }
}

/**
    prints a line made of random "words"
	@return 
number of words printed in the line
*/
int printLine() 
{
    /**
        determines position in the line
        count: number of words in line
        pos: position in the line while prining
        space: indicates a space in the line
    */
    int count = 0, pos = 0, space = 0;
	
    //Choses a random length for the word which is fed into printWord
	
    int len = 1 + rand() % 10;
    // Print a line of words up to a limited length.
    while ( pos + len + space < SEVENTY ) {
        if ( space > 0 ) {
            printf( " " );
            }
        printWord( len );
        pos += len + space;
        len = 1 + rand() % 10;
        space = 1;
        count += 1;
	}
    printf( "\n" );
    return count;
}
/** 
    Prints a paragraph, or a number of lines of random words.
    @param 
n number of lines in the paragraph
    @return 
number of words printed in the paragraph
*/
int printParagraph( int n )
{
    //number of words in paragraph
    int total = 0;
    for ( int i = 0; i < n; i++ )
    total += printLine();
    return total;
}
/**
    main method: prints a paragraph with 10 lines
    @return 
success, exit program
*/
int main()
{
    int w=printParagraph(10);
    printf("Words: %d\n",w);
    return 0;
}