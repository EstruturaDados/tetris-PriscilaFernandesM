//Tetris//
//Nível novato

// Incluindo Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//Defnindo constantes Globais
#define MAXIMO_PECAS 5

//Estrutura das peças
typedef struct {
    char nome;
    int id; 
} Peca;

//Estrutura da fila
Peca fila[MAXIMO_PECAS];
int frente = 0;
int final = 0;
int count = 0;
int proximo_id = 0;

//Definindo as peças

Peca gerarPeca() {
    Peca novaPeca;
    char tipos[] = {'I', 'O', 'T', 'L', 'J', 'Z', 'S'};
    int num_tipos = sizeof(tipos) / sizeof(tipos[0]);

    //Função de aleatório
    novaPeca.nome = tipos[rand() % num_tipos];
    
    //Função do id
    novaPeca.id = proximo_id++;

    return novaPeca;
}

//Atualização da fila e visualização das peças

void exibirFila() {
    printf("• Fila de Peças Futuras (CAP: %d/5) • \n", count);
    
    if (count == 0) {
        printf("• Nenhuma peça na fila.\n");
        return;
    }

    printf("Entrando na fila de peças:\n");
    printf("• Início ► Final •\n");
    
    //Fazendo o FiFo

    for (int i = 0; i < count; i++) {
        int indice = (frente + i) % MAXIMO_PECAS;
        printf("[%c %d] ", fila[indice].nome, fila[indice].id);
    }
}

//Função de Fila
void inserirPeca(Peca peca) {
    if (count == MAXIMO_PECAS) {
        printf("Fila está completa!\n");
        printf("Peça • %c %d • não pode ser adicionada.\n", peca.nome, peca.id);
        return;
    }


    //Enqueue, adicionando pe~ças no FiFo
    fila[final] = peca;
    
    final = (final + 1) % MAXIMO_PECAS;
    
    count++;

    printf("Peça • %c %d • foi para o final da fila.\n", peca.nome, peca.id);
}

//Removendo a peça
void jogarPeca() {
    if (count == 0) {
        printf("Sua fila está sem peças para serem jogadas.\n");
        return;
    }

    //Pegando a peça da frente e fazendo a rotação de FiFO
    Peca pecaRemovida = fila[frente];

    frente = (frente + 1) %MAXIMO_PECAS;

    count--;
    
    printf("Peça • %c %d • jogada.\n", pecaRemovida.nome, pecaRemovida.id);
}

//Função Principal, inicializando com número aleatórios 
int main() {
    int opcao;
    srand(time(NULL)); 

    printf("• Tetris •\n");

    //Iniciando a Fila e Printando a fila
    printf("Iniciando a sua fila com %d Peças\n", MAXIMO_PECAS);
    for (int i = 0; i < MAXIMO_PECAS; i++) {
        Peca nova = gerarPeca();
        inserirPeca(nova);
    }
    
        exibirFila();

    do {
        printf("Escolhe uma ação para começar a jogar:\n");
        printf("1      | Jogar peça (DEQUEUE) - Remove da frente\n");
        printf("2      | Inserir nova peça (ENQUEUE) - Adiciona ao final\n");
        printf("0      | Sair do Jogo\n");
        printf("Digite o número da sua ação:\n");
        
        //Limpeza de buffer
        fflush(stdin); 
        if (scanf("%d", &opcao) != 1) {
            printf("\nOpção inválida. Digite um número.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF) { }
            opcao = 0;
            continue;
        }

        switch (opcao) {
            case 1:
                jogarPeca();
                exibirFila();
                break;
            case 2: {
                Peca nova = gerarPeca();
                inserirPeca(nova);
                exibirFila();
                break;
            }
            case 0:
                printf("Tetris encerrado.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
        
    } while (opcao != 0);

    return 0;
}