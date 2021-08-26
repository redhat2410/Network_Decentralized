#include "block.h"

DATA create_data(WORD length, BYTE *buff){
    DATA segment;
    // write packet data
    segment.length = length;
    memcpy(&segment.value[0], buff, sizeof(BYTE) * length);
    // return packet data have been written.
    return segment;
}

void MD5convert(BYTE value[], WORD length, BYTE *result){
    //init MD5
    MD5_CTX ctx;
    md5_init(&ctx);
    md5_update(&ctx, value, length);
    md5_final(&ctx, result);
}

void calc_hash(TRANSACTION trans, BYTE *result){
    SHA256_CTX ctx;
    BYTE temp[SHA256_BLOCK_SIZE]; //array store result
    // buffer to convert struct Transactions to BYTEs
    BYTE *buff = (BYTE*)malloc(sizeof(TRANSACTION) * sizeof(BYTE));
    //convert struct Transactions to BYTEs array
    memcpy(buff, &trans, sizeof(TRANSACTION));
    //init sha256 encode and convert to sha256
    sha256_init(&ctx);
    sha256_update(&ctx, buff, sizeof(TRANSACTION));
    sha256_final(&ctx, temp);
    // return encode result
    memcpy(result, &temp, SHA256_BLOCK_SIZE);
}

BLOCK block_init(DATA value, const BYTE addr[], const BYTE pre_hash[], int index){
    //get time create block
    DATETIME timestamp = get_currenttime();
    BLOCK ret = { 0 };
    // write block
    BYTE hash[SHA256_BLOCK_SIZE];
    // transaction data
    TRANSACTION trans = {0};
    trans.index = index;
    memcpy(&trans.segment, &value, sizeof(DATA));
    memcpy(&trans.timestamp, &timestamp, sizeof(DATETIME));
    memcpy(&trans.address[0], &addr[0], MD5_BLOCK_SIZE);
    // calculator hash for transaction block
    calc_hash(trans, hash);
    // write block
    memcpy(&ret.hash[0], &hash[0], SHA256_BLOCK_SIZE);
    memcpy(&ret.previous_hash[0], &pre_hash[0], SHA256_BLOCK_SIZE);
    memcpy(&ret.transaction, &trans, sizeof(TRANSACTION));
    // return block
    return ret;
}

int sha2str(BYTE *hash, char result[]){
    char character[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a',
                'b', 'c', 'd', 'e', 'f'};
    char str[SHA256_BLOCK_SIZE * 2];
    BYTE high = 0, low = 0;

    for(int i = 0; i < SHA256_BLOCK_SIZE; i++){
        low = hash[i] & 0x0F;
        high = (hash[i] >> 4) & 0x0F;
        str[(i * 2)] = character[high];
        str[(i * 2) + 1] = character[low];
            
    }
    // copy str to result
    strcpy(result, str);
    // return lenght of string
    return SHA256_BLOCK_SIZE * 2;
}

#ifdef DEBUG
void print_debug_block(BLOCK b){
    printf("============Transaction============\n");
    printf("index:\t%d\n", b.transaction.index);
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