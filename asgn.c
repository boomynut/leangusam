#include <stdio.h>
#include <stdlib.h>
#include "htable.h"
#include "mylib.h"
#include <getopt.h>
#include <time.h>

static void print_info(int freq, char *word) {
    printf("%-4d %s\n", freq, word);
}

int main(int argc, char *argv[]){
    htable h = htable_new(113);
    char word[256];

    /*These to be used elsewhere
     *htable_print(h, print_info, stdout);
     *htable_free(h);*/

    /*getopt variables:
     *Optstring indicates which cases require arguments
     *Option is used for the case */
    const char *optstring = "c:deps:t:h";
    char option;

    /*Timing information start and end*/
    clock_t start, end;
    clock_t start2, end2;
    
    /*File pointer fp to read the filename given as an optarg*/
    FILE *fp;

    int count = 0;

    while ((option = getopt(argc, argv, optstring)) != EOF) {
        switch (option) {
            case 'c':
                fp = fopen(optarg, "r");
                start = clock();
                while (getword(word, sizeof word, stdin) != EOF) {
                    htable_insert(h, word);
                }
                end = clock();
                start2 = clock();
                while (getword(word, sizeof word, fp) != EOF) {
                    if(!htable_search(h, word)){
                        htable_print(h, print_info, stdout);
                        count++;
                    }
                    end2 = clock();
                    fprintf(stderr, "fill time\n", (end-start) / (double)CLOCKS_PER_SEC);
                    fprintf(stderr, "Search Time\n", (end2-start2) / (double)CLOCKS_PER_SEC);
                    fprintf(stderr, "Unknown words: %d\n", count);
                }

             case 'd':

             case 'e':

             case 'p':

             case 's':
             
             case 't':
             
             case 'h':

            default:
                break;
        }
    }
}
