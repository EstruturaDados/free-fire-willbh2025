#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Definição da struct Item
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Protótipos das funções
void inserirItem();
void removerItem();
void listarItens();
void buscarItem();

// Variáveis globais
#define MAX_ITENS 10
Item mochila[MAX_ITENS];
int totalItens = 0;

// Função para inserir item na mochila
void inserirItem() {
    if (totalItens >= MAX_ITENS) {
        printf("Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }
    Item novo;
    printf("Nome do item: ");
    scanf("%s", novo.nome);
    printf("Tipo do item (arma, municao, cura, etc.): ");
    scanf("%s", novo.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    mochila[totalItens] = novo;
    totalItens++;
    printf("Item adicionado com sucesso!\n");
    listarItens();
}

// Função para remover um item pelo nome
void removerItem() {
    char nomeRemover[30];
    printf("Digite o nome do item a ser removido: ");
    scanf("%s", nomeRemover);
    int encontrado = 0;
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            for (int j = i; j < totalItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            totalItens--;
            printf("Item removido com sucesso!\n");
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Item não encontrado na mochila.\n");
    }
    listarItens();
}

// Função para listar os itens presentes na mochila
void listarItens() {
    printf("\nItens na mochila (%d/%d):\n", totalItens, MAX_ITENS);
    printf("--------------------------------------\n");
    for (int i = 0; i < totalItens; i++) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n", i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
    printf("--------------------------------------\n");
}

// Função para buscar um item pelo nome
void buscarItem() {
    char nomeBusca[30];
    printf("Digite o nome do item a buscar: ");
    scanf("%s", nomeBusca);
    int encontrado = 0;
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("Item encontrado!\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Item não encontrado na mochila.\n");
    }
}

// Função principal com menu
int main() {
    int opcao;
    do {
        printf("\n----- Sistema de Inventário Free Fire -----\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opção inválida, tente novamente.\n");
        }
    } while (opcao != 0);
    return 0;
}

