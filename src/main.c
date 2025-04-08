<<<<<<< HEAD
// Versão com MENU INTERATIVO e funcionalidades completas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processo.h"

void exibir_menu() {
    printf("\n=========== MENU ===========\n");
    printf("[1] Ordenar por ID (crescente)\n");
    printf("[2] Ordenar por Data (decrescente)\n");
    printf("[3] Contar processos por ID de classe\n");
    printf("[4] Contar assuntos distintos\n");
    printf("[5] Listar processos com múltiplos assuntos\n");
    printf("[6] Mostrar dias em tramitação\n");
    printf("[7] Filtrar por ano de eleição\n");
    printf("[8] Exportar processos por ID de classe\n");
    printf("[0] Sair\n");
    printf("============================\n");
    printf("Escolha: ");
}

void exportar_por_classe(Processo processos[], int n, int id_classe) {
    char nome_arquivo[50];
    sprintf(nome_arquivo, "classe_%d.csv", id_classe);
    FILE *arq = fopen(nome_arquivo, "w");
    if (!arq) {
        printf("Erro ao criar o arquivo.\n");
        return;
    }
    fprintf(arq, "id,numero,data_ajuizamento,id_classe,id_assunto,ano_eleicao\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < processos[i].qtd_classes; j++) {
            if (processos[i].id_classe[j] == id_classe) {
                fprintf(arq, "%d,%s,%s,{%d},", processos[i].id, processos[i].numero, processos[i].data_ajuizamento, id_classe);
                for (int k = 0; k < processos[i].qtd_assuntos; k++) {
                    fprintf(arq, "{%d}%s", processos[i].id_assuntos[k], k < processos[i].qtd_assuntos - 1 ? "," : "");
                }
                fprintf(arq, ",%d\n", processos[i].ano_eleicao);
                break;
            }
        }
    }
    fclose(arq);
    printf("Exportado para %s\n", nome_arquivo);
}

void filtrar_por_ano(Processo processos[], int n, int ano) {
    printf("Processos com ano de eleição = %d:\n", ano);
    for (int i = 0; i < n; i++) {
        if (processos[i].ano_eleicao == ano) {
            printf("→ ID: %d | Data: %s | Classe: %d\n", processos[i].id, processos[i].data_ajuizamento, processos[i].id_classe[0]);
        }
    }
}

void resumo_estatistico(Processo processos[], int n) {
    printf("\n===== RELATÓRIO GERAL =====\n");
    printf("Total de processos: %d\n", n);
    int mult = 0, classes[1000] = {0}, q_classes = 0;
    for (int i = 0; i < n; i++) {
        if (processos[i].qtd_assuntos > 1) mult++;
        for (int j = 0; j < processos[i].qtd_classes; j++) {
            int id = processos[i].id_classe[j], existe = 0;
            for (int k = 0; k < q_classes; k++) {
                if (classes[k] == id) {
                    existe = 1;
                    break;
                }
            }
            if (!existe) classes[q_classes++] = id;
        }
    }
    printf("Processos com múltiplos assuntos: %d\n", mult);
    printf("Classes distintas encontradas: %d\n", q_classes);
    printf("Processo mais antigo: %d (%d dias em tramitação)\n", processos[0].id, dias_em_tramitacao(processos[0].data_ajuizamento));
}
=======
#include <stdio.h>
#include <stdlib.h>
#include "processo.h"

// Funções declaradas no outro arquivo (já estão implementadas lá)
void ler_csv(const char *nome_arquivo, Processo processos[], int *qtd);
void ordenar_por_id(Processo processos[], int n);
void ordenar_por_data(Processo processos[], int n);
int contar_assuntos_distintos(Processo processos[], int qtd);
void listar_multiplos_assuntos(Processo processos[], int n);
int dias_em_tramitacao(const char *data_str);
void salvar_csv_ordenado_por_id(const char *nome_arquivo, Processo processos[], int n);
void salvar_csv_ordenado_por_data(const char *nome_arquivo, Processo processos[], int n);
>>>>>>> 018131cd533fc199a092d48b628771e80f3bce86

int main() {
    Processo processos[MAX_PROCESSOS];
    int qtd_processos = 0;
<<<<<<< HEAD
    char arquivo_entrada[100];

    printf("Digite o nome do arquivo CSV (ex: processo_043_202409032338.csv): ");
    scanf("%s", arquivo_entrada);

    ler_csv(arquivo_entrada, processos, &qtd_processos);

    if (qtd_processos == 0) {
        printf("⚠️ Nenhum processo carregado. Verifique o nome do arquivo.\n");
        return 1;
    }

    int opcao;
    do {
        exibir_menu();
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                ordenar_por_id(processos, qtd_processos);
                salvar_csv_ordenado_por_id("ordenado_por_id.csv", processos, qtd_processos);
                printf("Ordenado por ID e salvo em ordenado_por_id.csv\n");
                break;
            case 2:
                ordenar_por_data(processos, qtd_processos);
                salvar_csv_ordenado_por_data("ordenado_por_data.csv", processos, qtd_processos);
                printf("Ordenado por data e salvo em ordenado_por_data.csv\n");
                break;
            case 3: {
                int id_classe;
                printf("Digite o ID da classe: ");
                scanf("%d", &id_classe);
                int count = contar_por_classe(processos, qtd_processos, id_classe);
                printf("Quantidade de processos com id_classe = %d: %d\n", id_classe, count);
                break;
            }
            case 4: {
                int qtd = contar_assuntos_distintos(processos, qtd_processos);
                printf("Assuntos distintos encontrados: %d\n", qtd);
                break;
            }
            case 5:
                listar_multiplos_assuntos(processos, qtd_processos);
                break;
            case 6:
                for (int i = 0; i < qtd_processos; i++)
                    printf("ID %d: %d dias\n", processos[i].id, dias_em_tramitacao(processos[i].data_ajuizamento));
                break;
            case 7: {
                int ano;
                printf("Digite o ano da eleição para filtrar: ");
                scanf("%d", &ano);
                filtrar_por_ano(processos, qtd_processos, ano);
                break;
            }
            case 8: {
                int id_classe;
                printf("Digite o ID da classe para exportar: ");
                scanf("%d", &id_classe);
                exportar_por_classe(processos, qtd_processos, id_classe);
                break;
            }
            case 0:
                resumo_estatistico(processos, qtd_processos);
                printf("Encerrando...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);

    return 0;
}

=======

    // Caminho do CSV de entrada
    const char *arquivo_entrada = "entrada.csv";

    // Lê os dados
    ler_csv(arquivo_entrada, processos, &qtd_processos);
    printf("Total de processos carregados: %d\n\n", qtd_processos);

    // Contar e exibir total de assuntos distintos
    int assuntos_distintos = contar_assuntos_distintos(processos, qtd_processos);
    printf("Quantidade de assuntos distintos: %d\n\n", assuntos_distintos);

    // Listar processos com múltiplos assuntos
    listar_multiplos_assuntos(processos, qtd_processos);
    printf("\n");

    // Ordenar por ID e salvar em CSV
    ordenar_por_id(processos, qtd_processos);
    salvar_csv_ordenado_por_id("saida_ordenada_por_id.csv", processos, qtd_processos);

    // Ordenar por data e salvar em CSV
    ordenar_por_data(processos, qtd_processos);
    salvar_csv_ordenado_por_data("saida_ordenada_por_data.csv", processos, qtd_processos);

    // Exibir dias em tramitação de cada processo
    printf("Dias em tramitação por processo:\n");
    for (int i = 0; i < qtd_processos; i++) {
        int dias = dias_em_tramitacao(processos[i].data_ajuizamento);
        printf("ID: %d - Dias em tramitação: %d\n", processos[i].id, dias);
    }

    return 0;
}
>>>>>>> 018131cd533fc199a092d48b628771e80f3bce86
