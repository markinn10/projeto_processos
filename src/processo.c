#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "processo.h"

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
}
