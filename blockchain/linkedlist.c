#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "linkedlist.h"

// CHAIN **head_node = NULL;

CHAIN* insert_first(int index, BLOCK block, CHAIN* head_node){
    //create link
    CHAIN *link = (CHAIN*)malloc(sizeof(CHAIN));
    // write index and data to chain
    link->index = index;
    memcpy(&link->block, &block, sizeof(BLOCK));
    // point next head_node
    link->next = head_node;
    // set address node head_node to new node
    return link;
}

CHAIN* delete_first(CHAIN* head_node){
    // set temp is first node in chain
    CHAIN* temp = head_node;
    //return chain has removed
    return head_node->next;
}

CHAIN* delete_node(int index, CHAIN* head_node){
    CHAIN* current = head_node;
    CHAIN* previous = NULL;

    if(head_node == NULL) return NULL;

    while(current->index != index){
        if(current->next == NULL) return NULL;
        else{
            previous = current;
            current = current->next;
        }
    }

    if(current == head_node) return head_node->next;
    else previous->next = current->next;

    free(current);
    free(previous);

    return head_node;
}

CHAIN* find_node(int index, CHAIN* head_node){
    CHAIN* current = head_node;

    if(head_node == NULL) return NULL;

    while(current->index != index){
        if(current->next == NULL) return NULL;
        else current = current->next;
    }
    return current;
}

BOOL is_empty(CHAIN* head_node){
    return (head_node == NULL) ? TRUE : FALSE;
}

int length_chain(CHAIN* head_node){
    int length = 0;
    CHAIN* current;
    //browser node in chain.
    for(current = head_node; current != NULL; current = current->next)
        length++;
    //return length of chain
    return length;
}

void print_debug_chain(CHAIN* head_node){
    CHAIN *ptr = head_node;
    //start from begining
    printf("+++++ debug chain +++++\n");
    while(ptr != NULL){
        printf("{%d}\n", ptr->index);
        print_debug_block(ptr->block);
        ptr = ptr->next;
    }
    printf("+++++++++++++++++++++++\n\n");
}

void print_debug_node(CHAIN* node){
    printf("+++++ debug node +++++\n");
    printf("\tindex:\t%d\n", node->index);
    print_debug_block(node->block);
    printf("+++++++++++++++++++++++\n\n");
}