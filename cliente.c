#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;
    int pv; // Pontos de vida do jogador

    clientSocket = socket(PF_INET, SOCK_STREAM, 0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(1234);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

    if (connect(clientSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) {
        perror("Connect falhou");
        exit(1);
    }

    while (1) {
    int elemento, acao, pv;

    recv(clientSocket, &pv, sizeof(pv), 0);
    if (pv <= 0) {
        printf("Você perdeu!\n");
        break;
    }

    printf("Seus pontos de vida: %d\n", pv);

    printf("Escolha um elemento (1- Água, 2- Terra, 3- Fogo, 4- Ar): ");
    scanf("%d", &elemento);
    send(clientSocket, &elemento, sizeof(elemento), 0);

    printf("Escolha uma ação (1- Atacar, 2- Defender): ");
    scanf("%d", &acao);
    send(clientSocket, &acao, sizeof(acao), 0);

    // [Receba o resultado do servidor e imprima para o jogador]

    printf("Esperando a escolha do oponente...\n");
    // [Receba as escolhas do oponente e imprima para o jogador]
}

close(clientSocket);

return 0;
}