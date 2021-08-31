#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "crypto.h"

int sha2str(BYTE *hash, char result[]){
    char character[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a',
                'b', 'c', 'd', 'e', 'f'};
    char str[(SHA256_BLOCK_SIZE * 2) + 1];
    BYTE high = 0, low = 0;

    for(int i = 0; i < SHA256_BLOCK_SIZE; i++){
        low = hash[i] & 0x0F;
        high = (hash[i] >> 4) & 0x0F;
        str[(i * 2)] = character[high];
        str[(i * 2) + 1] = character[low];
    }
    // copy str to result
    strcpy(result, str);
    // process string
    if (strlen(result) > (SHA256_BLOCK_SIZE * 2) + 1){
        int temp = strlen(result) - ((SHA256_BLOCK_SIZE * 2) + 1);
        for(int i = (SHA256_BLOCK_SIZE * 2) + 1; i < (SHA256_BLOCK_SIZE * 2) + 4; i++)
            result[i] = 0;
    }
    // return lenght of string
    return SHA256_BLOCK_SIZE * 2;
}

int md52str(BYTE *hash, char result[]){
    char character[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a',
                'b', 'c', 'd', 'e', 'f'};
    char str[MD5_BLOCK_SIZE * 2];
    BYTE high = 0, low = 0;

    for(int i = 0; i < MD5_BLOCK_SIZE; i++){
        low = hash[i] & 0x0F;
        high = (hash[i] >> 4) & 0x0F;
        str[(i * 2)] = character[high];
        str[(i * 2) + 1] = character[low];
    }
    // copy str to result
    strcpy(result, str);
    // return length of string
    return MD5_BLOCK_SIZE * 2;
}

int des2str(BYTE *hash, char result[]){
    char character[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a',
                'b', 'c', 'd', 'e', 'f'};
    char str[DES_BLOCK_SIZE * 2];
    BYTE high = 0, low = 0;

    for(int i = 0; i < DES_BLOCK_SIZE; i++){
        low = hash[i] & 0x0F;
        high = (hash[i] >> 4) & 0x0F;
        str[(i * 2)] = character[high];
        str[(i * 2) + 1] = character[low];
    }
    // copy str to result
    strcpy(result, str);
    // return length of string
    return DES_BLOCK_SIZE * 2;
}