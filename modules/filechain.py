import os
import sys
import time
from modules.blockchain import BLOCKCHAIN, BLOCK

class FILECHAIN(object):
    def __init__(self, chain : BLOCKCHAIN, folder : str):
        self.chain = chain
        # data will be write in folder
        self.folder = folder

    def chain2file(self):
        if len(self.chain.chain) > 0:
            block : BLOCK = None
            for block in self.chain.chain:
                # create shortcut file with first block
                if int(block.index.decode('utf8')) == 0:
                    filename = os.path.basename(self.chain.url).split('.')[0] + ".sha"
                    f = open(os.path.join(self.folder, filename), 'w')
                    f.buffer.write(block.__bytes__())
                    f.close()
                    # print(len(block.__bytes__()))
                else:
                    filename = block.pre_hash + ".sha"
                    f = open(os.path.join(self.folder, filename), 'w')
                    f.buffer.write(block.__bytes__())
                    f.close()
                    # print(len(block.__bytes__()))

