import os
import sys
import time
from modules.blockchain import BLOCKCHAIN, BLOCK

class FILECHAIN(object):
    def __init__(self, chain : BLOCKCHAIN, folder : str):
        self.chain : BLOCKCHAIN = chain
        # data will be write in folder
        self.folder = folder

    def chain2file(self):
        if len(self.chain.chain) > 0:
            block : BLOCK = None
            for block in self.chain.chain:
                # create shortcut file with first block
                if int.from_bytes(block.index, 'big') == 0:
                    filename = os.path.basename(self.chain.url).split('.')[0] + ".sha"
                    f = open(os.path.join(self.folder, filename), 'w')
                    f.buffer.write(block.__bytes__())
                    f.close()
                    # print(len(block.__bytes__()))
                else:
                    filename = block.pre_hash.hex() + ".sha"
                    f = open(os.path.join(self.folder, filename), 'w')
                    f.buffer.write(block.__bytes__())
                    f.close()
                    # print(len(block.__bytes__()))

    def __readfileSHA(self, url : str):
        f = open(url, 'r')
        buff = f.buffer.read()
        f.close() # close file and process data
        block = BLOCK(buffer = buff)
        return block

    def file2chain(self, shortcut : str):
        # check file shortcut is exists
        if os.path.isfile(shortcut) == False:
            print("Shortcut file is not exists !!!!")
            return None
        # read file shortcut and convert to genesis block
        block = self.__readfileSHA(shortcut)
        self.chain.__genesis_block(genesis=block)
        # continue read file 
        is_exit = False
        while not is_exit:
            # gen path file from hash of previous block
            path = self.folder + block.hash.hex() + '.sha'
            if os.path.isfile(path):
                block = self.__readfileSHA(path)
                # check block is last block by index
                if int.from_bytes(block.index, 'big', signed=True) == -1:
                    self.chain.__last_block(block)
                    is_exit = True
                else:
                    self.chain.__add_block(block)
            else:
                is_exit = True # set flag for exit loop

        # done convert file to chain

