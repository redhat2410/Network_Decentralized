#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "blockchain.h"

BYTE address_default[] = {0x90, 0x2b, 0x34, 0xb1, 0x84, 0x4d};

CHAIN* genesis_block(CHAIN* chain, BYTE *hash){
    // create genesis block
    BLOCK genesis;
    DATA segment = { 0 };
    BYTE *addr = (BYTE*)malloc(MD5_BLOCK_SIZE * sizeof(BYTE));
    // write block genesis
    MD5convert(address_default, 6, addr);
    genesis = block_init(segment, addr, DEFAULT_SHA256, 0);
    //copy hash of block
    memcpy(hash, genesis.hash, SHA256_BLOCK_SIZE * sizeof(BYTE));
    // release memory
    free(addr);
    return insert_first(0, genesis, chain);
}

CHAIN* add_block(const BYTE *pre_hash, DATA segment, 
        int index, CHAIN* chain){
    // create block and data
    BLOCK child_block;
    BYTE* addr = (BYTE*)malloc(MD5_BLOCK_SIZE * sizeof(BYTE));
    //select physical address and convert
    MD5convert(address_default, 6, addr);
    child_block = block_init(segment, addr, pre_hash, index);
    // copy hash
    memcpy(pre_hash, child_block.hash, SHA256_BLOCK_SIZE * sizeof(BYTE));
    //release memory
    free(addr);
    //return chain
    return insert_first(index, child_block, chain);
}

BOOL vaild_block(BLOCK current_block){
    //get hash of block 
    TRANSACTION temp = {0};
    BYTE* hash = (BYTE*)malloc(SHA256_BLOCK_SIZE * sizeof(BYTE));
    BYTE* result = (BYTE*)malloc(SHA256_BLOCK_SIZE * sizeof(BYTE));

    memcpy(hash, current_block.hash, SHA256_BLOCK_SIZE * sizeof(BYTE));
    // re-compute transaction of block
    memcpy(&temp, &current_block.transaction, sizeof(TRANSACTION) * sizeof(BYTE));
    calc_hash(temp, result);
    // return compare result of 
    return (memcmp(hash, result, SHA256_BLOCK_SIZE * sizeof(BYTE)) != 0) ? TRUE : FALSE;
}

BOOL write_block_local(BLOCK b){
    //write file in local with name is hash of block
    //get hash of block
    char hash_str[SHA256_BLOCK_SIZE * 2];
    char* fname;
    FILE* f;
    BYTE* hash = (BYTE*)malloc(SHA256_BLOCK_SIZE * sizeof(BYTE));
    BYTE* buff = (BYTE*)malloc(sizeof(BLOCK) * sizeof(BYTE));
    memcpy(hash, b.hash, SHA256_BLOCK_SIZE * sizeof(BYTE));
    // init name file from hash of block
    sha2str(b.hash, hash_str);
    fname = strcat(hash_str, ".sha");
    // creat file and write file
    f = fopen(fname, "w");
    // check create file success
    if(f == NULL) return FALSE;
    // convert block to buff byte have to write file
    memcpy(buff, &b, sizeof(BLOCK) * sizeof(BYTE));
    // write file
    for(int i = 0; i < sizeof(BLOCK); i++)
        fprintf(f, "%c", buff[i]);
    //release memory and close file
    fclose(f);
    free(hash);
    free(buff);
    // return TRUE write done
    return TRUE;
}

BLOCK read_block_local(char *url){
    //read file in local 
}