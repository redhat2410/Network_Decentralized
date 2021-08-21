#include <stdio.h>
#include <block.h>

int block_test(void){
    byte str[] = {"hello world"};
    byte address[] = {0x90, 0x2b, 0x34, 0xb1, 0x84, 0x4d};
    byte addr[MD5_BLOCK_SIZE];
    data value;
    MD5_CTX ctx;
    value.length = strlen(str);
    memcpy(&value.value, &str, strlen(str));
    md5_init(&ctx);
    md5_update(&ctx, address, 6);
    md5_final(&ctx, addr);
}
