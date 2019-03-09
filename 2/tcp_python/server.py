#https://rk.edu.pl/pl/python-i-programowanie-sieciowe/
from socket import *
import sys

PORT = int(sys.argv[1])
MESSAGE = 'Hello world\n\r'

s = socket(AF_INET, SOCK_STREAM) #utworzenie gniazda
s.bind(('', PORT)) #dowiazanie do portu 8888
s.listen(1)

while 1:
	client,addr = s.accept() # odebranie polaczenia
	print 'Polaczenie z ', addr
	client.send(MESSAGE) # wyslanie danych do klienta
	client.close()

sys.exit()