/*
 * concord3.c
 *
 * Starter file provided to students for Assignment #3, SENG 265,
 * Fall 2022.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emalloc.h"
#include "seng265-list.h"

#define MAX_WORD_LEN 40
#define MAX_LINE_LEN 100

void print_word(node_t *node, void *arg)
{
    char *format = (char *)arg;
    printf(format, node->text);
}


#ifdef DEBUG

/*
 * Just showing the use of the linked-list routines.
 */

void _demo() {
printf("DEBUG: in _demo\n");
    char *words_german[] = {"Der", "Kater", "mit", "Hut."};
    int   words_german_len = 4;

    char *words_english[] = {"The", "cat", "in", "the", "hat."};
    int   words_english_len = 5;

    node_t *temp_node = NULL;
    node_t *head = NULL;

    int i;

    /* Add the words in German, at the front. */
    for (i = 0; i < words_german_len; i++) {
        temp_node = new_node(words_german[i]);
        head = add_front(head, temp_node);
    }

    /* Add the words in English, at the end. */
    for (i = 0; i < words_english_len; i++) {
        temp_node = new_node(words_english[i]);
        head = add_end(head, temp_node);
    }

    /* Print the list of words. */

    apply(head, print_word, "--> %s\n");

    /* Free up the memory. This is done rather deliberately
     * and manually.  Asserts are liberally used here as they
     * express state that *must* be true if all of the code is
     * correctly working.
     */

    temp_node = head;
    while (temp_node != NULL) {
        assert(temp_node != NULL);
        head = remove_front(head);
        free(temp_node);
        temp_node = head;
    }
   
    assert(head == NULL); 
}

#endif



node_t *read_excl_words(){
    node_t *excl_head = NULL;
    char *buffer;
    size_t buffer_len;
    getline(&buffer, &buffer_len, stdin);
    if(strncmp(buffer, "1\n", buffer_len) == 0){
        printf("Input is version 1, concord3 expected version 2\n");
        exit(0);
    }
    getline(&buffer, &buffer_len, stdin);
    getline(&buffer, &buffer_len, stdin);
    while(strncmp(buffer, "\"\"\"\"\n", buffer_len) != 0){
        char *temp_str = emalloc(sizeof(char)*buffer_len);
        strncpy(temp_str, buffer, buffer_len);
        node_t *temp_node = new_node(temp_str);
        excl_head = add_front(excl_head, temp_node);
        getline(&buffer, &buffer_len, stdin);
    }
    return excl_head;
}

node_t *read_lines(){
    node_t *lines_head = NULL;
    char *buffer;
    size_t buffer_len;
    while(getline(&buffer, &buffer_len, stdin) != -1){
        char *temp_str = emalloc(sizeof(char)*buffer_len);
        strncpy(temp_str, buffer, buffer_len);
        node_t *temp_node = new_node(temp_str);
        lines_head = add_end(lines_head, temp_node);
    }
    return lines_head;
}

void free_lists(node_t *n){
    while(n != NULL){
        node_t *temp = n->next;
        free(n);
        n = temp;
    }
}

int main(int argc, char *argv[]){
    node_t *excl_words = read_excl_words();
    node_t *input_lines = read_lines();

    //read_input(excl_words, input_lines);
    printf("%s", input_lines->text);

    free_lists(excl_words);
    free_lists(input_lines);
/* 
 * Showing some simple usage of the linked-list routines.
 */

#ifdef DEBUG
    _demo();
#endif

    exit(0);
}
