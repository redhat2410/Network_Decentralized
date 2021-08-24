#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "define.h"
#include "times/datetime.h"
#include "blockchain/block.h"
#include "blockchain/linkedlist.h"
#include "crypto/sha256.h"
#include "crypto/md5.h"


int main(int argc, char **argv){
    // Transactions trans;
    // data segment;
    // block b;

    // BYTE str[] = {"Hello World"};
    // BYTE address[] = {0x90, 0x2b, 0x34, 0xb1, 0x84, 0x4d};
    // BYTE *addr = (BYTE*)malloc(MD5_BLOCK_SIZE * sizeof(BYTE));

    // MD5convert(address, 6, addr);

    // segment.length = strlen(str);
    // memcpy(&segment.value, &str, strlen(str));

    // b = block_init(segment, addr, DEFAULT_SHA256, 1);

    // print_debug_block(b);
    // return 0;

    insert_first(1, 10);
    insert_first(2, 20);
    insert_first(3, 30);
    insert_first(4, 40);

    print_debug_chain();

    delete_first();

    print_debug_chain();

    delete_node(2);

    print_debug_chain();

    CHAIN* temp = find_node(1);

    print_debug_node(temp);

    return 0;
}