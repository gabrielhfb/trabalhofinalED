#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef enum TipoDeOperacao {INSERE = 0, CONSULTA} TipoDeOperacao;
typedef enum TipoDeArvore {ARVORE_ABP = 0, ARVORE_AVL} TipoDeArvore;

#define ARQUIVO_RESULTADOS  "resultados.txt"

// Estrutura de dados para ambas as �rvores (na ABP o fator de balanceamento n�o � usado)
typedef struct pNodoA{
        int id_usuario;
        char senha[32];

        struct pNodoA *esq;
        struct pNodoA *dir;
        int FB = 0;
} pNodoA;


void leDadosDoArquivoEManipulaArvore(char nome_arq_entrada[], pNodoA **ptr_arvore, int arvore, int operacao);
void salvaResultados(char nome_arq_entrada[], double tempo_cpu, pNodoA *ptr_arvore, int arvore, int operacao,
                     int comparacoes, int n_encontrados, int senha_incorreta, int senha_correta);

// Fun��o para ler arquivo texto no formato CSV, com trazendo o id e senha do usu�rio.
// Recebe um ponteiro para arquivo, e ponteiros para os locais onde os dados ser�o armazenados
bool carregaSenhaTXT(FILE *prt_arq, int *id_usuario, char *senha_usuario);

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
