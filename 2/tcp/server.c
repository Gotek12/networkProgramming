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

int main(int argc, char* argv[]){
	
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
	if(soc == -1){
		perror("blad socketa");
		exit(EXIT_FAILURE);
	}
	
	int bi = bind(soc,( struct sockaddr*)&adres, sizeof(adres));
	if(bi == -1){
		perror("blad bind");
		exit(EXIT_FAILURE);
	}
	
	int lis =  listen(soc, 2);
	if(lis == -1){
		perror("blad lis");
		exit(EXIT_FAILURE);
	}
	
	int add;
	char *komunikat = "Hello, world!\r\n";
	socklen_t sin_size = sizeof( adres );
	while(1){
		printf("Oczekuje na polaczenie\n");

		add = accept(soc, (struct sockaddr*)&adres, &sin_size);
		
		if(add < 0){
			perror("blad accept");
			exit(EXIT_FAILURE);
		}
		
		if(add >=0){
			send(add, komunikat, 15, 0);
			close(add);
			exit(1);
		}
		
	}
	
	//shutdown(soc, SHUT_RDWR);
	close(soc);
	return 0;
}
