//https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h> 
#include <netinet/in.h>
#include <limits.h>

//#define MAX 4096 //stala dl linii 
#define MAX 20 //stala dl linii 

int extractNum(char linia[]);
char* itoa(int value, char* result, int base);

//ncat -v -C 127.0.0.1 8888
int main(int argc, char* argv[]){
	char buf[MAX];
	
	if(argc != 2){
		perror("Bledna ilosc argumetow\n");
    exit(EXIT_FAILURE);
	}
	
	int port = atoi(argv[1]);	
	
	struct sockaddr_in adres, cli; 
		adres.sin_family = AF_INET; 
		adres.sin_port = htons(port); 
		adres.sin_addr.s_addr = htonl(INADDR_ANY); 
  
	int soc = socket(AF_INET, SOCK_STREAM, 0);
	if(soc < 0){
		perror("Blad socketa");
		exit(EXIT_FAILURE);
	}
	
	if(bind(soc,( struct sockaddr*)&adres, sizeof(adres)) < 0){
		perror("Blad bind");
		exit(EXIT_FAILURE);
	}
	
	if(listen(soc, 1) < 0){
		perror("Blad listen");
		exit(EXIT_FAILURE);
	}
	
	int add;
	socklen_t sin_size = sizeof( cli );
	
	printf("Oczekuje na polaczenie... \n");
	
	add = accept(soc, (struct sockaddr*)&cli, &sin_size);
	if(add < 0){
		perror("blad accept");
		exit(EXIT_FAILURE);
	}
	
	int licz = 0;
	while(1){	
		read(add, buf, sizeof(buf));
		licz = extractNum(buf);
		//printf("%d\n", licz)
		send(add, itoa(licz, buf, 10), sizeof(itoa(licz, buf, 10)), 0);
		memset(&buf, 0, sizeof(buf));	
	}
	
	close(soc);
	return 0;
}

int overFlow(int a, int b){
	if(a > INT_MAX -b){
		return -1;
	}
	return 0;
}

//funkcja czytajaca liczby z bufora
int extractNum(char linia[]){
	const char *p = linia;
	int suma = 0, liczba = 0;
	int i;
	
	for(i = 0; i < strlen(linia); i++){
		
		if(*p == ' '){

			if(overFlow(suma, liczba) < 0){
				printf("ERROR\n");
			}

			suma += liczba;
			liczba = 0; //zerujemy
			p++;

		}else{

			liczba = 10 * liczba + *p - '0';
			p++;

		}

	}

	return suma;
}

void swap(char *x, char *y) {
	char t = *x; *x = *y; *y = t;
}
char* reverse(char *buffer, int i, int j)
{
	while (i < j)
		swap(&buffer[i++], &buffer[j--]);

	return buffer;
}

char* itoa(int value, char* buffer, int base)
{
	// invalid input
	if (base < 2 || base > 32)
		return buffer;

	// consider absolute value of number
	int n = abs(value);

	int i = 0;
	while (n)
	{
		int r = n % base;

		if (r >= 10) 
			buffer[i++] = 65 + (r - 10);
		else
			buffer[i++] = 48 + r;

		n = n / base;
	}

	if (i == 0)
		buffer[i++] = '0';

	if (value < 0 && base == 10)
		buffer[i++] = '-';

	buffer[i] = '\0'; // null terminate string

	return reverse(buffer, 0, i - 1);
}