# -*- coding: utf-8 -*-

import base64
import struct
import binascii
import ctypes
import os.path


RES_PATH = "../Resources";

# 获取所有png文件base64编码后的总大小

size = 0

for dirpath, dirnames, filenames in os.walk(RES_PATH):
    for filename in filenames:
        if (os.path.splitext(filename)[1] == ".png"):
            with open(os.path.join(dirpath,filename), 'rb') as image_file:
                size += len(base64.b64encode(image_file.read()))

print "total size=",size



# png索引文件 (filename,offset,size)
indexFile = open("png.idx","wb")

# 全部图片的缓存数据
prebuffer = ctypes.create_string_buffer(size);

offset = 0

for dirpath, dirnames, filenames in os.walk(RES_PATH):
    for filename in filenames:
        if (os.path.splitext(filename)[1] == ".png"):
            with open(os.path.join(dirpath,filename), 'rb') as image_file:
                # base64编码
                encoded_string = base64.b64encode(image_file.read())
                # 编码长度
                length = len(encoded_string)
                # 索引信息
                a = [os.path.join(dirpath.replace(RES_PATH,''),filename), ',', str(offset), ',', str(length), '\n']
                indexInfo = '%s%s%s%s%s%s' % tuple(a)
                print indexInfo
                #写入索引文件
                indexFile.write(indexInfo)
                #添加到数据缓存
                s = struct.Struct(str(length)+'s')
                s.pack_into(prebuffer, offset, encoded_string)
                offset += s.size

indexFile.close()

# 写入二进制文件
binfile = open("bin","wb")
binfile.write(prebuffer)
binfile.close()