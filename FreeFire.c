#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

Item mochila[MAX_ITENS];
int totalItens = 0;

void flushStdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void adicionarItem() {
    if (totalItens >= MAX_ITENS) {
        printf("Mochila cheia!\n");
        return;
    }
    Item novo;
    printf("Nome: "); scanf("%s", novo.nome); flushStdin();
    printf("Tipo: "); scanf("%s", novo.tipo); flushStdin();
    printf("Quantidade: "); scanf("%d", &novo.quantidade); flushStdin();
    mochila[totalItens++] = novo;
    printf("\nItem '%s' adicionado com sucesso!\n", novo.nome);
}

void removerItem() {
    char nome[30];
    printf("Nome do item a remover: "); scanf("%s", nome); flushStdin();
    int i, encontrou = 0;
    for (i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            for (int j = i; j < totalItens - 1; j++)
                mochila[j] = mochila[j + 1];
            totalItens--;
            encontrou = 1;
            printf("\nItem '%s' removido com sucesso!\n", nome);
            break;
        }
    }
    if (!encontrou)
        printf("\nItem '%s' não encontrado na mochila.\n", nome);
}

void listarItens() {
    printf("\n--- ITENS NA MOCHILA (%d/%d) ---\n", totalItens, MAX_ITENS);
    printf("----------------------------------------------\n");
    printf("%-15s| %-10s| %-10s\n", "NOME", "TIPO", "QUANTIDADE");
    printf("----------------------------------------------\n");
    for (int i = 0; i < totalItens; i++)
        printf("%-15s| %-10s| %-10d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    printf("----------------------------------------------\n");
}

void buscarItem() {
    char nome[30];
    int comparacoes = 0, encontrou = 0;
    printf("Nome do item a buscar: "); scanf("%s", nome); flushStdin();
    for (int i = 0; i < totalItens; i++) {
        comparacoes++;
        if (strcmp(mochila[i].nome, nome) == 0) {
            printf("\nItem encontrado na posição %d: %s | %s | %d\n", 
                i+1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            encontrou = 1;
            break;
        }
    }
    if (!encontrou)
        printf("\nItem '%s' não encontrado na mochila.\n", nome);
    printf("Comparações: %d\n", comparacoes);
}


void menu() {
    char linha[20];
    int opcao, entradaValida;
    do {
        printf("============================================\n");
        printf("  MOCHILA DE SOBREVIVENCIA - CODIGO DA ILHA\n");
        printf("============================================\n");
        printf("Itens na Mochila: %d/%d\n", totalItens, MAX_ITENS);
        printf("============================================\n");
        printf("1. Adicionar Item (Loot)\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens na Mochila\n");
        printf("4. Buscar Item por Nome\n");
        printf("0. Sair\n");
        printf("--------------------------------------------\n");

        entradaValida = 0;
        while (!entradaValida) {
            printf("Escolha: ");
            if (fgets(linha, sizeof(linha), stdin) == NULL) {
                printf("Opção inválida, digite novamente.\n");
                continue;
            }

            // Checa se realmente é número e está no intervalo
            if (sscanf(linha, "%d", &opcao) != 1 || opcao < 0 || opcao > 4) {
                printf("Opção inválida, digite novamente.\n");
                // Imprime Escolha: novamente automaticamente
            } else {
                entradaValida = 1;
            }
        }

        switch(opcao) {
            case 1: adicionarItem(); break;
            case 2: removerItem(); break;
            case 3: listarItens(); break;
            case 4: buscarItem(); break;
            case 0: printf("Saindo...\n"); break;
        }
    } while (opcao != 0);
}

int main() {
    menu();
    return 0;
}
