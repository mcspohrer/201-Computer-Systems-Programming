/*Matthew Spohrer
CS201 Program 1
Student id : 958566579*/
#define _BSD_SOURCE
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

//gets the size of the statement...i'm not sure for what, but it does it
#define LENGTH sizeof("Thequickbrownfoxjumpsoverthelazydog") 
#define ALENGTH 9 //number of indices in the array 
#define WLENGTH 6 //size of the largest word 


/*scans in the word from the user and compares it to the word needing
to be typed. Returns 'n' if typed incorrectly and 'y' if completed
successfully*/
char play(char * base_array[])
{
    char word[WLENGTH];
    for (int i = 0; i < ALENGTH; ++i) {
        printf("\nYour word is: %s\n", base_array[i]);
        scanf("%s",word);
        if (strncmp(word,base_array[i], strnlen((base_array[i]), WLENGTH)) == 0) {
            printf("\nGood Job!\n");
        } else {
            printf("\nBAAAAAHHHHNNN (to be read as a buzzer)"
                "\nUnfortunately you have to start over!\n");
            return 'n';
        }
    }
    return 'y';
}

//populates the base array from the sentence
void pop_base(char ** base_array)
{
    int base_i = 0;
    char * word;
    char * sentence;
    int size = sizeof("The quick brown fox jumps over the lazy dog");
    sentence =(char*) malloc (sizeof(char) * size +1);
    assert(sentence);
    strncpy(sentence, "The quick brown fox jumps over the lazy dog", size+1);
    word = strtok(sentence, " ");
    while (base_i < ALENGTH) {
        base_array[base_i] = (char*) malloc (sizeof(char) * strnlen(word,WLENGTH));
        assert(base_array[base_i]);
        strncpy(base_array[base_i], word, strnlen(word, WLENGTH));
        base_array[base_i][strnlen(word, WLENGTH) + 1] = '\0';
        ++base_i;
        word = strtok(NULL, " ");
    }
    free (sentence);
    return;
}

//populates the random array using the base array
void pop_rand(char ** base_array)
{
    int rand_i = 0;
    char * temp = NULL;

    for (int i = (ALENGTH - 1); i >= 0; --i) {
        rand_i = rand() % (i + 1);
        temp = base_array[rand_i];
        base_array[rand_i] = base_array[i];
        base_array[i] = temp;
    }
         
    return;
}

int
main() {
    char correct;
    char ** base_array;
    struct timeval tstart, tend, tdiff;
    srand(getpid());

    base_array = (char**)malloc(sizeof(char*) * 9);
    assert(base_array);
    pop_base(base_array);
    pop_rand(base_array);

//intro to the program
    printf ("\nA word will randomly appear on your screen ad wait" 
        "for you to type it. Once finished typing");
    printf ("\njust hit enter and I'll do the rest. Be sure to type"
        " it exactly as it is shown!\n");

//gets the times and calls the play function
    gettimeofday(&tstart, NULL); 
    correct = play(base_array);		
    gettimeofday(&tend, NULL);
    timersub(&tend, &tstart, &tdiff);
    if (correct == 'y') {
        printf("\nCongrats! You finished! And your time was :\n:");
        printf ("%ld secs and %ld usecs\n", tdiff.tv_sec, tdiff.tv_usec);
	}

    for (int i = (ALENGTH - 1); i >= 0; --i) 
        free (base_array[i]);
    free (base_array);
    return 0;
}

