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
    // char* path = {"dcb37f3b885b41594ebc82b2f64f32e0b6c421757ea6ed05f45fedd3e36761ea.sha"};
    // BYTE str[] = {"Hello World"};

    // CHAIN *new_chain = NULL;

    // DATA temp = create_data(strlen(str), str);
    // BYTE* hash = (BYTE*)malloc(SHA256_BLOCK_SIZE * sizeof(BYTE));
    // char name[SHA256_BLOCK_SIZE * 2];
    
    // new_chain = genesis_block(new_chain, hash);
    // new_chain = add_block(hash, temp, 1, new_chain);
    // new_chain = add_block(hash, temp, 2, new_chain);
    // new_chain = add_block(hash, temp, 3, new_chain);

    // CHAIN* node = find_node(1, new_chain);

    // // print_debug_chain(new_chain);
    // print_debug_node(node);

    // write_block_local(node->block, "temp/");

    // // BLOCK b = read_block_local(path);

    // // print_debug_block(b);

    char* path = {"/home/ducvu/Desktop/face_mesh.py"};
    CHAIN* new_chain = NULL;

    new_chain = file2chain(path, new_chain);

    // print_debug_chain(new_chain);
    // printf("%d\n", length_chain(new_chain));
    chain2file(new_chain, "temp/");
    printf("done\n");

    return 0;
}