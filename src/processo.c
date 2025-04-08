#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "processo.h"

<<<<<<< HEAD
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
=======
#define MAX_PROCESSOS 1000

typedef struct {
    int id;
    char assunto[100];
    char data[11];
    char hora[9];
    char minuto[3];
    char segundo[3];
    char status[20];
    int id_classe;
    int id_subclasse;
    int id_prioridade;
    int id_status;
    int id_usuario;
    int id_categoria;
    char data_ajuizamento[11];
    char hora_ajuizamento[9];
    char id_assunto_raw[100];
    int ano_eleicao;
} Processo;

// Comparadores para qsort
int comparar_por_id(const void *a, const void *b) {
    Processo *p1 = (Processo *)a;
    Processo *p2 = (Processo *)b;
    return p1->id - p2->id;
}

int comparar_por_data(const void *a, const void *b) {
    Processo *p1 = (Processo *)a;
    Processo *p2 = (Processo *)b;
    return strcmp(p1->data, p2->data);
}

// Função para salvar em CSV ordenado por ID
void imprimir_processos_csv_com_titulo(Processo processos[], int n) {
    // Ordena por ID
    qsort(processos, n, sizeof(Processo), comparar_por_id);

    FILE *arquivo = fopen("processos_ordenados_id.csv", "w");
    if (!arquivo) {
        printf("Erro ao abrir arquivo CSV.\n");
        return;
    }

    fprintf(arquivo, "id,assunto,data,hora,minuto,segundo,status,id_classe,id_subclasse,id_prioridade,id_status,id_usuario,id_categoria,data_ajuizamento,hora_ajuizamento,id_assunto_raw,ano_eleicao\n");

    for (int i = 0; i < n; i++) {
        fprintf(arquivo, "%d,%s,%s,%s,%s,%s,%s,%d,%d,%d,%d,%d,%d,%s,%s,%s,%d\n",
            processos[i].id,
            processos[i].assunto,
            processos[i].data,
            processos[i].hora,
            processos[i].minuto,
            processos[i].segundo,
            processos[i].status,
            processos[i].id_classe,
            processos[i].id_subclasse,
            processos[i].id_prioridade,
            processos[i].id_status,
            processos[i].id_usuario,
            processos[i].id_categoria,
            processos[i].data_ajuizamento,
            processos[i].hora_ajuizamento,
            processos[i].id_assunto_raw,
            processos[i].ano_eleicao
        );
    }

    fclose(arquivo);
    printf("CSV ordenado por ID gerado com sucesso.\n");
}

// Função para salvar em CSV ordenado por Data
void imprimir_processos_csv_por_data(Processo processos[], int n) {
    // Ordena por Data
    qsort(processos, n, sizeof(Processo), comparar_por_data);

    FILE *arquivo = fopen("processos_ordenados_data.csv", "w");
    if (!arquivo) {
        printf("Erro ao abrir arquivo CSV.\n");
        return;
    }

    fprintf(arquivo, "id,assunto,data,hora,minuto,segundo,status,id_classe,id_subclasse,id_prioridade,id_status,id_usuario,id_categoria,data_ajuizamento,hora_ajuizamento,id_assunto_raw,ano_eleicao\n");

    for (int i = 0; i < n; i++) {
        fprintf(arquivo, "%d,%s,%s,%s,%s,%s,%s,%d,%d,%d,%d,%d,%d,%s,%s,%s,%d\n",
            processos[i].id,
            processos[i].assunto,
            processos[i].data,
            processos[i].hora,
            processos[i].minuto,
            processos[i].segundo,
            processos[i].status,
            processos[i].id_classe,
            processos[i].id_subclasse,
            processos[i].id_prioridade,
            processos[i].id_status,
            processos[i].id_usuario,
            processos[i].id_categoria,
            processos[i].data_ajuizamento,
            processos[i].hora_ajuizamento,
            processos[i].id_assunto_raw,
            processos[i].ano_eleicao
        );
    }

    fclose(arquivo);
    printf("CSV ordenado por data gerado com sucesso.\n");
}

// Função principal para exportar os CSVs
void salvar_csv(Processo processos[], int n) {
    imprimir_processos_csv_com_titulo(processos, n);
    imprimir_processos_csv_por_data(processos, n);
}

// Função main de exemplo
int main() {
    Processo processos[MAX_PROCESSOS];

    // Inserção de dois registros para simulação
    processos[0].id = 5;
    strcpy(processos[0].assunto, "Recurso Financeiro");
    strcpy(processos[0].data, "2023-10-20");
    strcpy(processos[0].hora, "12:00:00");
    strcpy(processos[0].minuto, "00");
    strcpy(processos[0].segundo, "00");
    strcpy(processos[0].status, "Ativo");
    processos[0].id_classe = 1;
    processos[0].id_subclasse = 2;
    processos[0].id_prioridade = 3;
    processos[0].id_status = 4;
    processos[0].id_usuario = 5;
    processos[0].id_categoria = 6;
    strcpy(processos[0].data_ajuizamento, "2023-10-19");
    strcpy(processos[0].hora_ajuizamento, "11:00:00");
    strcpy(processos[0].id_assunto_raw, "RF2023");
    processos[0].ano_eleicao = 2024;

    processos[1].id = 2;
    strcpy(processos[1].assunto, "Denúncia Eleitoral");
    strcpy(processos[1].data, "2022-08-15");
    strcpy(processos[1].hora, "09:30:00");
    strcpy(processos[1].minuto, "30");
    strcpy(processos[1].segundo, "00");
    strcpy(processos[1].status, "Concluído");
    processos[1].id_classe = 2;
    processos[1].id_subclasse = 1;
    processos[1].id_prioridade = 1;
    processos[1].id_status = 2;
    processos[1].id_usuario = 3;
    processos[1].id_categoria = 4;
    strcpy(processos[1].data_ajuizamento, "2022-08-14");
    strcpy(processos[1].hora_ajuizamento, "08:45:00");
    strcpy(processos[1].id_assunto_raw, "DE2022");
    processos[1].ano_eleicao = 2022;

    salvar_csv(processos, 2);

    return 0;
>>>>>>> 018131cd533fc199a092d48b628771e80f3bce86
}
