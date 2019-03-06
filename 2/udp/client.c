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
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char* argv[]){
	
	if(argc != 3){
		perror("Bledna ilosc argumetow\n");
        exit(EXIT_FAILURE);
	}
	
	char ad = *argv[1];	
	int port = atoi(argv[2]);	
	char buf[1024];
	
	struct sockaddr_in adres; 
	memset(&adres, 0, sizeof(adres));
	adres.sin_family = AF_INET; 
  adres.sin_port = htons(port); 
 	adres.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    
	int soc = socket(AF_INET, SOCK_DGRAM, 0);
	if(soc == -1){
		perror("blad socketa");
		exit(EXIT_FAILURE);
	}
	
	int n, len; 
	char *hello = "test\n\r";
	if(sendto(soc, (const char *)hello, strlen(hello), 0, (const struct sockaddr *) &adres, sizeof(adres)) < 0){
		perror("blad sendto");
		exit(EXIT_FAILURE);
	}

	memset(buf, 0, sizeof( buf ) );
	struct sockaddr_in from = { };
	if(recvfrom(soc, buf, sizeof(buf), 0,(struct sockaddr *) & from, & len ) < 0 ){
    perror( "blad recvfrom" );
  	exit(EXIT_FAILURE);
  }
  printf("%s \n", buf );

	close(soc);
	return 0;
}
