#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "htable.h"
#include "mylib.h"

struct htablerec {
    int capacity;
    int num_keys;
    int *frequencies;
    char **key;
    hashing_t method;
};

htable htable_new(int capacity){
    int i;
    htable result = emalloc(sizeof * result);
    result->capacity = capacity;
    result->num_keys = 0;
    result->frequencies = emalloc(sizeof(int) * capacity);
    result->key = emalloc(sizeof(result->key[0]) * capacity);
    for (i = 0; i < capacity; i++){
        result -> frequencies[i] = 0;
        result -> key[i] = NULL;
    }
    return result;
}

static unsigned int htable_step(htable h, unsigned int i_key){
    return 1 + (i_key % (h->capacity - 1));
}

static unsigned int htable_word_to_int(char *word) {
    unsigned int result = 0;
    while (*word != '\0') {
        result = (*word++ + 31 * result);
    }
    return result;
}

int htable_insert(htable h, char *str){
    unsigned int index;
    int count;
    int step;

    index = htable_word_to_int(str) % h->capacity;
    step = htable_step(h, index);

    count = 0;
    while(count < h->capacity){
        if (h->key[index] == NULL){
            h->key[index] = emalloc((strlen(str) + 1) * sizeof h->key[0][0]);
            strcpy(h->key[index], str);
            h->frequencies[index] = 1;
            h->num_keys++;

            return 1;
        } else if (strcmp(h->key[index], str) == 0){
            h->frequencies[index]++;
            return h->frequencies[index];
        }
        index = (index + step) % h->capacity;
        count++;
    }
    return 0;
}

int htable_search(htable h, char *str){
    int step;
    int collisions = 0;
    int position;

    position = htable_word_to_int(str) % h->capacity;
    step = htable_step(h, position);
    while(h->key[position] != NULL && strcmp(h->key[position], str) != 0 && collisions < h->capacity){
        position = (position + step) % h->capacity;
        collisions++;
    }
    if(collisions == h->capacity) {
        return 0;
    }else{
        return h->frequencies[position];
    }
}



void htable_print(htable h, void f(int freq, char *word), FILE *stream){
    int i;
    for(i = 0; i < h->capacity; i++ ){
        if (h->key[i] != NULL){
            f(h->frequencies[i], h->key[i]);
            fprintf(stream, "%d %s\n", h->frequencies[i], h->key[i]);
        }
    }
}

void htable_free(htable h){
    free(h->key);
    free(h->frequencies);
    free(h);
}
