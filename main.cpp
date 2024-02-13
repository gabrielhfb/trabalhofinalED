#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "avalia_senha.h"

int main(void)
{
    CombinacoesArquivos combinacoes[TOTAL_DE_COMBINACOES];
    montaCombinacoesDeTestes(combinacoes);


    for(int i=0; i<TOTAL_DE_COMBINACOES; i++){
        pNodoA *ABP = NULL;
        pNodoA *AVL = NULL;

        printf("Dados INSERIDOS: \"%s\" / Dados COLSULTADOS: \"%s\"\n", combinacoes[i].arquivo_de_dados, combinacoes[i].arquivo_de_teste);

        // ABP
        if(strcmp("100mil_ordenado.csv", combinacoes[i].arquivo_de_dados)!=0){                               // Não insere os 100mil dados ordenados na ABP
            printf("Inserindo na ABP\n");
            leDadosDoArquivoEManipulaArvore(combinacoes[i].arquivo_de_dados, &ABP, ARVORE_ABP, INSERE);      //Insere
            printf("Buscando na ABP\n");
            leDadosDoArquivoEManipulaArvore(combinacoes[i].arquivo_de_teste, &ABP, ARVORE_ABP, CONSULTA);    //Consulta
        }

        printf("----------------\n");
        // AVL
        printf("Inserindo na AVL\n");
        leDadosDoArquivoEManipulaArvore(combinacoes[i].arquivo_de_dados, &AVL, ARVORE_AVL, INSERE);      // Insere
        printf("Buscando na AVL\n");
        leDadosDoArquivoEManipulaArvore(combinacoes[i].arquivo_de_teste, &AVL, ARVORE_AVL, CONSULTA);    // Consulta

        printf("============================================================================================\n\n");

        //limpa ABP e AVL
        desalocaMemoria(ABP);
        desalocaMemoria(AVL);

    }


    return 0;
}
