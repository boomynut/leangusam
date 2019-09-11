#include <stdio.h>
#include <stdlib.h>
#include "htable.h"
#include "mylib.h"
/*
int main(void) {
    htable h = htable_new(18143);
    char word[256];
    while (getword(word, sizeof word, stdin) != EOF) {
        htable_insert(h, word);
    }
    htable_print(h, stdout);
    htable_free(h);
    return EXIT_SUCCESS;
 }
*/
int main(void) {
    htable h = htable_new(113);
    char word[256];
    char op;
    /* We must have a space before the %c */
    while (2 == scanf(" %c %255s", &op, word)) {
        if ('+' == op) {
                htable_insert(h, word);
        } else if ('?' == op) {
            printf("%d %s\n", htable_search(h, word), word);
        }
    }
    htable_free(h);
    return EXIT_SUCCESS;
}
