#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "define.h"
#include "times/datetime.h"
#include "blockchain/block.h"
#include "blockchain/linkedlist.h"
#include "blockchain/blockchain.h"
#include "crypto/sha256.h"
#include "crypto/md5.h"

int main(int argc, char **argv){
    BYTE str[] = {"Hello World"};

    CHAIN *new_chain = NULL;

    DATA temp = create_data(strlen(str), str);
    BYTE* hash = (BYTE*)malloc(SHA256_BLOCK_SIZE * sizeof(BYTE));
    char name[SHA256_BLOCK_SIZE * 2];
    
    new_chain = genesis_block(new_chain, hash);
    new_chain = add_block(hash, temp, 1, new_chain);
    new_chain = add_block(hash, temp, 2, new_chain);
    new_chain = add_block(hash, temp, 3, new_chain);

    CHAIN* node = find_node(1, new_chain);

    // print_debug_chain(new_chain);
    print_debug_node(node);

    write_block_local(node->block);

    return 0;
}