#ifndef __BLOCK_H__
#define __BLOCK_H__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "../define.h"
#include "../crypto/sha256.h"
#include "../crypto/md5.h"
#include "../times/datetime.h"

#define DATA_BLOCK_SIZE     64
/**
 * struct data about:
 *      + @param length         length of data
 *      + @param value          array value with size 64 BYTE /block
*/
typedef struct data{
    WORD length;
    BYTE value[DATA_BLOCK_SIZE];
}data;

/**
 *  struct Transactions about:
 *      + @param timestamp         time to create block
 *      + @param segment           data segment
 *      + @param address           address of device store next block
*/
typedef struct Transactions{
    BYTE address[MD5_BLOCK_SIZE];
    datetime timestamp;
    data segment;
}Transactions;
/**
 * struct block about 
 *      + @param hash:             hash code of block signature digit.
 *      + @param previous_hash     hash code of previous block signature digital of previour block.
 *      + @param transaction       packet data.
*/
typedef struct block{
    WORD index;
    BYTE hash[SHA256_BLOCK_SIZE];
    Transactions transaction;
    BYTE previous_hash[SHA256_BLOCK_SIZE];
}block;

/**
 * function create_data use to create data for block
 * @param length        the length of data.
 * @param buff          array BYTE data (max 64 BYTEs).
 * @return              the function return packet data.
*/
data create_data(WORD length, BYTE *buff);
/**
 * function calc_hash compute hash code of transaction packet data
 * @param trans     transaction packet data.
 * @param result    result hash code
*/
void calc_hash(Transactions trans, BYTE *result);
/**
 * function MD5convert convert data to MD5 encode
 * @param value     value to convert MD5 hash
 * @param length    length of value
 * @param result    result of hash process
*/
void MD5convert(BYTE value[], WORD length, BYTE *result);
/**
 * function block_init will be initialized block with param:
 *      @param value        data to store in block.
 *      @param addr         address to store for NEXT block.
 *      @param pre_hash     hash code previous block
 *      @param index        index block
*/
block block_init(data value, const BYTE* addr, const BYTE* pre_hash, int index);

#ifdef DEBUG

void print(block b);

#endif

#endif