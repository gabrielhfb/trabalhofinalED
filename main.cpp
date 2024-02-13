#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "avalia_senha.h"

int main(void){

    char arq_entrada[32] = "entrada.txt";
    char arq_testes[32] = "testes.txt";

    printf("Digite o nome do arquivo com os dados de entrada: ");
    scanf("%s", arq_entrada);

    printf("Digite o nome do arquivo com os dados de teste: ");
    scanf("%s", arq_testes);

    pNodoA *ABP = NULL;
    pNodoA *AVL = NULL;

    // -------------------------------------------------------------------------
    // ABP
    leDadosDoArquivoEManipulaArvore(arq_entrada, &ABP, ARVORE_ABP, INSERE);      //Insere
    leDadosDoArquivoEManipulaArvore(arq_testes, &ABP, ARVORE_ABP, CONSULTA);    //Consulta




    // -------------------------------------------------------------------------
    // AVL
    leDadosDoArquivoEManipulaArvore(arq_entrada, &AVL, ARVORE_AVL, INSERE);      // Insere
    leDadosDoArquivoEManipulaArvore(arq_testes, &AVL, ARVORE_AVL, CONSULTA);    // Consulta


    return 0;
}
