import os
import sys
import time
import json
from datetime import datetime
from hashlib import sha256

DATA_BLOCK_SIZE = 10 * 1024

class TRANSACTION(object):
    def __init__(self, length : int = None, data : bytes = None):
        self.__key      = 0x2410
        self.__lengh    = length
        self.__data     = data
        self.__buff     = b""

    def __enc__(self):
        # encode data by private key = 0x2410 will be xor all data 
        buffer = list()
        if self.__lengh != None and self.__data != None:
            for i in range(0, self.__lengh):
                temp = self.__data[i] ^ self.__key
                buffer.append(temp.to_bytes(2, 'big'))
        self.__buff = b"".join(buffer)

    def __dec__(self, buffer : bytes, length : int):
        # length of original data with before encode
        data = list()
        for i in range(0, length * 2, 2):
            # each of length with 2 bytes in buffer
            temp = int.from_bytes(buffer[i : i + 2], 'big') ^ self.__key
            # append temp into list
            data.append(temp.to_bytes(1, 'big'))
        self.__lengh = length
        self.__data = b"".join(data)

    def __bytes__(self):
        # convert Transaction object to bytes with format: bytes (0, 1) -> length (2 -> end) data
        return b"".join([int(self.__lengh).to_bytes(2, 'big'), self.__buff])

    def __str__(self):
        print("Length:\t", self.__lengh)
        print("Data: ", self.__data)


class DATETIME(object):
    def __init__(self, now : datetime = None, buff : bytes = None):
        self.SIZE     = 10
        self.__now    = now
        self.__buff   = buff
    
    def __bytes__(self):
        buff = b"".join([self.__now.year.to_bytes(2, 'big'),
                        self.__now.month.to_bytes(1, 'big'),
                        self.__now.day.to_bytes(1, 'big'),
                        self.__now.hour.to_bytes(1, 'big'),
                        self.__now.minute.to_bytes(1, 'big'),
                        self.__now.second.to_bytes(1, 'big'),
                        self.__now.microsecond.to_bytes(3, 'big')])
        return buff

    def __str__(self):
        if self.__now != None:
            return self.__now.__str__()
        elif self.__buff != None:
            year    = int.from_bytes(self.__buff[0:2], 'big')
            month   = int.from_bytes(self.__buff[2:3], 'big')
            day     = int.from_bytes(self.__buff[3:4], 'big')
            hour    = int.from_bytes(self.__buff[4:5], 'big')
            minute  = int.from_bytes(self.__buff[5:6], 'big')
            second  = int.from_bytes(self.__buff[6:7], 'big')
            microsecond = int.from_bytes(self.__buff[7:len(self.__buff)], 'big')
            return "%d-%d-%d %d:%d:%d.%d" % (year, month, day, hour, minute, second, microsecond)

class BLOCK(object):
    def __init__(self, index : int, length : int, data : bytes, pre_hash : bytes):
        # init block with param length and
        self.hash       = None
        self.index      = index.to_bytes(2, 'big')
        self.timestamp  = DATETIME(datetime.now())
        self.transaction = TRANSACTION(length, data)
        self.pre_hash   = pre_hash
        # calc hash of block
        self.__hash__()

    def __bytes__(self):
        # convert byte with format bytes (0,1) -> index; (2, 12) -> timestamp; (13, 35) -> hash; (36, 68) -> pre-hash (69 -> end) transaciton
        hash = b"".join([self.index, self.timestamp.__bytes__(), self.hash, self.pre_hash, self.transaction.__bytes__()])
        return hash

    def __hash__(self):
        # calc hash of block
        hash = b"".join([self.index, self.timestamp.__bytes__(), self.transaction.__bytes__()])
        self.hash = sha256(hash).digest()

    def __str__(self):
        pass

class BLOCKCHAIN(object):
    def __init__(self, path : str):
        # init blockchain
        self.chain  = list()
        # path of file
        self.url    = path
        # check file is exisit and file is exisits get size of file
        if os.path.isfile(self.url):
            self.__size = os.path.getsize(self.url) # get size of file
            # process file 
            self.__process()
        else:
            print("file is not exists !!!")
            return None

    def __genesis_block(self):
        # geensis block will be store filename and extension of file
        filename = os.path.basename(self.url)
        genesis = BLOCK(0, len(filename), filename.encode('utf8'), '0')
        self.chain.append(genesis)
        # return hash of block
        return genesis.hash

    def __add_block(self, length : int, data : bytes, index : int, pre_hash : str):
        # add block normal in chain
        block = BLOCK(index, length, data, pre_hash)
        # put block into chain
        self.chain.append(block)
        # return hash of block
        return block.hash

    def __last_block(self, pre_hash : str):
        # add last block in chain
        last = BLOCK(-1, 3, str('end').encode('utf8'), pre_hash)
        # put last block into chain
        self.chain.append(last)
        # return hash of block
        return last.hash

    def __process(self):
        # function process will convert file to blockchain
        f = open(self.url, 'r')
        index = 1
        # compute time to loop
        step = int(self.__size / DATA_BLOCK_SIZE)
        mod = self.__size - (step * DATA_BLOCK_SIZE)
        print(step)
        # create genesis block
        hash = self.__genesis_block()
        # read file by step
        for i in range(0, step):
            data = f.buffer.read(DATA_BLOCK_SIZE)
            # creat block data 
            hash = self.__add_block(DATA_BLOCK_SIZE, data, index, hash)
            # increase index of block
            index += 1

        # add data residual in block
        residual_data = f.buffer.read(mod)
        # create block data
        hash = self.__add_block(mod, residual_data, index, hash)
        # add last block
        self.__last_block(hash)
        # close file
        f.close()

    def show(self):
        # show info block of chain
        if len(self.chain) > 0:
            block : BLOCK = None
            for block in self.chain:
                print('Hash:\t',    block.hash)
                print('Index:\t',   block.index)
                print('Length:\t',  block.length)
                print('Data:\t',    block.data)
                print('Timestamp:\t',   time.asctime(time.localtime(float(block.timestamp.decode('utf8')))))
                print('Pre-hash:\t',    block.pre_hash)
                print()