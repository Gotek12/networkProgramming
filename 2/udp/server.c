//serwer udp
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
	int add;
	char *komunikat = "Hello, world!\r\n";
	
	struct sockaddr_in adres, klientadr; 
	adres.sin_family = AF_INET; 
  adres.sin_port = htons(port); 
	adres.sin_addr.s_addr = htonl(INADDR_ANY); 
	socklen_t sin_size = sizeof( adres );
  
	int soc = socket(AF_INET, SOCK_DGRAM, 0);
	if(soc == -1){
		perror("blad socketa");
		exit(EXIT_FAILURE);
	}
	
	int bi = bind(soc,( struct sockaddr*)&adres, sizeof(adres));
	if(bi == -1){
		perror("blad bind");
		exit(EXIT_FAILURE);
	}
	
	char buffer[100]; 
	int len;
	while(1){
		printf("Waiting for info..\n");
		memset(buffer, 0, sizeof( buffer ) );

		if(recvfrom(soc, (char *)buffer, sizeof(buffer)-1, 0, ( struct sockaddr *) &klientadr, &len) < 0){
			perror("blad recfrom");
			exit(EXIT_FAILURE);
		}
		printf("Client : %s\n", buffer); 

		//MSG_CONFIRM
		if(sendto(soc, (const char *)komunikat, strlen(komunikat), 0, (const struct sockaddr *) &klientadr, len) < 0){
			perror("blad sendto");
			exit(EXIT_FAILURE);
		}else{
			exit(1);
		}
		printf("Hello message sent.\n");
	}
	close(soc);
	return 0;
}
