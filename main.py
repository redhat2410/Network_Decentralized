from hashlib import sha256
import os
import sys
from datetime import datetime
from modules.blockchain import BLOCKCHAIN, DATETIME, TRANSACTION, BLOCK
from modules.filechain import FILECHAIN

# chain = BLOCKCHAIN('/home/ducvu/Desktop/hello.txt')
# chain.show()
# fs = FILECHAIN(chain, 'temp/')
# fs.chain2file()

chain = BLOCKCHAIN()

fs = FILECHAIN(chain, 'temp/')
fs.file2chain('temp/hello.sha')

chain.show()

# date = DATETIME(now = datetime.now())
# buff = date.__bytes__()
# print(len(buff))
# date2 = DATETIME(buff = buff)
# print(date2.__str__())

# data = "Hello World"

# b = BLOCK(1, len(data), data.encode('utf8'), sha256(data.encode('utf8')).digest())
# print(b.__bytes__())