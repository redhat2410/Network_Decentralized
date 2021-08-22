#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "define.h"
#include "times/datetime.h"
#include "blockchain/block.h"
#include "crypto/sha256.h"
#include "crypto/md5.h"


int main(int argc, char **argv){
    // Transactions trans;
    data segment;
    block b;

    BYTE str[] = {"Hello World"};
    BYTE address[] = {0x90, 0x2b, 0x34, 0xb1, 0x84, 0x4d};
    BYTE *addr = (BYTE*)malloc(MD5_BLOCK_SIZE * sizeof(BYTE));

    MD5convert(address, 6, addr);

    segment.length = strlen(str);
    memcpy(&segment.value, &str, strlen(str));

    b = block_init(segment, addr, DEFAULT_SHA256, 1);

    print(b);
    return 0;
}