#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
    int prioridade;
} Componente;

Componente mochila[MAX_ITENS];
int totalItens = 0;
int estaOrdenadoPorNome = 0;

// Remover '\n' do fgets
void limpaEnter(char *str) {
    str[strcspn(str, "\n")] = 0;
}

void adicionarComponente() {
    if (totalItens >= MAX_ITENS) {
        printf("Mochila cheia!\n");
        return;
    }
    Componente novo;
    printf("\n--- Coletando Novo Componente ---\n");
    printf("Nome: "); fgets(novo.nome, sizeof(novo.nome), stdin); limpaEnter(novo.nome);
    printf("Tipo (Estrutural, Eletronico, Energia): ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin); limpaEnter(novo.tipo);

    printf("Quantidade: ");
    char qnt[10]; fgets(qnt, sizeof(qnt), stdin); novo.quantidade = atoi(qnt);
    do {
        printf("Prioridade de Montagem (1-5): ");
        char prio[10]; fgets(prio, sizeof(prio), stdin); novo.prioridade = atoi(prio);
    } while (novo.prioridade < 1 || novo.prioridade > 5);

    mochila[totalItens++] = novo;
    estaOrdenadoPorNome = 0;
    printf("\nComponente '%s' adicionado!\n", novo.nome);
}

void descartarComponente() {
    char nome[30];
    printf("Nome do componente a descartar: ");
    fgets(nome, sizeof(nome), stdin); limpaEnter(nome);

    int i, achou = 0;
    for (i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            for (int j = i; j < totalItens - 1; j++)
                mochila[j] = mochila[j + 1];
            totalItens--;
            achou = 1;
            estaOrdenadoPorNome = 0;
            printf("Componente '%s' descartado!\n", nome);
            break;
        }
    }
    if (!achou)
        printf("Componente '%s' não está na mochila.\n", nome);
}

void mostrarComponentes() {
    printf("\n--- INVENTARIO ATUAL (%d/%d) ---\n", totalItens, MAX_ITENS);
    printf("-------------------------------------------------------------------\n");
    printf("%-15s| %-12s| %-10s| %-10s\n", "NOME", "TIPO", "QUANTIDADE", "PRIORIDADE");
    printf("-------------------------------------------------------------------\n");
    for (int i = 0; i < totalItens; i++)
        printf("%-15s| %-12s| %-10d| %-10d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade, mochila[i].prioridade);
    printf("-------------------------------------------------------------------\n");
}

// Bubble Sort por nome
int bubbleSortNome(Componente arr[], int n) {
    int comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            comparacoes++;
            if (strcmp(arr[j].nome, arr[j + 1].nome) > 0) {
                Componente aux = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = aux;
            }
        }
    }
    return comparacoes;
}

// Insertion Sort por tipo
int insertionSortTipo(Componente arr[], int n) {
    int comparacoes = 0;
    for (int i = 1; i < n; i++) {
        Componente key = arr[i];
        int j = i - 1;
        while (j >= 0 && (++comparacoes, strcmp(arr[j].tipo, key.tipo) > 0)) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
    return comparacoes;
}

// Selection sort prioridade
int selectionSortPrioridade(Componente arr[], int n) {
    int comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (arr[j].prioridade < arr[min_idx].prioridade)
                min_idx = j;
        }
        if(min_idx != i) {
            Componente aux = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = aux;
        }
    }
    return comparacoes;
}

int buscaBinariaPorNome(Componente arr[], int n, char *buscado, int *comparacoes) {
    int ini = 0, fim = n - 1; *comparacoes = 0;
    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        (*comparacoes)++;
        int cmp = strcmp(arr[meio].nome, buscado);
        if (cmp == 0) return meio;
        else if (cmp < 0) ini = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

void menuOrdenacao() {
    char linha[50];
    int criterio, entradaValida, comparacoes = 0;
    printf("\n--- Estrategia de Organizacao ---\n");
    printf("Como deseja ordenar os componentes?\n");
    printf("1. Por Nome (Ordem Alfabética)\n");
    printf("2. Por Tipo\n");
    printf("3. Por Prioridade de Montagem\n");
    printf("0. Cancelar\n");

    entradaValida = 0;
    while (!entradaValida) {
        printf("Escolha o criterio: ");
        if (fgets(linha, sizeof(linha), stdin) == NULL) {
            printf("Opção inválida, tente novamente.\n");
            continue;
        }
        if (sscanf(linha, "%d", &criterio) != 1 || criterio < 0 || criterio > 3) {
            printf("Opção inválida, tente novamente.\n");
        } else {
            entradaValida = 1;
        }
    }

    if (criterio == 0) {
        printf("Organização cancelada.\n");
        return;
    }
    if (criterio == 1) {
        comparacoes = bubbleSortNome(mochila, totalItens);
        printf("Componentes organizados por nome!\nComparações: %d\n", comparacoes);
        estaOrdenadoPorNome = 1;
    } else if (criterio == 2) {
        comparacoes = insertionSortTipo(mochila, totalItens);
        printf("Componentes organizados por tipo!\nComparações: %d\n", comparacoes);
        estaOrdenadoPorNome = 0;
    } else if (criterio == 3) {
        comparacoes = selectionSortPrioridade(mochila, totalItens);
        printf("Componentes organizados por prioridade!\nComparações: %d\n", comparacoes);
        estaOrdenadoPorNome = 0;
    }
    mostrarComponentes();
}

void menu() {
    char linha[50];
    int opcao, entradaValida;
    do {
        printf("=====================================================\n");
        printf("  PLANO DE FUGA - CODIGO DA ILHA (NIVEL MESTRE)\n");
        printf("=====================================================\n");
        printf("Itens na Mochila: %d/%d\n", totalItens, MAX_ITENS);
        printf("Status da Ordenacao por Nome: %s\n", estaOrdenadoPorNome ? "ORDENADO" : "NAO ORDENADO");
        printf("=====================================================\n");
        printf("1. Adicionar Componente\n");
        printf("2. Descartar Componente\n");
        printf("3. Listar Componentes (Inventario)\n");
        printf("4. Organizar Mochila (Ordenar Componentes)\n");
        printf("5. Busca Binaria por Componente-Chave (por nome)\n");
        printf("0. ATIVAR TORRE DE FUGA (Sair)\n");
        printf("-----------------------------------------------------\n");

        entradaValida = 0;
        while (!entradaValida) {
            printf("Escolha uma opcao: ");
            if (fgets(linha, sizeof(linha), stdin) == NULL) {
                printf("Opção inválida, digite novamente.\n");
                continue;
            }
            if (sscanf(linha, "%d", &opcao) != 1 || opcao < 0 || opcao > 5) {
                printf("Opção inválida, digite novamente.\n");
            } else {
                entradaValida = 1;
            }
        }

        switch(opcao) {
            case 1:
                adicionarComponente();
                mostrarComponentes();
                break;
            case 2:
                descartarComponente();
                break;
            case 3:
                mostrarComponentes();
                break;
            case 4:
                menuOrdenacao();
                break;
            case 5: {
                if (!estaOrdenadoPorNome) {
                    printf("\nALERTA: Ordene a mochila antes! (Use a opção 4 para ordenar por nome)\n");
                    break;
                }
                if (totalItens == 0) {
                    printf("Nenhum componente na mochila para buscar.\n");
                    break;
                }
                char chave[30];
                printf("Nome do componente-chave para busca: ");
                fgets(chave, sizeof(chave), stdin); limpaEnter(chave);
                int comparacoes = 0, pos = buscaBinariaPorNome(mochila, totalItens, chave, &comparacoes);
                mostrarComponentes();
                printf("Comparações (busca binária): %d\n", comparacoes);
                if (pos != -1)
                    printf("Componente-chave '%s' ENCONTRADO na posição %d!\n", chave, pos+1);
                else
                    printf("Componente-chave '%s' NÃO encontrado.\n", chave);
                break;
            }
            case 0:
                printf("TORRE DE FUGA ATIVADA! Parabéns!\n");
                break;
        }
    } while(opcao != 0);
}

int main() {
    menu();
    return 0;
}
