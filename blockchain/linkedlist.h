#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "../define.h"
#include "block.h"

typedef struct CHAIN{
    BLOCK block;
    int index;
    struct CHAIN *next;
}CHAIN;

/**
 * the function insert_first use to add node in first pos chain
 * @param index         index of node
 * @param address       value of node
 * @param head_node     head node of chain
 * @return              chain has inserted.
*/
CHAIN* insert_first(int index, BLOCK block, CHAIN* head_node);
/**
 * the function delete_first use to remove node in first position chain.
 * @param head_node     chain need to remove first node
 * @return      The function return chain has removed.
*/
CHAIN* delete_first(CHAIN* head_node);
/**
 * the function delete_node use to remove node in everywhere in chain.
 * @param index     index of node want to remove.
 * @param head_node chain need to remove idx node.
 * @return          the function return chain has  removed.
*/
CHAIN* delete_node(int index, CHAIN* head_node);
/**
 * the function find_node use to find node by index.
 * @param   index   index of node want to find.
 * @param   head_node chain to find.
 * @return          the function return node or NULL.
*/
CHAIN* find_node(int index, CHAIN* head_node);
/**
 * the function is_empty use to check chain empty
 * @return      the function return TRUE/FALSE
*/
BOOL is_empty(CHAIN* head_node);
/**
 * the function length_chain length of chain.
 * @return      the function return length of chain.
*/
int length_chain(CHAIN* head_node);

#ifdef DEBUG
/**
 * the function pritn_debug_chain use to print data in chain
*/
void print_debug_chain(CHAIN* head_node);
void print_debug_node(CHAIN* node);
#endif

#endif