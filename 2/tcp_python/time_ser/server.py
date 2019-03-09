#https://rk.edu.pl/pl/python-i-programowanie-sieciowe/
from socket import *
import time
s = socket(AF_INET, SOCK_STREAM) #utworzenie gniazda
s.bind(('', 8888)) #dowiazanie do portu 8888
s.listen(5)

while 1:
	client,addr = s.accept() # odebranie polaczenia
	print 'Polaczenie z ', addr
	client.send(time.ctime(time.time())) # wyslanie danych do klienta
	client.close()