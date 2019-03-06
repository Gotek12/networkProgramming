#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <sys/types.h>
#include<errno.h> 

int main(int argc, char* argv[]){
	
	char* odczyt = argv[1];
	char* zapis = argv[2];
	char buf[50];
	int czytaj;

	if(argc < 3){
		perror("Bledna ilosc argumetow\n");
        exit(EXIT_FAILURE);
	}
	
	//open to read
	int otw = open(odczyt, O_RDONLY);
	if(otw == -1){
        perror("Problem z otwarciem pliku do odczytu\n");
        exit(EXIT_FAILURE);
    }
	//open to write
	int otw2 = open(zapis, O_WRONLY | O_CREAT ,0666);
	if(otw2 == -1){
        perror("Problem z otwarciem pliku do zapisu\n");
        exit(EXIT_FAILURE);
    }

    int ct = 1;
	while((czytaj = read(otw, buf, 1)) > 0){
        //printf("%s", buf);
        int i = 0;
        if(buf[i] == 10){
            ct++;
        }

        if(ct%2 != 0){
            write(otw2, buf, 1);
        }
	}

	if(czytaj == -1){
        perror("Problem zczytywaniem pliku\n");
        exit(EXIT_FAILURE);
    }
	if(close(otw) == -1){
        perror("Problem z zamknieciem pliku\n");
        exit(EXIT_FAILURE);
    }
}
