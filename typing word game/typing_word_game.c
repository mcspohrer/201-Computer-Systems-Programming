/*Matthew Spohrer
ID# 958566579
CS201 Assignment 1*/

/*randomly chooses a word from the phrase 
 * "The quick brown fox jumps over the lazy dog"
 * for the user to enter, tallies the total time 
 * for the user to enter all the words in*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#define SIZE 9

int main(){
    //initializes the char pointer to an array of chars 
    //containing the words
    char * words[] = {
        "The", "quick", "brown", "fox",
        "jumps", "over", "the", "lazy", "dog"
    }; 
    

    //welcomes user and explins the game
    printf("\nWelcome to the typatron 5000. This game measures how "
            "quickly you can type in randomly selected words from "
            "\nthe phrase \"lazy The dog quick the fox brown over "
            "jumps\"....er, I meant \"The quick brown fox jumps "
            "over the lazy dog\". \nBe sure to type your answers "
            "in exactly as they appear on the screen,"
            " caps and all!\n\n");

    //creates a timeval object to be used to seed srand and to manage
    //the start/stop/differences for the times 
    struct timeval start, stop, difference;

    //gets the start time and seeds rand()
    gettimeofday(&start, NULL);
    srand(start.tv_usec);

    int rand_i = 0;
    int iterations = 0;
    char user_word[SIZE];

    for (int last=SIZE - 1; last >= 0; --last)
    {
        //set rand_i using the rand function then reducing the size it can be
        //by 1 per iteration
        rand_i = rand() % (SIZE - iterations);
        ++iterations;

        //stops when the user enters the correct data
        while (strncmp(words[rand_i], user_word, strlen(words[rand_i])) != 0) 
        {
            printf("\nYour Word:%6s \n", words[rand_i]);
            scanf("%s", user_word);
            //compares what was entered to the word, printing if not the same
            if (strncmp(words[rand_i], user_word, strlen(words[rand_i])) != 0)  
            {
                printf("\nBAAAANNNNNNNN (to be read as an annoying buzzer), "
                       "please try again and remember, enter it EXACTLY as "
                       "it is shown!");
            }
        }
        //reorganizes the array to exclude the most recently entered word
        words[rand_i] = words[last]; 
    }

    //stops the time then subtracts the times
    gettimeofday(&stop, NULL);
    timersub(&stop, &start, &difference);

    printf("\nDonesoes! Good job! Your time was %ld sec and %ld usecs.\n\n",
            difference.tv_sec, difference.tv_usec);
    
    //returns 0
    return 0;
}
