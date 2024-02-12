#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int comparacoes = 0;


typedef struct pNodoA{
        int id_usuario;
        char senha[32];

        struct pNodoA *esq;
        struct pNodoA *dir;
        int FB = 0;
} pNodoA;



bool carregaSenhaTXT(FILE *prt_arq, int *id_usuario, char *senha_usuario);
