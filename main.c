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
    // char* path = {"/home/ducvu/Desktop/Example.py"};
    // CHAIN* new_chain = NULL;
    CHAIN* old_chain = NULL;
    // new_chain = file2chain(argv[1], new_chain);
    // print_debug_chain(new_chain);
    // // printf("%d\n", length_chain(new_chain));
    // chain2file(new_chain, "temp/");
    // printf("done\n");

    const char* shortcut = {"temp/0000000000000000000000000000000000000000000000000000000000000000.sha"};
    const char* folder = {"temp/"};

    convertChain2file(shortcut, folder, old_chain);

    // BLOCK b = read_block(argv[1]);

    // print_debug_block(b);

    return 0;
}