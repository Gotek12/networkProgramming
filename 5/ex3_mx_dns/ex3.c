// gcc -std=c99 -pedantic -Wall find_mx.c -c
// gcc -o 3 ex3.c find_mx.o -lresolv -std=c99 -pedantic -Wall
// example ./3 a@uj.edu.pl a@gmail.com asdeee@interia.pl
// example2 ./3 onet.pl  ala@gmail.com @yahoo.com
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
#define PORT 25
#define BUFF_SIZE 4096
int counter = 0;

void przywitania(char *ip){
	
	char buf[BUFF_SIZE];

    struct sockaddr_in adres; 
        adres.sin_family = AF_INET; 
        adres.sin_port = htons(PORT); 
        adres.sin_addr.s_addr = inet_addr(ip); 

    int soc = socket(AF_INET, SOCK_STREAM, 0);
	if(soc < 0){
		perror("blad socketa");
		exit(EXIT_FAILURE);
	}

    int con = connect(soc,(struct sockaddr*)&adres, sizeof(struct sockaddr));
    if(con < 0){
		perror("blad connect");
		exit(EXIT_FAILURE);
	}
    
    read(soc, buf, sizeof(buf));
    printf("%s\n", buf);

    sleep(1);
    memset(&buf, 0, sizeof(buf));
	close(soc);
}

void mxFind(char *t){
    printf("\n[ %s ]\n\n", t);
    struct in_addr * adresses = find_mail_exchanges(t);

    if (adresses == NULL) {
        return;
    }

    char buf[INET_ADDRSTRLEN];
    for(int i = 0; adresses[i].s_addr != htonl(INADDR_ANY); ++i) {
        if (inet_ntop(AF_INET, adresses + i, buf, sizeof(buf)) == NULL) {
            perror("inet_ntop");
            return;
        }
        printf("%s\n", buf);
        przywitania(buf);

    }
    free(adresses);
}

int main(int argc, char **argv) {
    char *domains[argc];
    //jesli pusty to error
    if (argc < 2) {
        printf("Brak argumentow\n");
        exit(EXIT_FAILURE);
    }

    //wpisujemy wszystkie wpisane emaily jako arg do tablicy emailow
    char *emailsTab[argc];
    int i = 1;
    for (; i < argc; ++i){
        emailsTab[i] = argv[i];
    }

    //czytamy same domeny
    int j = 1;
    char tmp[50];
    for(; j < argc; j++){
        memset(&tmp, 0, sizeof(tmp));
        char *p = emailsTab[j];
        int licz = 0;
        int k, z = 0;

        while(p[licz] != '@' && p[licz] != '\0'){    
            licz++;
        }

        if(p[licz] != '@'){
            licz = -1;
        }

        for(k = licz+1; p[k] != '\0'; k++){
            tmp[z] = p[k];
            z++;
        }

        domains[j] = malloc(50*sizeof(char));
        strcpy(domains[j], tmp);

        //sprawdzamy czy powtarzają się domeny
        bool test = false;
        for(int q = 1; q < j ; q++){
            if(strcmp(tmp, domains[q]) == 0){
                test = true;
            }
        }
        
        if(!test){
            mxFind(tmp);
        }
        
    }

    return 0;
}

