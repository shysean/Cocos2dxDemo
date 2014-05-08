require 'socket'

#
# Method 
# *Note: must before the main
# 
def handleRepeat(conn, content, repeatCount)
	count = repeatCount.to_i
	result = content * count

	conn.send(result, 0)
end

def createBuffer(symbol, repeatCount) 
	result = symbol * repeatCount


	return result
end

def handleMultiSend(conn, totalSize, bufferSizeStr)
	symbolArray = "abcdefg"

	bufferSize = bufferSizeStr.to_i
	remain = totalSize.to_i
	idx = 0

	while(remain > 0) 
		size = (remain < bufferSize) ? remain : bufferSize
		symbol = symbolArray[idx % 7].chr

		buffer = createBuffer(symbol, size)

		puts "size=#{size} idx=#{idx} symbol=#{symbol}"
		conn.send(buffer, 0)
		
		remain -= bufferSize
		idx = idx + 1
	end	
	
#	result = ""
#	conn.send(result, 0)
end

def handleEchoNumber(conn, type, valueStr)
	intValue = valueStr.to_i
	dataArray = [intValue]

	
	if (type == "int") 
		packType = 'N*'		# big-endian
	elsif (type == "int-l") 
		packType = 'V*'		# little-endian
	elsif (type == "short")
		packType = 'n*'
	else 
		dataArray = [0x61, 0x66, 0x63]
		packType = 'N'
	end
	
	buffer = dataArray.pack(packType)
	puts "buffer=#{buffer} size=#{buffer.length}"
	conn.send(buffer, 0)
end


def handleCommand(cmdLine, conn) 
	cmdLine = cmdLine.chomp
	puts "Received [" + cmdLine + "]"


	cmdTokens = cmdLine.split(' ')
	cmd = cmdTokens[0]
	arg1 = cmdTokens[1]
	arg2 = cmdTokens[2]

	result = ""
	puts "cmd: #{cmd} arg1=#{arg1}"
	if (cmd == "repeat")
		handleRepeat(conn, arg1, arg2)
	elsif (cmd == "multi")
		handleMultiSend(conn, arg1, arg2)
	elsif (cmd == "number")
		handleEchoNumber(conn, arg1, arg2)
	else 
		conn.send(cmdLine, 0)
	end

end



# --------------------------------------
# Main 

server = TCPServer.new(1234)
 
while (connection = server.accept)

  Thread.new(connection) do |conn|

    port, host = conn.peeraddr[1,2]
    client = "#{host}:#{port}"

    puts "#{client} is connected"
    begin
      loop do
	    
        line = conn.readline

        puts "#{client} says: #{line}"
		handleCommand(line, conn);

      end

    rescue EOFError
      conn.close
      puts "#{client} has disconnected"
    end
  end
end


