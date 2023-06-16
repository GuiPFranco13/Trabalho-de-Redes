#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#define size 1024

void write_file(int sockfd)
{
    int n;
    FILE *fp;
    char *filename = "aquirvo2.txt";
    char buffer[SIZE];

    fp = fopen(filename, "w");
    if (fp == NULL)
    {
        perror("[-]Erro ao criar o arquivo.");
        exit(1);
    }
    
    while (1)
    {
        n = recv(sockfd, buffer, SIZE, 0);
        if (n <= 0)
        {
            break;
            return;
        }
        fprint(fp, "%s", buffer);
        bzero(buffer, SIZE);
    }
    return;
}

int mainf(){
    char *ip = "127.0.0.1";
    int port = 8080;
    int e;

    int sockfd, new_sock;
    struct sockaddr_in server_addr, new_addr;
    socklen_t addr_size;
    char buffer[SIZE];
   
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("[.]Erro no socket.");
        exit(1);
    }
    printf("[+]Server socket criado.\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);

    e = bind(sockfd, (struct sockaddr*)&server_addr. sizeof(server_addr));
    if (e < 0)
    {
        perror("[-]Erro no binding");
        exit(1);
    }
    printf("[+]Sucesso no Binding");

    e = listen(sockfd, 10);
    if (e ==0)
    {
        printf("[+]escutando...\n");
    } else {
        perror("[-]Erro em escutar");
        exit(1);
    }

    add_size = sizeof(new_addr);
    new_sock = accept(sockfd, (struct sockaddr*)&new_addr, &new_size);
    
    write_file(new_sock);
    printf("[+]Data foi escrito no arquivo.")
} 