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

#define MAX 4096 //stala dl linii 

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
	while(1){
		add = accept(soc, (struct sockaddr*)&cli, &sin_size);
		if(add < 0){
			perror("blad accept");
			exit(EXIT_FAILURE);
		}else{
			int ret;
			int liczba = 0;
			int suma = 0;
			while((ret = read(add, buf, sizeof(buf)-1)) > 0){
					printf("%s\n", buf);
					
					
			}
			//printf("%s\n", buf);
			//send(add, komunikat, 15, 0);
		}
		
		close(add);
	}
	
	close(soc);
	return 0;
}
