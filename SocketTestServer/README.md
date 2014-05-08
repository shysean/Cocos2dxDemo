SocketTestServer
============

使用方法:
unzip echo-server.ruby.zip 
ruby echo-server.ruby

客户端（使用 telnet)
telnet localhost 1234
输入命令：

#1 重复echo repeat (your-string) (repeat-count) 
repeat a 1000

#2 下发段数据 multi (total size) (block size)
multi 10240 1000

#2 下发int / short number (type) (value)
number int 123400
number short 1234