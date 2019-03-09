import socket
import sys

PORT = int(sys.argv[1])
MESSAGE = 'Hello world\n\r'
BUFF = 1024
ADDRESS = ('', PORT)

soc = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
soc.bind(ADDRESS)

while True:
    print "Waiting for client..."
    data, addr = soc.recvfrom(BUFF)
    print "Received Messages:",data," from",addr

    if data:
        soc.sendto(MESSAGE, addr)
