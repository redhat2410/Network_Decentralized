#ifndef __BLOCKCHAIN_H__
#define __BLOCKCHAIN_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "../define.h"
#include "block.h"

/**
 * function genesis_block create first block 
 * @return  function is return first block.
*/
block genesis_block(void);

/**
 * function add_block add block into chain.
 * @param previour_hash     hash of previous of block.
 * @param segment           segment of data.
 * @return                  the function is return block.
*/
block add_block(const BYTE *pre_hash, data segment);

/**
 * the function vaid_block use to check hash of block is valid 
 * @param current_block     block want to check.
 * @return                  the function is return TRUE/FALSE
*/
BOOL vaild_block(block current_block);

/**
 * the function write_block_local use to write block in local pc.
 * block will write to default_folder has been defined.
 * @param b             block want to write in local.
 * @return              return status write TRUE/FALSE.
*/
BOOL write_block_local(block b);

#endif