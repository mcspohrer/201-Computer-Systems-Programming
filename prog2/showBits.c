/*Matthew Spohrer
 * ID - 958566579
 * CS 201 Section 4 
 * Assignment 2*/

/*This program takes in two hex digits from the command 
 * line, converts them to longs, bitwise &'s them, converts
 * the result to binary and casts to different types of 
 * variable types.*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int SIZE=31;//the size of number in bits

int main(int argc, char * argv[]) 
{
    //checks the number of arguments entered
    if(argc != 3) 
    {
        printf("\n\nPlease provide two hex numbers as arguments"
            " to the program instead of wasting my time with "
            "not using me correctly!\n\n");
        return 1;
    }

    //converts the two arguments to decimal and bitwise &'s
    //bits
    unsigned long result = strtol(argv[1], NULL, 16) & 
        strtol(argv[2], NULL, 16);

    //the mask (I think) used to compare to the decimal 
    //being converted
    unsigned int mask = 1;

    //prints the binary version of the result (I think)
    printf("Bits ");
    for (int i = 0; i <= SIZE; ++i) 
    {
        if((result & mask) == mask){
            printf("%d, ", i);
        }
        mask = mask<<1;
    }
    printf("in common.\n");
        
    //prints result as hex, signed int and unsigned long
    printf("Hexadecimal: %lx, Signed: %d, Unsigned: "
            "%lu\n\n", result, (signed int) result, result);

    return 0;
}

                
