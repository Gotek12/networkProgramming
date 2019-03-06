#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>
#include <stdbool.h>

bool drukowalne(const void * buf, int len){
	int i;
	for(i = 0; i < len; i++){
		unsigned int znak = (int)buf;
		if(znak >= 32 || znak <= 126){
			return true;
		}	
	}
	return false;
}

bool drukowalnewsk(const void * buf, int len){
	const char *poczatek = buf;
	for(; poczatek != 0; poczatek++){
		if(*poczatek >= 32 || *poczatek <= 126){
			return true;
		}
	}
}

int main(int argc, char* argv[]){
	
	
	if(drukowalne("abcde23", 7)){
		printf("yes\n");
	}else{
		printf("no\n");
	}

	if(drukowalnewsk("abcde23", 7)){
		printf("yes wsk\n");
	}else{
		printf("no wsk\n");
	}

	return 0;
}
