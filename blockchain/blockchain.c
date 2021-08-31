#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "blockchain.h"

BYTE address_default[] = {0x90, 0x2b, 0x34, 0xb1, 0x84, 0x4d};

CHAIN* genesis_block(CHAIN* chain, BYTE *hash, char* shortcut){
    // create genesis block
    BLOCK genesis;
    DATA segment = { 0 };
    BYTE *addr = (BYTE*)malloc(MD5_BLOCK_SIZE * sizeof(BYTE));
    // write block genesis
    MD5convert(address_default, 6, addr);
    //create data by shortcut file
    segment = create_data(strlen(shortcut), (BYTE*)shortcut);
    //create first block
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

BOOL write_block_local(BLOCK b, char* folder){
    //write file in local with name is hash of block
    //get hash of block
    char hash_str[SHA256_BLOCK_SIZE * 2];
    char* fullname;
    char* extension = {".sha"};
    FILE* f;
    BYTE* hash = (BYTE*)malloc(SHA256_BLOCK_SIZE * sizeof(BYTE));
    BYTE* buff = (BYTE*)malloc(sizeof(BLOCK) * sizeof(BYTE));
    memcpy(hash, b.hash, SHA256_BLOCK_SIZE * sizeof(BYTE));
    // init name file from hash of block
    sha2str(b.previous_hash, hash_str);
    fullname = make_path_file(folder, hash_str, extension);
    // creat file and write file
    f = fopen(fullname, "w");
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
    free(fullname);
    // return TRUE write done
    return TRUE;
}

BLOCK read_block_local(char *url){
    //read file in local 
    BLOCK b = {0};
    FILE *fp;
    BYTE *buff = (BYTE*)malloc(sizeof(BLOCK) * sizeof(BYTE));
    char chr;
    int index = 0;

    fp = fopen(url, "r");
    if(fp == NULL) return b;
    // read byte to file
    while((chr = fgetc(fp)) != EOF){
        if(index > sizeof(BLOCK)) break;
        buff[index] = chr;
        index++;
    }
    //convert buff byte to block
    memcpy(&b, buff, sizeof(BLOCK) * sizeof(BYTE));

    //close file and release buffer
    fclose(fp);
    free(buff);
    return b;
}

CHAIN* file2chain(char* path, CHAIN* chain){
    // read file and split data to segment 64 byte and write to block.
    BYTE *buffer = (BYTE*)malloc(DATA_BLOCK_SIZE * sizeof(BYTE));
    BYTE *hash = (BYTE*)malloc(SHA256_BLOCK_SIZE * sizeof(BYTE));
    DATA temp = { 0 };
    char* filename;
    int length = 0, index = 1;
    char chr;
    // check file is ready
    FILE *fp;
    fp = fopen(path, "r"); //read file
    if(fp == NULL) return NULL;
    filename = basename(path);
    // create first block
    chain = genesis_block(chain, hash, filename);
    // read byte to file
    while((chr = fgetc(fp)) != EOF){
        if(length >= DATA_BLOCK_SIZE){
            // write segment to block
            temp = create_data(length, buffer);
            chain = add_block(hash, temp, index, chain);
            //reset index and buffer
            length = 0;
            //incease index to 1
            index++;
        }
        // write data to buffer and increase to 1
        buffer[length] = (BYTE)chr;
        length++;
    }
    // in-case last buffer not enough size
    if(length != 0){
        temp = create_data(length, buffer);
        // add last block in chain
        chain = add_block(hash, temp, index, chain);
    }
    else { /* do nothing */ }
    //close file
    fclose(fp);
    free(hash);
    free(buffer);
    //return chain
    return chain;
}

BOOL chain2file(CHAIN* chain, char* folder){
    CHAIN* ptr = chain;
    //browser chain node by node and write block by file
    while(ptr != NULL){
        //write block
        BOOL chk = write_block_local(ptr->block, folder);
        //load next pointer
        ptr = ptr->next;
    }
    free(ptr);
    return TRUE;
}

BOOL convertChain2file(char* shortcut, char* folder){
    BLOCK genesis, b;
    char hashstr[(SHA256_BLOCK_SIZE * 2) + 1];
    char *fname, *temp;
    FILE *fp;
    FILE *fc;
    //first read file shortcut and search next file in folder.
    genesis = read_block_local(shortcut);
    sha2str(genesis.hash, hashstr);
    // create file to recogver
    temp = (char*)malloc(genesis.transaction.segment.length * sizeof(char));
    strcpy(temp, (char*)genesis.transaction.segment.value);
    fc = fopen(temp, "w");
    // after read file shortcut and convert to BLOCK 
    fname = make_path_file(folder, hashstr, ".sha");
    // check file is exists 
    fp = fopen(fname, "r");
    if(fp == NULL) return FALSE;
    do{
        fclose(fp);
        //read file and convert to block
        printf("%s\n", fname);
        b = read_block_local(fname);
        printf("1");
        for(int i = 0; i < b.transaction.segment.length; i++)
            fprintf(fc, "%c", (char)b.transaction.segment.value[i]);
        sha2str(b.hash, hashstr);
        printf("2");
        fname = make_path_file(folder, hashstr, ".sha");
        printf("3");
        // check file
        fp = fopen(fname, "r");
    }while(fp != NULL);

    printf("Create file: %s\n", genesis.transaction.segment.value);
    //close all file and release memory
    if(fp != NULL) fclose(fp);
    if(fc != NULL) fclose(fc);
    free(temp);
    free(fname);
}