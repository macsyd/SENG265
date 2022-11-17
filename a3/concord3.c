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
#include <ctype.h>
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

node_t *get_index_words(node_t *index_words, node_t *lines, node_t *excl){
    node_t *temp_list = lines;
    
    for( ; temp_list != NULL; temp_list = temp_list->next){
        char temp[strlen(temp_list->text)];
        strncpy(temp, temp_list->text, strlen(temp_list->text));
        char *token = strtok(temp, " ");
        while(token != NULL){
            node_t *list = excl;
            int isExcl = 0;
            for( ; list != NULL; list = list->next){
                if(strncmp(token, list->text, strlen(token)) == 0){
                    isExcl = 1;
                    break;
                }
            }
            if(!isExcl){
                index_words = add_inorder(index_words, new_node(token));
            }
            token = strtok(NULL, " ");
        }
    }
    return index_words;
}

node_t *read_excl_words(){
    node_t *excl_head = NULL;
    char *buffer = emalloc(sizeof(char)*MAX_LINE_LEN);
    //char *buffer;
    size_t buffer_len;
    getline(&buffer, &buffer_len, stdin);
    if(strncmp(buffer, "1\n", buffer_len) == 0){
        printf("Input is version 1, concord3 expected version 2\n");
        exit(0);
    }
    getline(&buffer, &buffer_len, stdin);
    getline(&buffer, &buffer_len, stdin);
    while(strncmp(buffer, "\"\"\"\"\n", buffer_len) != 0){
        //char *temp_str = emalloc(sizeof(char)*buffer_len);
        //strncpy(temp_str, buffer, buffer_len);
        //temp_str[strlen(temp_str)-1] = '\0';
        buffer[strlen(buffer)-1] = '\0';
        node_t *temp_node = new_node(buffer);
        excl_head = add_front(excl_head, temp_node);
        getline(&buffer, &buffer_len, stdin);
    }
    free(buffer);
    return excl_head;
}

node_t *read_lines(){
    node_t *lines_head = NULL;
    //char *buffer;
    char *buffer = emalloc(sizeof(char)*MAX_LINE_LEN);
    size_t buffer_len;
    while(getline(&buffer, &buffer_len, stdin) != -1){
        //char *temp_str = emalloc(sizeof(char)*buffer_len);
        //strncpy(temp_str, buffer, buffer_len);
        //temp_str[strlen(temp_str)-1] = '\0';
        buffer[strlen(buffer)-1] = '\0';
        node_t *temp_node = new_node(buffer);
        lines_head = add_end(lines_head, temp_node);
        
    }
    free(buffer);
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
    node_t *index_words = NULL;
    index_words = get_index_words(index_words, input_lines, excl_words);
    
    node_t *temp_list = input_lines;
    for( ; temp_list != NULL; temp_list = temp_list->next){
        //printf("%s\n", temp_list->text);
        //index_words = get_index_words(index_words, input_lines, excl_words);
        //printf("%s\n", index_words->text);
    }
    //printf("%s", input_lines->text);
    //printf("%s", index_words->text);
    printf("--\n");
    temp_list = index_words;
    for( ; temp_list != NULL; temp_list = temp_list->next){
        printf("%s\n", temp_list->text);
    }
    free_lists(excl_words);
    free_lists(input_lines);
    free_lists(index_words);
/* 
 * Showing some simple usage of the linked-list routines.
 */

#ifdef DEBUG
    _demo();
#endif

    exit(0);
}
