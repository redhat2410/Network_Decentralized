#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "linkedlist.h"

CHAIN *head_node = NULL;

void insert_first(int index, int address){
    //create link
    CHAIN* link = (CHAIN*)malloc(sizeof(CHAIN));
    // write index and data to chain
    link->index = index;
    link->address = address;
    // point next head_node
    link->next = head_node;
    // set address node head_node to new node
    head_node = link;
}

CHAIN* delete_first(void){
    // set temp is first node in chain
    CHAIN* temp = head_node;
    head_node = head_node->next;
    //return
    return temp;
}

CHAIN* delete_node(int index){
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

    if(current == head_node) head_node = head_node->next;
    else previous->next = current->next;

    return current;
}

CHAIN* find_node(int index){
    CHAIN* current = head_node;

    if(head_node == NULL) return NULL;

    while(current->index != index){
        if(current->next == NULL) return NULL;
        else current = current->next;
    }
    return current;
}

BOOL is_empty(void){
    return (head_node == NULL) ? TRUE : FALSE;
}

int length_chain(void){
    int length = 0;
    CHAIN* current;
    //browser node in chain.
    for(current = head_node; current != NULL; current = current->next)
        length++;
    //return length of chain
    return length;
}

void print_debug_chain(void){
    CHAIN* ptr = head_node;
    //start from begining
    printf("+++++ debug chain +++++\n");
    while(ptr != NULL){
        printf("{%d, %ld}\n", ptr->index, ptr->address);
        ptr = ptr->next;
    }
    printf("+++++++++++++++++++++++\n\n");
}

void print_debug_node(CHAIN* node){
    printf("+++++ debug node +++++\n");
    printf("\tindex:\t%d\n", node->index);
    printf("\tvalue:\t%d\n", node->address);
    printf("+++++++++++++++++++++++\n\n");
}