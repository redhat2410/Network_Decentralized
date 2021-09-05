import os
import sys
from datetime import datetime
from modules.blockchain import BLOCKCHAIN, DATETIME, TRANSACTION
from modules.filechain import FILECHAIN

# chain = BLOCKCHAIN('/home/ducvu/Desktop/video2.mp4')
# fs = FILECHAIN(chain, 'temp/')

# fs.chain2file()

# date = DATETIME(now = datetime.now())
# buff = date.__bytes__()
# print(len(buff))
# date2 = DATETIME(buff = buff)
# print(date2.__str__())

data = "Hello World"

trans = TRANSACTION(len(data), data.encode('utf8'))
trans.__enc__()
buffer = trans.__bytes__()
trans.__str__()
length = int.from_bytes(buffer[0:2], 'big')
buffer = buffer[2:len(buffer)]
trans2 = TRANSACTION()
trans2.__dec__(buffer, length)
trans2.__str__()