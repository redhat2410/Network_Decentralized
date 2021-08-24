#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "../define.h"
#include "../crypto/md5.h"
#include "../crypto/sha256.h"

typedef struct CHAIN{
    int address;
    int index;
    struct CHAIN *next;
}CHAIN;

/**
 * the function insert_first use to add node in first pos chain
 * @param index         index of node
 * @param address       value of node
 * @return              None
*/
void insert_first(int index, int address);
/**
 * the function delete_first use to remove node in first position chain.
 * @return      The function return chain has been removed.
*/
CHAIN* delete_first(void);
/**
 * the function delete_node use to remove node in everywhere in chain.
 * @param index     index of node want to remove.
 * @return          the function return chain has been removed.
*/
CHAIN* delete_node(int index);
/**
 * the function find_node use to find node by index.
 * @param   index   index of node want to find.
 * @return          the function return node or NULL.
*/
CHAIN* find_node(int index);
/**
 * the function is_empty use to check chain empty
 * @return      the function return TRUE/FALSE
*/
BOOL is_empty(void);
/**
 * the function length_chain length of chain.
 * @return      the function return length of chain.
*/
int length_chain(void);

#ifdef DEBUG
/**
 * the function pritn_debug_chain use to print data in chain
*/
void print_debug_chain(void);
void print_debug_node(CHAIN* node);
#endif

#endif