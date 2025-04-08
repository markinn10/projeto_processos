#ifndef PROCESSO_H
#define PROCESSO_H

#define MAX_PROCESSOS 1000
<<<<<<< HEAD
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
=======
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


>>>>>>> 018131cd533fc199a092d48b628771e80f3bce86
void ler_csv(const char *nome_arquivo, Processo processos[], int *qtd);
void ordenar_por_id(Processo processos[], int n);
void ordenar_por_data(Processo processos[], int n);
int contar_por_classe(Processo processos[], int n, int id_classe);
int contar_assuntos_distintos(Processo processos[], int n);
void listar_multiplos_assuntos(Processo processos[], int n);
int dias_em_tramitacao(const char *data_str);
<<<<<<< HEAD
void salvar_csv_ordenado_por_id(const char *nome_arquivo, Processo processos[], int n);
void salvar_csv_ordenado_por_data(const char *nome_arquivo, Processo processos[], int n);
=======
void salvar_csv(const char *nome_arquivo, Processo processos[], int n);
void salvar_csv_com_titulo(const char *nome_arquivo, Processo processos[], int n);
void imprimir_processos(Processo processos[], int n);
>>>>>>> 018131cd533fc199a092d48b628771e80f3bce86

#endif
