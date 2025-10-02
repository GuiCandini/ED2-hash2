#ifndef HASH_H
#define HASH_H

#define NOME_TAM 30

struct produto {
    int codigo;
    char nome[NOME_TAM];
    float preco;
    int quantidade;
};

struct hash {
    int qtd;
    int tamanho;
    struct produto* itens;
};

typedef struct hash Hash;

int hash_code(int codigo, int tamanho);
Hash* criar_tabela(int tamanho);
void liberar_tabela(Hash* h);
void imprimir_produto(const struct produto* p);
struct produto ler_produto();
int inserir_sem_colisao(Hash* h, struct produto p);
struct produto* buscar_sem_colisao(Hash* h, int codigo);
int inserir_endereco_aberto(Hash* h, struct produto p);
struct produto* buscar_endereco_aberto(Hash* h, int codigo);
int excluir_produto(Hash* h, int codigo);
void limpar_tabela(Hash* h);
void exibir_menu();
void exibir_status(Hash* h);

#endif
