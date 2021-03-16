/*Matthew Spohrer
 * ID - 958566579
 * CS 201 Section 4 
 * Assignment 2*/

//this program takes in a number of ints ranging from 0 
//to 15, switches the nth binary digit to 1 and prints the
//binary 

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

//15 is the MSD of a 16 bit binary
#define MAX 15
//decimal equivalent of having the 15th binary bit a 1
#define BINARY_15 32768
int main(int argc, char * argv[])
{

    //number is the number represented by the binary bits
    //being turned on by the command line args
    unsigned short number = 0;
    //temp is a command line arg converted to a unsigned
    //long via strtol
    unsigned short temp = 0;
    //mask is used to check which binary bits are turned on
    //for printing, it's set to the decimal with only the 
    //15th binary bit a 1
    unsigned short mask = BINARY_15;
    
    //checks that there are entries
    if(argc == 1) 
    {
        printf("\ntsk tsk...I need some nums between 0 and 15"
                " to work properly, you tricky devil!\n");
        return 1;
    }

    /*converts the command line args to unsigned longs
    assert they are less than or equal to 15 (negatives
      have been converted to unsigned longs)
    clears the bits at the specified index
    then turns on the specified bit */
    for(int i = 1; i < argc; ++i)
    {
        temp = strtol(argv[i], NULL, 10);
        if(temp > MAX)
        {
            printf("\nDon't you have anything better to do "
                    "than to try to make me not work? I need"
                    " a number between 0 and 15 and you knew "
                    "that!\n\n");
            return 2;
        }
        assert(temp <= MAX);
        number &= ~(1<<temp);
        number |= (1<<temp);
    }

    /*Compares the MSD using mask, prints the appropriate
     * binary bit, then bitshifts mask*/
    putchar('\n');
    for(int i = MAX; i >= 0; --i) 
    {
        if((mask & number) == mask) putchar('1');
        else putchar('0');
        if(i%4 == 0) putchar(' ');
        mask = (mask>>1); 
    }
    putchar('\n');
    putchar('\n');

    return 0;
}

