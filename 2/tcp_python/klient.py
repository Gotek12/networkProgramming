# coding: utf8
from socket import *
import sys

IP = sys.argv[1]
PORT = int(sys.argv[2])
BUFF = 1024

soc = socket(AF_INET, SOCK_STREAM) #utworzenie gniazda
soc.connect((IP, PORT)) # nawiazanie polaczenia
tm = soc.recv(BUFF) #odbior danych (max 1024 bajtów)
soc.close()
print tm