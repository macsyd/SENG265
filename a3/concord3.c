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
#define OUTPUT_LINE_LEN 60
#define OUTPUT_WORD_INDEX 30
#define SPACE 1

void print_word(node_t *node, void *arg)
{
    char *format = (char *)arg;
    printf(format, node->text);
}


#ifdef DEBUG


 /* Just showing the use of the linked-list routines.*/
 

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

 //ctype.h   /* Print the list of words. */

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

void free_lists(node_t *n){
    while(n != NULL){
        node_t *temp = n->next;
        free(n);
        n = temp;
    }
}

node_t *get_index_words(node_t *lines, node_t *excl){
    node_t *index_words = NULL;
    node_t *temp_list = lines;
    for( ; temp_list != NULL; temp_list = temp_list->next){
        char temp[MAX_LINE_LEN];
        strncpy(temp, temp_list->text, MAX_LINE_LEN);
        char *token = strtok(temp, " ");
        while(token != NULL){
            node_t *list = excl;
            int isExcl = 0;
            for( ; list != NULL; list = list->next){
                if(compare(token, list->text) == 0){
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
    size_t buffer_len;
    getline(&buffer, &buffer_len, stdin);
    if(strncmp(buffer, "1\n", buffer_len) == 0){
        printf("Input is version 1, concord3 expected version 2\n");
        exit(0);
    }
    getline(&buffer, &buffer_len, stdin);
    getline(&buffer, &buffer_len, stdin);
    while(strncmp(buffer, "\"\"\"\"\n", buffer_len) != 0){
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
    char *buffer = emalloc(sizeof(char)*MAX_LINE_LEN);
    size_t buffer_len;
    while(getline(&buffer, &buffer_len, stdin) != -1){
        buffer[strlen(buffer)-1] = '\0';
        node_t *temp_node = new_node(buffer);
        lines_head = add_end(lines_head, temp_node);
        
    }
    free(buffer);
    return lines_head;
}

void print_front(node_t *list){
    char front_line[OUTPUT_WORD_INDEX];
    for(int i = 0; i < OUTPUT_WORD_INDEX; i++){
        front_line[i] = ' ';
    }
    front_line[OUTPUT_WORD_INDEX-1] = '\0';
    int index = OUTPUT_WORD_INDEX;
    for(node_t *temp = list; temp != NULL; temp = temp->next){
        if(index - strlen(temp->text) - SPACE >= 10){
	    strncpy(&front_line[index-1-SPACE-strlen(temp->text)], temp->text, strlen(temp->text));
            index -= SPACE + strlen(temp->text);
        } else {
	    break;
        }
    }
    free_lists(list);
    printf("%s", front_line);
}

void print_line(char *word, char *line){
    char output_word[strlen(word)+1];
    node_t *front_words = NULL;
    char temp[MAX_LINE_LEN];
    strncpy(temp, line, MAX_LINE_LEN);
    char *token = strtok(temp, " ");
    while(token != NULL){
        if(compare(word, token) == 0){
            int i;
            for(i = 0; i < strlen(token); i++){
                output_word[i] = toupper(token[i]);
            }
            output_word[i] = '\0';
            break;
        } else {
            front_words = add_front(front_words, new_node(token));
        }
        token = strtok(NULL, " ");
    }
    print_front(front_words);
    printf("%s", output_word);
    int index = OUTPUT_WORD_INDEX + strlen(word);
    token = strtok(NULL, " ");
    while(token != NULL){
        if(index + SPACE + strlen(token) <= OUTPUT_LINE_LEN){
            printf(" %s", token);
            index += SPACE + strlen(token);
        } else {
            break;
        }
        token = strtok(NULL, " ");
    }
    printf("\n");
}

void output_lines(node_t *list, void *lines){
    char *word = list->text;
    for(node_t *temp_list = lines; temp_list != NULL; temp_list = temp_list->next){
        char temp[MAX_LINE_LEN];
        strncpy(temp, temp_list->text, MAX_LINE_LEN);
        char *token = strtok(temp, " ");
        while(token != NULL){
            if(compare(word, token) == 0){
                print_line(word, temp_list->text);
            }
            token = strtok(NULL, " ");
        }
    }
}

int main(int argc, char *argv[]){
    node_t *excl_words = read_excl_words();
    node_t *input_lines = read_lines();
    node_t *index_words = get_index_words(input_lines, excl_words);

    apply(index_words, output_lines, input_lines);
    
    free_lists(excl_words);
    free_lists(input_lines);
    free_lists(index_words);
/* 
 * Showing some simple usage of the linked-list routines.
 */

#ifdef DEBUG
   // _demo();
#endif

    exit(0);
}
