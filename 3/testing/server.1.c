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

#define MAX 4096 //stala dl linii 
#define ERR "ERROR\r\n"

int extractNum(char linia[]);
char* itoa(int value, char* result);
char* reverse(char *buffer, int i, int j);

//ncat -v -C 127.0.0.1 8888
int main(int argc, char* argv[]){
	char buf[MAX];
	
	if(argc != 2){
		perror("Bledna ilosc argumetow\n");
    exit(EXIT_FAILURE);
	}
	
	int port = atoi(argv[1]);	
	
	struct sockaddr_in adres; 
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
	struct sockaddr_in clientAdd = {0};

	socklen_t sin_size = sizeof( clientAdd );
	add = accept(soc, (struct sockaddr*)&clientAdd, &sin_size);
	if(add < 0){
		perror("blad accept");
		exit(EXIT_FAILURE);
	}
	
	printf("Oczekuje na polaczenie... \n");
	
	int licz = 0;
    char *komErr = ERR;
	while(1){	

		int re = read(add, buf, sizeof(buf));
		printf("%d\n", re);
		if(re == 2){
			continue;
		}

		licz = extractNum(buf);
		
        if(licz < 0){
            send(add, komErr, sizeof(komErr), 0);
        }else{
            char *tmp = itoa(licz, buf);
            send(add, tmp, sizeof(tmp), 0);
        }
		memset(&buf, 0, sizeof(buf));

	}
	
	close(add);
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
		
        
        //jesli pierwszy el to spacja
        if(i == 0 & p[i] == ' '){
            return -1;
        }

        //jesli rozna od \n \r spacja i 0-9
        if(!(*p >= '0' && *p <= '9') & (*p != ' ') & *p != '\r' & *p != '\n'){
            return -1;
        }

        //jesli wiecej niz 2 spacje to err
        if(*p == ' ' & *(p+1) == ' '){
            return -1;
        }

		if(*p == ' '){

			if(overFlow(suma, liczba) < 0){
				return -1;
			}

			suma += liczba;
			liczba = 0;
			p++;

		}else{

			liczba = 10 * liczba + *p - '0';
			p++;

		}

	}
	return suma;
}

//ZMIANA INT TO CHAR
char* reverse(char *buffer, int i, int j){
	while (i < j){
        char *x = &buffer[i++];
        char *y = &buffer[j--];

        char t = *x; 
        *x = *y; 
        *y = t;
    }
		
	return buffer;
}

char* itoa(int value, char* buffer)
{
    int base = 10;
	int n = abs(value);
	int i = 0;

	while (n){
		int r = n % base;

		if (r >= 10) {
            buffer[i++] = 65 + (r - 10);
        }else{
            buffer[i++] = 48 + r;
        }
		n /= base;
	}

	if (i == 0){
        buffer[i++] = '0';
    }

    buffer[i] = '\0'; // null terminate string
    buffer[i+1] = '\r';
    buffer[i+2] = '\n';
	

	return reverse(buffer, 0, i - 1);
}