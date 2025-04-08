📌 Nome do Projeto
Sistema de Processamento de Dados da Justiça Eleitoral

👨‍💻 Desenvolvedor
Marcus – Análise e Desenvolvimento de Sistemas

🎯 Objetivo
Este sistema tem como finalidade processar e analisar um arquivo CSV contendo dados de processos da Justiça Eleitoral, realizando:

- Ordenação crescente por ID
- Ordenação decrescente por data de ajuizamento
- Contagem de processos por ID de classe
- Contagem de assuntos distintos
- Identificação de processos com múltiplos assuntos
- Cálculo dos dias em tramitação de cada processo

────────────────────────────────────────────────────────────────────

📁 Arquivos

- main.c ................ Código principal com entrada interativa
- processo.c ............ Funções que implementam o TAD Processo
- processo.h ............ Estrutura do TAD e constantes
- processo_043_202409032338.csv ... Base de dados fornecida
- ordenado_por_id.csv .... Saída ordenada por ID
- ordenado_por_data.csv .. Saída ordenada por data de ajuizamento

────────────────────────────────────────────────────────────────────

⚙️ Como Compilar e Executar (Windows)

1. Acesse a pasta do projeto pelo PowerShell:
   Exemplo:
   cd "C:\Users\SeuUsuario\Downloads\projeto_processos-main"

2. Compile:
   gcc src/main.c src/processo.c -I include -o programa.exe

3. Execute:
   .\programa.exe

4. Quando solicitado, digite o nome do arquivo CSV:
   processo_043_202409032338.csv

────────────────────────────────────────────────────────────────────

📈 Exemplo de Execução

Digite o nome do arquivo CSV: processo_043_202409032338.csv  
Total de processos carregados: 1000

Assuntos distintos: 22

Processos com múltiplos assuntos:
ID: 405288866 - Assuntos: 2  
ID: 405289050 - Assuntos: 2  
...

Digite o ID da classe para contar: 12477  
Quantidade de processos com id_classe = 12477: 3

Dias em tramitação:
ID 680402167: 251 dias  
ID 680402203: 258 dias  
...

────────────────────────────────────────────────────────────────────

📌 Observações

- Não foi utilizada nenhuma função de ordenação pronta da linguagem C.
- O parser reconhece campos multivalorados delimitados por `{}`.
- Os dados são armazenados em vetores de `structs` conforme diretriz do TAD.
- Os arquivos de saída `.csv` são gerados com o cabeçalho padrão.

────────────────────────────────────────────────────────────────────

📌 Conclusão

Trabalho realizado seguindo as diretrizes propostas em aula, com foco em modularização, legibilidade e entrada dinâmica. O sistema está preparado para ser executado com qualquer base no formato especificado.

Desenvolvido por Marcus – ADS 2024/2025
