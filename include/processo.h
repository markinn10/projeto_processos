#ifndef PROCESSO_H
#define PROCESSO_H

#define MAX_PROCESSOS 1000
#define TAM_MAX_ASSUNTO 256
#define TAM_MAX_DATA 30

typedef struct {
    int id;
    char numero[30];
    char data_ajuizamento[TAM_MAX_DATA];
    int id_classe;
    char id_assunto_raw[100]; // Campo como string, para verificar múltiplos assuntos
    int ano_eleicao;

    char assunto[100];
    char data[20], hora[10], minuto[10], segundo[10], status[20];
    int id_subclasse, id_prioridade, id_status, id_usuario, id_categoria;
    char hora_ajuizamento[10];
} Processo;

void ordenar_por_id(Processo processos[], int n);
void ordenar_por_data(Processo processos[], int n);
void imprimir_processos_csv_com_titulo(Processo processos[], int n);
void imprimir_processos_csv_por_data(Processo processos[], int n);


void ler_csv(const char *nome_arquivo, Processo processos[], int *qtd);
void ordenar_por_id(Processo processos[], int n);
void ordenar_por_data(Processo processos[], int n);
int contar_por_classe(Processo processos[], int n, int id_classe);
int contar_assuntos_distintos(Processo processos[], int n);
void listar_multiplos_assuntos(Processo processos[], int n);
int dias_em_tramitacao(const char *data_str);
void salvar_csv(const char *nome_arquivo, Processo processos[], int n);
void salvar_csv_com_titulo(const char *nome_arquivo, Processo processos[], int n);
void imprimir_processos(Processo processos[], int n);

#endif
