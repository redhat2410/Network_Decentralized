#ifndef __BLOCKCHAIN_H__
#define __BLOCKCHAIN_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "../define.h"
#include "block.h"
#include "linkedlist.h"

/**
 * function genesis_block create first block 
 * @param   chain       put block into chain
 * @param   hash        return hash of bloock.
 * @return              The function return chai.
*/
CHAIN* genesis_block(CHAIN* chain, BYTE *hash);

/**
 * function add_block add block into chain.
 * @param index             index of block.
 * @param previour_hash     hash of previous of block and provide new hash of block.
 * @param hash              hash of current block.
 * @param segment           segment of data.
 * @param chain             put block in to chain
 * @return                  the function is return block.
*/
CHAIN* add_block(const BYTE *pre_hash, DATA segment, int index, 
            CHAIN* chain);

/**
 * the function vaid_block use to check hash of block is valid 
 * @param current_block     block want to check.
 * @return                  the function is return TRUE/FALSE
*/
BOOL vaild_block(BLOCK current_block);

/**
 * the function write_block_local use to write block in local pc.
 * block will write to default_folder has been defined.
 * @param b             block want to write in local.
 * @return              return status write TRUE/FALSE.
*/
BOOL write_block_local(BLOCK b);
/**
 * the function read_block_local use to read block from local
 * @param url           path to file.
 * @return              the function return block after read success.
*/
BLOCK read_block_local(char *url);

#endif