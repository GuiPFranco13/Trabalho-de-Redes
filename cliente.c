#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define SIZE 1024

void send_file(FILE *fp, int sockfd){
    char data[SIZE] = {0};

    while(fgets(data, SIZE, fp) !=NULL){
        if (send(sockfd, data, sizeof(data), 0) == -1)
        {
            perror("[-]Erro em enviar data");
            exit(1);
        }
        bzero(data, SIZE);
    }
}

int main(){

    char *ip="127.0.0.1";
    int port = 8080;
    int e;

    int sockfd;
    struct sockaddr_in server_addr;
    FILE *fp;
    char *filename = "arquivo.txt";

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
    e = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if(e == -1)
    {
        perror("[-]Erro na conexão");
        exit(1);
    }
    printf("[+]Conectado ao servidor.\n");

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        perror("[-]Erro ao ler o arquivo.");
        exit(1);
    }
    
    send_file(fp, sockfd);
    printf("[+]File data enviado com sucesso.\n");

    close(sockfd);
    printf("[+]Desconectado do servidor")
}