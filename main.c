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

    byte str[] = {"Hello World"};
    byte address[] = {0x90, 0x2b, 0x34, 0xb1, 0x84, 0x4d};
    byte *addr = (byte*)malloc(MD5_BLOCK_SIZE * sizeof(byte));

    MD5convert(address, 6, addr);

    segment.length = strlen(str);
    memcpy(&segment.value, &str, strlen(str));

    b = block_init(segment, addr, DEFAULT_SHA256, 1);

    print(b);
    return 0;
}