#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "avalia_senha.h"

int main(void)
{
    CombinacoesArquivos combinacoes[TOTAL_DE_COMBINACOES];
    montaCombinacoesDeTestes(combinacoes);

    //int espera_ate_arquivos_serem_montados;
    //scanf("%d", &espera_ate_arquivos_serem_montados);



    for(int i=0; i<20; i++){
        pNodoA *ABP = NULL;
        pNodoA *AVL = NULL;

        // ABP
        printf("INSERINDO os dados do arquivo \"%s\" na ABP\n", combinacoes[i].arquivo_de_dados);
        leDadosDoArquivoEManipulaArvore(combinacoes[i].arquivo_de_dados, &ABP, ARVORE_ABP, INSERE);      //Insere

        printf("BUSCANDO os dados do arquivo \"%s\" na ABP\n\n", combinacoes[i].arquivo_de_teste);
        leDadosDoArquivoEManipulaArvore(combinacoes[i].arquivo_de_teste, &ABP, ARVORE_ABP, CONSULTA);    //Consulta

        // AVL
        printf("INSERINDO os dados do arquivo \"%s\" na AVL\n", combinacoes[i].arquivo_de_dados);
        leDadosDoArquivoEManipulaArvore(combinacoes[i].arquivo_de_dados, &AVL, ARVORE_AVL, INSERE);      // Insere

        printf("BUSCANDO os dados do arquivo \"%s\" na AVL\n\n", combinacoes[i].arquivo_de_teste);
        leDadosDoArquivoEManipulaArvore(combinacoes[i].arquivo_de_teste, &AVL, ARVORE_AVL, CONSULTA);    // Consulta

        //limpa ABP e AVL
        desalocaMemoria(ABP);
        desalocaMemoria(AVL);

    }


    return 0;
}
