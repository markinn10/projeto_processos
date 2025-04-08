#ifndef PROCESSO_H
#define PROCESSO_H

#define MAX_PROCESSOS 1000
#define MAX_ASSUNTOS 10
#define MAX_NUMERO 30
#define MAX_DATA 25

typedef struct {
    int id;
    char numero[MAX_NUMERO];
    char data_ajuizamento[MAX_DATA];
    int id_classe[MAX_ASSUNTOS];
    int qtd_classes;
    int id_assuntos[MAX_ASSUNTOS];
    int qtd_assuntos;
    int ano_eleicao;
} Processo;

// Funções principais
void ler_csv(const char *nome_arquivo, Processo processos[], int *qtd);
void ordenar_por_id(Processo processos[], int n);
void ordenar_por_data(Processo processos[], int n);
int contar_por_classe(Processo processos[], int n, int id_classe);
int contar_assuntos_distintos(Processo processos[], int n);
void listar_multiplos_assuntos(Processo processos[], int n);
int dias_em_tramitacao(const char *data_str);
void salvar_csv_ordenado_por_id(const char *nome_arquivo, Processo processos[], int n);
void salvar_csv_ordenado_por_data(const char *nome_arquivo, Processo processos[], int n);

#endif
