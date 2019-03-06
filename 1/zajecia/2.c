#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>
#include <stdbool.h>

bool drukowalne(const char * buf){
	int i;
	for(i = 0; i < strlen(buf); i++){
		unsigned int znak = buf[i];
		if(znak >= 32 || znak <= 126){
			return true;
		}
	}
	return false;
}

bool drukowalnewsk(const char * buf){
	int i;
	/*for(i = 0; i < strlen(buf); i++){
			if((*buf + i) >= 32 || (*buf + i) <= 126){
					return true;
			}
	}*/
	
	const char *poczatek = buf;
	for(; poczatek != 0; poczatek++){
		if(*poczatek >= 32 || *poczatek <= 126){
			return true;
		}
	}
   
	return false;
}

int main(int argc, char* argv[]){
	if(drukowalnewsk("abcde23")){
		printf("yes wsk\n");
	}else{
		printf("no wsk\n");
	}
	
	if(drukowalne("abcde23")){
		printf("yes\n");
	}else{
		printf("no\n");
	}
	
}
