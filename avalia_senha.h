#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Variável global para contar o número de comparações feitas na execução
double comparacoes = 0;

// Estrutura de dados para ambas as árvores (na ABP o fator de balanceamento não é usado)
typedef struct pNodoA{
        int id_usuario;
        char senha[32];

        struct pNodoA *esq;
        struct pNodoA *dir;
        int FB = 0;
} pNodoA;

// Função para ler arquivo texto no formato CSV, com trazendo o id e senha do usuário.
// Recebe um ponteiro para arquivo, e ponteiros para os locais onde os dados serão armazenados
bool carregaSenhaTXT(FILE *prt_arq, int *id_usuario, char *senha_usuario);

// Função de consulta usada para ambas as árvores.
// Recebe um ponteiro para nodo e a chave (id) a ser consultada
pNodoA *consultaArvore(pNodoA *a, int chave);

// Função para inserção de um novo nodo na ABP.
pNodoA *InsereABP(pNodoA *a, int id, char *senha_usuario);

// Funções para inserção de um novo nodo na AVL.
int Altura(pNodoA *a);
int Calcula_FB(pNodoA *a);
pNodoA *rotacao_direita(pNodoA *pt);
pNodoA *rotacao_esquerda(pNodoA *pt);
pNodoA *rotacao_dupla_direita(pNodoA *pt);
pNodoA *rotacao_dupla_esquerda(pNodoA *pt);
pNodoA *Caso1(pNodoA *a, int *ok);
pNodoA *Caso2(pNodoA *a, int *ok);
pNodoA *InsereAVL(pNodoA *a, int id, char *senha_usuario, int *ok);