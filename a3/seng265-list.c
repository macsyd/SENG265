/*
 * linkedlist.c
 *
 * Based on the implementation approach described in "The Practice 
 * of Programming" by Kernighan and Pike (Addison-Wesley, 1999).
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "emalloc.h"
#include "seng265-list.h"


node_t *new_node(char *text) {
    assert( text != NULL);

    node_t *temp = (node_t *)emalloc(sizeof(node_t));

    strncpy(temp->text, text, LIST_MAXLEN_TEXT);
    temp->next = NULL;

    return temp;
}

int compare(char *str1, char *str2){
    char temp1[strlen(str1)];
    strncpy(temp1, str1, strlen(str1));
    char temp2[strlen(str2)];
    strncpy(temp2, str2, strlen(str2));
    for(int i = 0; i < strlen(str1); i++){
        temp1[i] = toupper(temp1[i]);
    }
    for(int j = 0; j < strlen(str2); j++){
        temp2[j] = toupper(temp2[j]);
    }
    return(strncmp(temp1, temp2, strlen(str1)));
}

node_t *add_front(node_t *list, node_t *new) {
    new->next = list;
    return new;
}


node_t *add_end(node_t *list, node_t *new) {
    node_t *curr;

    if (list == NULL) {
        new->next = NULL;
        return new;
    }

    for (curr = list; curr->next != NULL; curr = curr->next);
    curr->next = new;
    new->next = NULL;
    return list;
}

node_t *add_inorder(node_t *list, node_t *new){
    if(list == NULL){
        new->next = NULL;
        return new;
    }
    node_t *curr = list;
    node_t *prev = NULL;
    for ( ; curr != NULL; curr = curr->next){
        if(compare(curr->text, new->text) > 0){ /*new should be before curr*/
            if(prev == NULL){
                return add_front(curr, new);
            }
            prev->next = add_front(curr, new);
            return list;
        }else if(compare(list->text, new->text) == 0){ /*new and curr have the same word*/
            free(new);
            return list; /*get rid of duplicates*/
        }
        prev = curr;
    }
    return add_end(list, new);
}

node_t *peek_front(node_t *list) {
    return list;
}


node_t *remove_front(node_t *list) {
    if (list == NULL) {
        return NULL;
    }

    return list->next;
}


void apply(node_t *list,
           void (*fn)(node_t *list, void *),
           void *arg)
{
    for ( ; list != NULL; list = list->next) {
        (*fn)(list, arg);
    }
}
