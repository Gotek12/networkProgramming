# coding: utf8
from socket import *
s = socket(AF_INET, SOCK_STREAM) #utworzenie gniazda
s.connect(('127.0.0.1', 8888)) # nawiazanie polaczenia
tm = s.recv(1024) #odbior danych (max 1024 bajtów)
s.close()
print ('Czas serwera: ', tm)