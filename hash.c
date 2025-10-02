#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

int hash_code(int codigo, int tamanho) {
    return codigo % tamanho;
}

Hash* criar_tabela(int tamanho) {
    if (tamanho <= 0) return NULL;
    Hash* h = (Hash*) malloc(sizeof(Hash));
    h->tamanho = tamanho;
    h->qtd = 0;
    h->itens = (struct produto*) calloc(tamanho, sizeof(struct produto));
    printf("Tabela criada com tamanho %d.\n", tamanho);
    return h;
}

void liberar_tabela(Hash* h) {
    if (h != NULL) {
        free(h->itens);
        free(h);
    }
}

void imprimir_produto(const struct produto* p) {
    if (p != NULL && p->codigo != 0) {
        printf("\n--- Produto ---\n");
        printf("Código: %d\n", p->codigo);
        printf("Nome: %s\n", p->nome);
        printf("Preço: R$%.2f\n", p->preco);
        printf("Quantidade: %d\n", p->quantidade);
    } else {
        printf("\nProduto não encontrado.\n");
    }
}

struct produto ler_produto() {
    struct produto p;
    printf("\nCódigo: ");
    scanf("%d", &p.codigo);
    while (getchar() != '\n');
    printf("Nome: ");
    fgets(p.nome, NOME_TAM, stdin);
    p.nome[strcspn(p.nome, "\n")] = 0;
    printf("Preço: ");
    scanf("%f", &p.preco);
    printf("Quantidade: ");
    scanf("%d", &p.quantidade);
    return p;
}

int inserir_sem_colisao(Hash* h, struct produto p) {
    if (h == NULL || p.codigo <= 0 || h->qtd >= h->tamanho) return 0;
    int pos = hash_code(p.codigo, h->tamanho);
    if (h->itens[pos].codigo == 0) {
        h->itens[pos] = p;
        h->qtd++;
        printf("Produto %d inserido na posição %d.\n", p.codigo, pos);
        return 1;
    }
    printf("Colisão na posição %d.\n", pos);
    return 0;
}

struct produto* buscar_sem_colisao(Hash* h, int codigo) {
    if (h == NULL || codigo <= 0 || h->qtd == 0) return NULL;
    int pos = hash_code(codigo, h->tamanho);
    if (h->itens[pos].codigo == codigo) return &h->itens[pos];
    return NULL;
}

int inserir_endereco_aberto(Hash* h, struct produto p) {
    if (h == NULL || p.codigo <= 0 || h->qtd >= h->tamanho) return 0;
    int inicio = hash_code(p.codigo, h->tamanho), pos = inicio, tentativas = 0;
    while (h->itens[pos].codigo != 0 && tentativas < h->tamanho) {
        if (h->itens[pos].codigo == p.codigo) {
            printf("Produto %d já existe.\n", p.codigo);
            return 0;
        }
        pos = (inicio + tentativas + 1) % h->tamanho;
        tentativas++;
    }
    if (h->itens[pos].codigo == 0) {
        h->itens[pos] = p;
        h->qtd++;
        printf("Produto %d inserido na posição %d.\n", p.codigo, pos);
        return 1;
    }
    printf("Tabela cheia.\n");
    return 0;
}

struct produto* buscar_endereco_aberto(Hash* h, int codigo) {
    if (h == NULL || codigo <= 0 || h->qtd == 0) return NULL;
    int inicio = hash_code(codigo, h->tamanho), pos = inicio, tentativas = 0;
    while (h->itens[pos].codigo != 0 && tentativas < h->tamanho) {
        if (h->itens[pos].codigo == codigo) return &h->itens[pos];
        pos = (inicio + tentativas + 1) % h->tamanho;
        tentativas++;
    }
    return NULL;
}

int excluir_produto(Hash* h, int codigo) {
    if (h == NULL || codigo <= 0 || h->qtd == 0) return 0;
    int pos = hash_code(codigo, h->tamanho), tentativas = 0;
    while (h->itens[pos].codigo != 0 && tentativas < h->tamanho) {
        if (h->itens[pos].codigo == codigo) {
            h->itens[pos].codigo = 0;
            h->qtd--;
            printf("Produto %d removido.\n", codigo);
            return 1;
        }
        pos = (pos + 1) % h->tamanho;
        tentativas++;
    }
    printf("Produto %d não encontrado.\n", codigo);
    return 0;
}

void limpar_tabela(Hash* h) {
    if (h == NULL) return;
    for (int i = 0; i < h->tamanho; i++) {
        h->itens[i].codigo = 0;
    }
    h->qtd = 0;
    printf("Tabela limpa.\n");
}

void exibir_menu() {
    printf("\n1. Criar Tabela\n");
    printf("2. Inserir Produto (SEM Colisão)\n");
    printf("3. Buscar Produto (SEM Colisão)\n");
    printf("4. Inserir Produto (COM Colisão)\n");
    printf("5. Buscar Produto (COM Colisão)\n");
    printf("6. Exibir Tabela\n");
    printf("7. Excluir Produto\n");
    printf("8. Limpar Tabela\n");
    printf("0. Sair\n");
    printf("Opção: ");
}

void exibir_status(Hash* h) {
    if (h == NULL) {
        printf("\n[Tabela não criada]\n");
        return;
    }
    printf("\n--- Status (%d/%d) ---\n", h->qtd, h->tamanho);
    for (int i = 0; i < h->tamanho; i++) {
        printf("[%2d]: ", i);
        if (h->itens[i].codigo != 0) {
            printf("Cód: %d | Nome: %s\n", h->itens[i].codigo, h->itens[i].nome);
        } else {
            printf("LIVRE\n");
        }
    }
}
