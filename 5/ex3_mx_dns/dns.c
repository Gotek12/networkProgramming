#include <stdio.h>
#include <string.h> 
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <errno.h> 
#include <fcntl.h>
#include "find_mx.h"

/*
**********************************************************
*                                                        *
*                          dns.c                         *
*                  autor: Szymon Peszek                  *
*                                                        *
********************************************************** 
*/

// gcc -std=c99 -pedantic -Wall find_mx.c -c
// gcc -o test dns.c find_mx.o -lresolv -std=c99 -pedantic -Wall

// Potrebne stałe
#define port_TCP 25
#define MAX_BUFF 4096

/** FUNKCJE */
/*
* Funkcja łączy się z serwerem, a następnie drukuje jego wizytówkę
* \param *addr - addres mx, z którym się łączymy
*/
void connect_and_read(char *addr);
/*
* Funkcja drukuje adres lub adresy mx dla danej domeny (o ile ona istnieje)
* \param *temp - adres skrzynki pocztowej
*/
void get_adress(char *temp);

int main(int argc, char * argv[]){
	if (argc < 2) {
        perror("Usage: " );
        printf("%s", argv[0]);
        perror(" domain_or_host_name\n");
        return 1;
    }
    
    int it = 1;
    char pom[128];
	
	while(it < argc){
		char *p = argv[it];
		int pom_it = 0;
		int j = 0;
		
		while(p[pom_it] != '@') pom_it++;
		
		for(int i = pom_it+1; p[i] != '\0'; i++){
			if(p[i] != '@'){
				pom[j] = p[i];
				j++;
			}
		}
		
		get_adress(pom);
		it++;
		printf("\n");
		
		memset(&pom, 0, sizeof(pom));
    }

	return 0;
}

void connect_and_read(char *addr){
	int sock = socket(AF_INET, SOCK_STREAM, 0);
    
	if(sock < 0){
		perror("socket() error");
		exit(EXIT_FAILURE);
	}
	
	char buf[MAX_BUFF];
    struct sockaddr_in adres; 
    adres.sin_family = AF_INET; 
    adres.sin_port = htons(port_TCP); 
    adres.sin_addr.s_addr = inet_addr(addr); 


    if(connect(sock, (struct sockaddr*)&adres, sizeof(struct sockaddr)) < 0){
		perror("connect() error()");
		exit(EXIT_FAILURE);
	}

    if(read(sock, buf, sizeof(buf)) < 0){
		perror("read() error()");
		exit(EXIT_FAILURE);
	}
    else printf("   wizytowka: %s", buf);
    
    memset(&buf, 0, sizeof(buf));
	close(sock);
}

void get_adress(char *temp){
	struct in_addr * adresses = find_mail_exchanges(temp);
	
    if (adresses == NULL) {
        exit(EXIT_FAILURE);
    }
    
    char buf[INET_ADDRSTRLEN];
    
    printf("For: %s\n", temp);

    for(int i = 0; adresses[i].s_addr != htonl(INADDR_ANY); ++i){
        if(inet_ntop(AF_INET, adresses + i, buf, sizeof(buf)) == NULL){
            perror("inet_ntop() error");
            exit(EXIT_FAILURE);
        }

        printf("%s", buf);
        connect_and_read(buf);
    }
    
    free(adresses);
}
