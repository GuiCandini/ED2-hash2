#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

int main() {
    Hash* minha_tabela = NULL;
    int opcao, codigo_busca, tamanho;
    struct produto novo_produto;
    struct produto* resultado_busca;

    do {
        exibir_menu();
        if (scanf("%d", &opcao) != 1) {
            opcao = -1;
            while (getchar() != '\n');
        }

        switch (opcao) {
            case 1:
                if (minha_tabela != NULL) {
                    liberar_tabela(minha_tabela);
                }
                printf("Digite o tamanho da tabela: ");
                scanf("%d", &tamanho);
                minha_tabela = criar_tabela(tamanho);
                break;
            case 2:
                if (minha_tabela == NULL) {
                    printf("[ERRO] Crie a tabela primeiro.\n");
                    break;
                }
                novo_produto = ler_produto();
                inserir_sem_colisao(minha_tabela, novo_produto);
                break;
            case 3:
                if (minha_tabela == NULL) {
                    printf("[ERRO] Crie a tabela primeiro.\n");
                    break;
                }
                printf("Código: ");
                scanf("%d", &codigo_busca);
                resultado_busca = buscar_sem_colisao(minha_tabela, codigo_busca);
                imprimir_produto(resultado_busca);
                break;
            case 4:
                if (minha_tabela == NULL) {
                    printf("[ERRO] Crie a tabela primeiro.\n");
                    break;
                }
                novo_produto = ler_produto();
                inserir_endereco_aberto(minha_tabela, novo_produto);
                break;
            case 5:
                if (minha_tabela == NULL) {
                    printf("[ERRO] Crie a tabela primeiro.\n");
                    break;
                }
                printf("Código: ");
                scanf("%d", &codigo_busca);
                resultado_busca = buscar_endereco_aberto(minha_tabela, codigo_busca);
                imprimir_produto(resultado_busca);
                break;
            case 6:
                exibir_status(minha_tabela);
                break;
            case 7:
                if (minha_tabela == NULL) {
                    printf("[ERRO] Crie a tabela primeiro.\n");
                    break;
                }
                printf("Código: ");
                scanf("%d", &codigo_busca);
                excluir_produto(minha_tabela, codigo_busca);
                break;
            case 8:
                if (minha_tabela == NULL) {
                    printf("[ERRO] Crie a tabela primeiro.\n");
                    break;
                }
                limpar_tabela(minha_tabela);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);

    liberar_tabela(minha_tabela);
    return 0;
}
