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

int main() {
    Processo processos[MAX_PROCESSOS];
    int qtd_processos = 0;

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
