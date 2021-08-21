#include "block.h"

void MD5convert(byte value[], word length, byte *result){
    //init MD5
    MD5_CTX ctx;
    md5_init(&ctx);
    md5_update(&ctx, value, length);
    md5_final(&ctx, result);
}

void calc_hash(Transactions trans, byte *result){
    SHA256_CTX ctx;
    byte temp[SHA256_BLOCK_SIZE]; //array store result
    // buffer to convert struct Transactions to bytes
    byte *buff = (byte*)malloc(sizeof(Transactions) * sizeof(byte));
    //convert struct Transactions to bytes array
    memcpy(buff, &trans, sizeof(Transactions));
    //init sha256 encode and convert to sha256
    sha256_init(&ctx);
    sha256_update(&ctx, buff, sizeof(Transactions));
    sha256_final(&ctx, temp);
    // return encode result
    memcpy(result, &temp, SHA256_BLOCK_SIZE);
}

block block_init(data value, const byte addr[], const byte pre_hash[], int index){
    //get time create block
    datetime timestamp = get_currenttime();
    block ret = { 0 };
    // write block
    byte hash[SHA256_BLOCK_SIZE];
    // transaction data
    Transactions trans = {0};
    memcpy(&trans.segment, &value, sizeof(data));
    memcpy(&trans.timestamp, &timestamp, sizeof(datetime));
    memcpy(&trans.address[0], &addr[0], MD5_BLOCK_SIZE);
    // calculator hash for transaction block
    calc_hash(trans, hash);
    // write block
    memcpy(&ret.hash[0], &hash[0], SHA256_BLOCK_SIZE);
    memcpy(&ret.previous_hash[0], &pre_hash[0], SHA256_BLOCK_SIZE);
    memcpy(&ret.transaction, &trans, sizeof(Transactions));
    ret.index = index;
    // return block
    return ret;
}

#ifdef DEBUG
void print(block b){
    printf("============Transaction============\n");
    printf("index:\t%d\n", b.index);
    printf("address: ");
    for(int i = 0; i < MD5_BLOCK_SIZE; i++)
        printf("%02x", b.transaction.address[i]);
    printf("\nsegment:\n");
    printf("\tlength:\t%d\n", b.transaction.segment.length);
    printf("\tvalue:\t");
    for(int i = 0; i < b.transaction.segment.length; i++)
        printf("%02x", b.transaction.segment.value[i]);
    printf("\ntimestamp: %d/%d/%d %d:%d:%d", b.transaction.timestamp.day, b.transaction.timestamp.mon ,
            b.transaction.timestamp.year + DEFAULT_YEAR, b.transaction.timestamp.hour, b.transaction.timestamp.min, b.transaction.timestamp.sec);
    printf("\n===============Hash================\n");
    printf("hash:\t\t");
    for(int i = 0; i < SHA256_BLOCK_SIZE; i++)
        printf("%02x", b.hash[i]);
    printf("\nprevious hash:\t");
    for(int i = 0; i < SHA256_BLOCK_SIZE; i++)
        printf("%02x", b.previous_hash[i]);
    printf("\n===================================\n");
}
#endif