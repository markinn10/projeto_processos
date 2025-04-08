#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "processo.h"

void extrair_multivalores(const char *entrada, int saida[], int *qtd) {
    char buffer[256];
    strcpy(buffer, entrada);
    *qtd = 0;
    char *token = strtok(buffer, "{}, ");
    while (token && *qtd < MAX_ASSUNTOS) {
        saida[*qtd] = atoi(token);
        (*qtd)++;
        token = strtok(NULL, "{}, ");
    }
}

void ler_csv(const char *nome_arquivo, Processo processos[], int *qtd) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo CSV.\n");
        return;
    }

    char linha[512];
    fgets(linha, sizeof(linha), arquivo); // ignora cabeçalho
    *qtd = 0;

    while (fgets(linha, sizeof(linha), arquivo) && *qtd < MAX_PROCESSOS) {
        Processo *p = &processos[*qtd];
        char id_assunto_raw[100], id_classe_raw[100];

        sscanf(linha, "%d,%[^,],%[^,],%[^,],%[^,],%d",
               &p->id, p->numero, p->data_ajuizamento,
               id_classe_raw, id_assunto_raw, &p->ano_eleicao);

        extrair_multivalores(id_assunto_raw, p->id_assuntos, &p->qtd_assuntos);
        extrair_multivalores(id_classe_raw, p->id_classe, &p->qtd_classes);

        (*qtd)++;
    }
    fclose(arquivo);
}

void ordenar_por_id(Processo processos[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processos[j].id > processos[j + 1].id) {
                Processo temp = processos[j];
                processos[j] = processos[j + 1];
                processos[j + 1] = temp;
            }
        }
    }
}

void ordenar_por_data(Processo processos[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(processos[j].data_ajuizamento, processos[j + 1].data_ajuizamento) < 0) {
                Processo temp = processos[j];
                processos[j] = processos[j + 1];
                processos[j + 1] = temp;
            }
        }
    }
}

int contar_por_classe(Processo processos[], int n, int id_classe) {
    int contador = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < processos[i].qtd_classes; j++) {
            if (processos[i].id_classe[j] == id_classe) {
                contador++;
                break;
            }
        }
    }
    return contador;
}

int contar_assuntos_distintos(Processo processos[], int n) {
    int total[1000] = {0}, qtd = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < processos[i].qtd_assuntos; j++) {
            int atual = processos[i].id_assuntos[j];
            int existe = 0;
            for (int k = 0; k < qtd; k++) {
                if (total[k] == atual) {
                    existe = 1;
                    break;
                }
            }
            if (!existe)
                total[qtd++] = atual;
        }
    }
    return qtd;
}

void listar_multiplos_assuntos(Processo processos[], int n) {
    printf("Processos com múltiplos assuntos:\n");
    for (int i = 0; i < n; i++) {
        if (processos[i].qtd_assuntos > 1)
            printf("ID: %d - Assuntos: %d\n", processos[i].id, processos[i].qtd_assuntos);
    }
}

int dias_em_tramitacao(const char *data_str) {
    struct tm data_proc = {0};
    int ano, mes, dia, hora, minuto, segundo;
    sscanf(data_str, "%d-%d-%d %d:%d:%d", &ano, &mes, &dia, &hora, &minuto, &segundo);
    data_proc.tm_year = ano - 1900;
    data_proc.tm_mon = mes - 1;
    data_proc.tm_mday = dia;
    data_proc.tm_hour = hora;
    data_proc.tm_min = minuto;
    data_proc.tm_sec = segundo;

    time_t t1 = mktime(&data_proc);
    time_t agora = time(NULL);
    double segundos = difftime(agora, t1);
    return (int)(segundos / (60 * 60 * 24));
}

void salvar_csv_ordenado_por_id(const char *nome_arquivo, Processo processos[], int n) {
    FILE *arquivo = fopen(nome_arquivo, "w");
    fprintf(arquivo, "id,numero,data_ajuizamento,id_classe,id_assunto,ano_eleicao\n");
    for (int i = 0; i < n; i++) {
        fprintf(arquivo, "%d,%s,%s,{%d},", processos[i].id, processos[i].numero, processos[i].data_ajuizamento, processos[i].id_classe[0]);
        for (int j = 0; j < processos[i].qtd_assuntos; j++) {
            fprintf(arquivo, "{%d}%s", processos[i].id_assuntos[j], j < processos[i].qtd_assuntos - 1 ? "," : "");
        }
        fprintf(arquivo, ",%d\n", processos[i].ano_eleicao);
    }
    fclose(arquivo);
}

void salvar_csv_ordenado_por_data(const char *nome_arquivo, Processo processos[], int n) {
    salvar_csv_ordenado_por_id(nome_arquivo, processos, n);
}
