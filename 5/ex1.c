#include <stdio.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char **argv) {
    struct hostent *tmp = 0;
    
    int i = 0;

    if (argc < 2) {
        printf("Usage: %s <hostname>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    tmp = gethostbyname(argv[1]);

    if (!tmp) {
        printf("Lookup Failed: %s\n", hstrerror(h_errno));
         return 0;
    }
    printf("h_name: %s\n", tmp->h_name);

    i = 0;
    while(tmp->h_aliases[i] != NULL) {
        printf("h_aliases[i]: %s\n", tmp->h_aliases[i]);
        i++;
    }

    i = 0;
    while(tmp->h_addr_list[i] != NULL) {
        printf("h_addr_list[%d]: %s\n", i, inet_ntoa( (struct in_addr) *((struct in_addr *) tmp->h_addr_list[i])));
        i++;
    }

    return 0;
}