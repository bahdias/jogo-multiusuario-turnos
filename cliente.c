#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Definição de elementos e suas vantagens
#define FOGO 1
#define AGUA 2
#define TERRA 3
#define AR 4

int ataque_jogador(int elemento_jogador[], int posicao1, int posicao2, int defendeu) {
    //Danos que serão realizados ao oponente com base no tipo de ataque do jogador
    if ((elemento_jogador[posicao1] == FOGO && elemento_jogador[posicao2] == TERRA) ||
        (elemento_jogador[posicao1] == AGUA && elemento_jogador[posicao2] == FOGO) ||
        (elemento_jogador[posicao1] == TERRA && elemento_jogador[posicao2] == AR) ||
        (elemento_jogador[posicao1] == AR && elemento_jogador[posicao2] == AGUA)) {
        // Ataque Forte
        if (defendeu == 1){
            printf("Jogador %d realizou um ataque forte! -2 pontos pro Jogador %d que se defendeu do ataque\n", posicao1 + 1, posicao2 + 1);
            return 2; // Retorna 2 para indicar ataque forte, mas com defesa do oponente
        }else{
            printf("Jogador %d realizou um ataque forte! -3 pontos pro Jogador %d que nao se defendeu do ataque\n", posicao1 + 1, posicao2 + 1);
            return 3; // Retorna 3 para indicar ataque forte, sem defesa do oponente
        }
        
    } else if ((elemento_jogador[posicao1] == FOGO && elemento_jogador[posicao2] == AGUA) ||
               (elemento_jogador[posicao1] == AGUA && elemento_jogador[posicao2] == TERRA) ||
               (elemento_jogador[posicao1] == TERRA && elemento_jogador[posicao2] == AR) ||
               (elemento_jogador[posicao1] == AR && elemento_jogador[posicao2] == FOGO)) {
        // Ataque Regular
        if (defendeu == 1){
            printf("Jogador %d realizou um ataque regular. -1 pontos pro Jogador %d que se defendeu do ataque\n", posicao1 + 1, posicao2 + 1);
            return 1; // Retorna 1 para indicar ataque regular, mas com defesa do oponente
        }else{
            printf("Jogador %d realizou um ataque regular. -2 pontos pro Jogador %d que nao se defendeu do ataque\n", posicao1 + 1, posicao2 + 1);
            return 2; // Retorna 2 para indicar ataque regular, sem defesa do oponente
        }
    } else if ((elemento_jogador[posicao1] == FOGO && elemento_jogador[posicao2] == AR) ||
              (elemento_jogador[posicao1] == AGUA && elemento_jogador[posicao2] == TERRA) ||
              (elemento_jogador[posicao1] == TERRA && elemento_jogador[posicao2] == FOGO) ||
              (elemento_jogador[posicao1] == AR && elemento_jogador[posicao2] == AGUA)) {
        // Ataque Fraco (quando nenhum dos casos acima se aplica)
        if (defendeu == 1){
            printf("Jogador %d realizou um ataque fraco. -0 pontos pro Jogador %d que se defendeu do ataque\n", posicao1 + 1, posicao2 + 1);
            return 0; // Retorna 0 para indicar ataque fraco, mas com defesa do oponente
        }else{
            printf("Jogador %d realizou um ataque fraco. -1 ponto pro Jogador %d que nao se defendeu do ataque\n", posicao1 + 1, posicao2 + 1);
            return 1; // Retorna 1 para indicar ataque fraco, sem defesa do oponente
        }
    } else{
        printf("Jogador %d realizou um ataque nulo\n", posicao1 + 1);
        return 0; //Ataque nulo
    }
}

int main() {
    int pv_jogador[2] = {20, 20}; //Todos os jogadores começam com 20 pontos de vida
    int elemento_jogador[2] = {0, 0}; //Lista para guardar o elemento escolhido pelos jogadores
    int acao_jogador[2] = {0,0}; //Ação que os jogadores irão escolher (Ataque/Defesa)

    srand(time(NULL)); // Inicializa o gerador de números aleatórios
    printf("Bem-vindo a Batalha dos Elementos!\n");

    while (pv_jogador[0] > 0 && pv_jogador[1] > 0) {
        // Embaralhe os elementos aleatoriamente para ambos os jogadores
        int elementos_disponiveis[4] = {FOGO, AGUA, TERRA, AR}; //Os 4 elementos disponíveis
        int defendeu[2] = {0,0}; // false (não defende)
        for (int i = 0; i < 2; i++) {
            //for para gerar o elemento aleatório para cada jogador
            int indice_aleatorio = rand() % 4;
            elemento_jogador[i] = elementos_disponiveis[indice_aleatorio];
            // Remove o elemento escolhido do vetor
            for (int j = indice_aleatorio; j < 3; j++) {
                elementos_disponiveis[j] = elementos_disponiveis[j + 1];
            }
        }

        // Turno do Jogador 1
        printf("Elemento Jogador 1: ");
        if (elemento_jogador[0] == FOGO) {
            printf("FOGO\n");
        } else if (elemento_jogador[0] == AGUA) {
            printf("AGUA\n");
        } else if (elemento_jogador[0] == TERRA) {
            printf("TERRA\n");
        } else if (elemento_jogador[0] == AR) {
            printf("AR\n");
        }
        printf("Jogador 1, escolha uma acao:\n");
        printf("1 - Atacar\n");
        printf("2 - Defender\n");
        scanf("%d", &acao_jogador[0]);

        // Turno do Jogador 2
        srand(time(NULL)); // Reinicializa o gerador de números aleatório
        if (elemento_jogador[1] == FOGO){
            printf("Elemento: FOGO\n", elemento_jogador[1]);
        }else if (elemento_jogador[1] == AGUA){
            printf("Elemento: AGUA\n", elemento_jogador[1]);
        }else if (elemento_jogador[1] == TERRA){
            printf("Elemento: TERRA\n", elemento_jogador[1]);
        }else if (elemento_jogador[1] == AR){
            printf("Elemento: AR\n", elemento_jogador[1]);
        }
        printf("Jogador 2, escolha uma acao:\n");
        printf("1 - Atacar\n");
        printf("2 - Defender\n");
        scanf("%d", &acao_jogador[1]);

        // Lógica de combate
        if (acao_jogador[0] == 2) {
            defendeu[0] = 1;
            printf("Jogador 1 defendeu.\n");
        }if (acao_jogador[1] == 1) {
            pv_jogador[0] -= ataque_jogador(elemento_jogador, 1, 0, defendeu[0]); //Penaliza o Jogador dependendo do ataque realizado
        }else{
            defendeu[1] = 1;
            printf("Jogador 2 defendeu.\n");
        }
        if (acao_jogador[0] == 1) { 
            pv_jogador[1] -= ataque_jogador(elemento_jogador, 0, 1, defendeu[1]); //Ataque sem defesa
        }

        // Exibir pontos de vida
        printf("Pontos de Vida - Jogador 1: %d, Jogador 2: %d\n", pv_jogador[0], pv_jogador[1]);
    }

    // Determinar o vencedor
    if (pv_jogador[0] <= 0) {
        printf("Jogador 2 venceu!\n");
    } else {
        printf("Jogador 1 venceu!\n");
    }
    
    return 0;
}
