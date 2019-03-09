import socket
import sys

IP = sys.argv[1]
PORT = int(sys.argv[2])
BUFF = 1024


sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)  
msg = "Test!"
sock.sendto(msg,(IP,PORT))

data,addr = sock.recvfrom(BUFF)
print data