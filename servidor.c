#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

// Função para calcular o resultado do combate
int combateElementos(int elementoJogador, int elementoOponente) {
    if (elementoJogador == elementoOponente) return 0; // Empate
    if ((elementoJogador == 1 && elementoOponente == 4) ||
        (elementoJogador == 2 && elementoOponente == 1) ||
        (elementoJogador == 3 && elementoOponente == 2) ||
        (elementoJogador == 4 && elementoOponente == 3)) {
        return -1; // Jogador perde PV
    }
    return 1; // Oponente perde PV
}

int main() {
    int serverSocket, clientSocket1, clientSocket2, addrSize;
    struct sockaddr_in serverAddr, clientAddr;
    int pv1 = 100, pv2 = 100; // Pontos de vida dos jogadores

    serverSocket = socket(PF_INET, SOCK_STREAM, 0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(1234);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

    if (bind(serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) {
        perror("Bind falhou");
        exit(1);
    }

    if (listen(serverSocket, 5) < 0) {
        perror("Listen falhou");
        exit(1);
    }

    printf("Aguardando conexão do Jogador 1...\n");
    addrSize = sizeof(clientAddr);
    clientSocket1 = accept(serverSocket, (struct sockaddr *) &clientAddr, &addrSize);
    printf("Jogador 1 conectado.\n");

    printf("Aguardando conexão do Jogador 2...\n");
    clientSocket2 = accept(serverSocket, (struct sockaddr *) &clientAddr, &addrSize);
    printf("Jogador 2 conectado.\n");

    while (1) {
    int elemento1, elemento2, acao1, acao2, resultado;

    send(clientSocket1, &pv1, sizeof(pv1), 0);
    send(clientSocket2, &pv2, sizeof(pv2), 0);

    if (pv1 <= 0) {
        printf("Jogador 1 perdeu!\n");
        break;
    }
    if (pv2 <= 0) {
        printf("Jogador 2 perdeu!\n");
        break;
    }

    // Recebendo escolhas do Jogador 1
    recv(clientSocket1, &elemento1, sizeof(elemento1), 0);
    printf("Jogador 1 escolheu o elemento: %d\n", elemento1);
    recv(clientSocket1, &acao1, sizeof(acao1), 0);
    printf("Jogador 1 escolheu a ação: %d\n", acao1);

    // Recebendo escolhas do Jogador 2
    recv(clientSocket2, &elemento2, sizeof(elemento2), 0);
    printf("Jogador 2 escolheu o elemento: %d\n", elemento2);
    recv(clientSocket2, &acao2, sizeof(acao2), 0);
    printf("Jogador 2 escolheu a ação: %d\n", acao2);

    resultado = combateElementos(elemento1, elemento2);

    if (acao1 == 1 && acao2 == 2) resultado = 0;
    if (acao1 == 2 && acao2 == 1) resultado = -1;

    if (resultado == 1) {
        pv2 -= 10; // Jogador 2 perde PV
        printf("Jogador 1 ganha esta rodada. PV do Jogador 2: %d\n", pv2);
    } else if (resultado == -1) {
        pv1 -= 10; // Jogador 1 perde PV
        printf("Jogador 2 ganha esta rodada. PV do Jogador 1: %d\n", pv1);
    } else {
        printf("Empate nesta rodada. PVs mantidos.\n");
    }
}

close(clientSocket1);
close(clientSocket2);
close(serverSocket);

return 0;
}