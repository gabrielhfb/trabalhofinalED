//Bruna Corrêa de Freitas  
//Flavia Martins Lisboa
//Gabriel Henrique Fiszczuk Brandeburski

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef enum TipoDeOperacao {INSERE = 0, CONSULTA} TipoDeOperacao;
typedef enum TipoDeArvore {ARVORE_ABP = 0, ARVORE_AVL} TipoDeArvore;

#define ARQUIVO_RESULTADOS      "resultados.csv"
#define N_ARQUIVOS_DADOS        6
#define N_ARQUIVOS_TESTES       6
#define N_ARQUIVOS_TESTES_500   4
#define LENGHT_STRINGS          40
#define TOTAL_DE_COMBINACOES    32

// Estrutura de dados para ambas as �rvores (na ABP o fator de balanceamento n�o � usado)
typedef struct pNodoA
{
    int id_usuario;
    char senha[32];

    struct pNodoA *esq;
    struct pNodoA *dir;
    int FB = 0;
} pNodoA;

typedef struct CombinacoesArquivos
{
    char arquivo_de_dados[32];
    char arquivo_de_teste[32];
} CombinacoesArquivos;

void montaCombinacoesDeTestes(CombinacoesArquivos combinacoes[]);
void desalocaMemoria (pNodoA *a);
void leDadosDoArquivoEManipulaArvore(char nome_arq_entrada[], pNodoA **ptr_arvore, int arvore, int operacao);
void salvaResultados(char nome_arq_entrada[], double tempo_cpu, pNodoA *ptr_arvore, int arvore, int operacao,
                     int comparacoes, int n_encontrados, int senha_incorreta, int senha_correta, int insercoes);

// Fun��o para ler arquivo texto no formato CSV, com trazendo o id e senha do usu�rio.
// Recebe um ponteiro para arquivo, e ponteiros para os locais onde os dados ser�o armazenados
int carregaSenhaTXT(FILE *prt_arq, char *senha_usuario);

// Fun��o de consulta usada para ambas as �rvores.
// Recebe um ponteiro para nodo e a chave (id) a ser consultada
pNodoA *consultaArvore(pNodoA *a, int chave, int *comparacoes);

// Fun��o para inser��o de um novo nodo na ABP.
pNodoA *InsereABP(pNodoA *a, int id, char *senha_usuario, int *comparacoes);

// Fun��es para inser��o de um novo nodo na AVL.
int Altura(pNodoA *a, int *comparacoes);
int Calcula_FB(pNodoA *a, int *comparacoes);
pNodoA *rotacao_direita(pNodoA *pt);
pNodoA *rotacao_esquerda(pNodoA *pt);
pNodoA *rotacao_dupla_direita(pNodoA *pt, int *comparacoes);
pNodoA *rotacao_dupla_esquerda(pNodoA *pt, int *comparacoes);
pNodoA *Caso1(pNodoA *a, int *ok, int *comparacoes);
pNodoA *Caso2(pNodoA *a, int *ok, int *comparacoes);
pNodoA *InsereAVL(pNodoA *a, int id, char *senha_usuario, int *ok, int *comparacoes);
void testa_arvores(char arquivo_carrega[], char arquivo_teste[]);
