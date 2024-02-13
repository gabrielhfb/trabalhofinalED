#include "avalia_senha.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


void montaCombinacoesDeTestes(CombinacoesArquivos combinacoes[]){
    char nomes_arquivos_de_dados[N_ARQUIVOS_DADOS][LENGHT_STRINGS] = {"500_ordenado.csv",
                                                                        "500_desordenado.csv",
                                                                        "10mil_ordenado.csv",
                                                                        "10mil_desordenado.csv",
                                                                        "100mil_ordenado.csv",
                                                                        "100mil_desordenado.csv"};

    char arquivos_de_teste_500[N_ARQUIVOS_TESTES_500][LENGHT_STRINGS] = {"10u_base500_1e.csv",
                                                                        "10u_base500_5e.csv",
                                                                        "100u_base500_10e.csv",
                                                                        "100u_base500_50e.csv"};

    char arquivos_de_teste_10mil[N_ARQUIVOS_TESTES][LENGHT_STRINGS] = {"10u_base10mil_1e.csv",
                                                                        "10u_base10mil_5e.csv",
                                                                        "100u_base10mil_10e.csv",
                                                                        "100u_base10mil_50e.csv",
                                                                        "1000u_base10mil_100e.csv",
                                                                        "1000u_base10mil_500e.csv"};

    char arquivos_de_teste_100mil[N_ARQUIVOS_TESTES][LENGHT_STRINGS] = {"10u_base100mil_1e.csv",
                                                                        "10u_base100mil_5e.csv",
                                                                        "100u_base100mil_10e.csv",
                                                                        "100u_base100mil_50e.csv",
                                                                        "1000u_base100mil_100e.csv",
                                                                        "1000u_base100mil_500e.csv"};

    int c = 0;      // contador para as combinações

    // Cria combinacoes para os arquivos de 500 dados
    for(int i=0; i<2; i++){
        for(int j=0; j<N_ARQUIVOS_TESTES_500; j++){
            strcpy(combinacoes[c].arquivo_de_dados, nomes_arquivos_de_dados[i]);
            strcpy(combinacoes[c].arquivo_de_teste, arquivos_de_teste_500[j]);
            //printf("%d - Arquivo de dados: %s, Arquivo de testes: %s\n", c+1, combinacoes[c].arquivo_de_dados, combinacoes[c].arquivo_de_teste);
            c++;
        }
    }

    // Cria combinacoes para os arquivos de 10000 e 100000 dados
    for(int i =2; i<N_ARQUIVOS_DADOS; i++){
        for(int j=0; j<N_ARQUIVOS_TESTES; j++){
            strcpy(combinacoes[c].arquivo_de_dados, nomes_arquivos_de_dados[i]);
            if((i==2 || i==3))
                strcpy(combinacoes[c].arquivo_de_teste, arquivos_de_teste_10mil[j]);
            else
                strcpy(combinacoes[c].arquivo_de_teste, arquivos_de_teste_100mil[j]);

            //printf("%d - Arquivo de dados: %s, Arquivo de testes: %s\n", c+1, combinacoes[c].arquivo_de_dados, combinacoes[c].arquivo_de_teste);
            c++;
        }
    }
}

void desalocaMemoria (pNodoA *a){
    if(a != NULL){
        desalocaMemoria(a->esq);
        desalocaMemoria(a->dir);
        free(a);
    }
}


void leDadosDoArquivoEManipulaArvore(char nome_arq_entrada[],
                                     pNodoA **ptr_arvore, int arvore,
                                     int operacao)
{
    FILE *ptr_arquivo;

    int id_lido;
    char senha_lida[128];

    clock_t inicio, fim;
    double tempo_cpu;

    int ok;

    int comparacoes = 0;
    int n_encontrados = 0;
    int senha_incorreta = 0;
    int senha_correta = 0;

    pNodoA *pt_aux = NULL;

    if (!(ptr_arquivo = fopen(nome_arq_entrada, "r")))
        printf("Nao foi possivel ler os dados do arquivo\n");
    else                 // Se conseguiu abrir o arquivo para leitura
    {

        fgets(senha_lida, 128, ptr_arquivo);

        inicio = clock();  // Inicia a contagem do tempo

        while (!feof(ptr_arquivo))
        {
            if ((id_lido = carregaSenhaTXT(
                               ptr_arquivo,
                               senha_lida)) != -1)  // Se conseguiu ler o usuario e a senha e
            {
                if (operacao == INSERE)    // Se a operacao for insere,
                {
                    if (arvore == ARVORE_ABP)
                        *ptr_arvore = InsereABP(*ptr_arvore, id_lido, senha_lida,
                                                &comparacoes);  // Insere o dado na ABP ou
                    else if (arvore == ARVORE_AVL)
                        *ptr_arvore = InsereAVL(*ptr_arvore, id_lido, senha_lida, &ok,
                                                &comparacoes);  // Insere o dado na AVL
                }
                else if (operacao == CONSULTA)      // Se a operacao for consulta,
                {
                    pt_aux = consultaArvore(*ptr_arvore, id_lido, &comparacoes);
                    if (pt_aux != NULL)    // Verifica se o usuario existe
                    {
                        if (strcmp(pt_aux->senha, senha_lida) ==
                                0)  // Se sim, verifica se a senha est� correta
                            senha_correta++;
                        else
                            senha_incorreta++;
                    }
                    else
                        n_encontrados++;
                }
            }
        }
        fclose(ptr_arquivo);  // Fecha o arquivo
        fim = clock();        // Encerra a contagem do tempo
        tempo_cpu = ((double)(fim - inicio) /
                     CLOCKS_PER_SEC);  // Transforma a contagem de tempo em segundos

        // Salva os resultados no arquivo
        salvaResultados(nome_arq_entrada, tempo_cpu, *ptr_arvore, arvore, operacao,
                        comparacoes, n_encontrados, senha_incorreta, senha_correta);
    }
}

void salvaResultados(char nome_arq_entrada[], double tempo_cpu,
                     pNodoA *ptr_arvore, int arvore, int operacao,
                     int comparacoes, int n_encontrados, int senha_incorreta,
                     int senha_correta)
{
    FILE *ptr_resultados;
    char nomeArvore[5];

    if (arvore == ARVORE_ABP)
        strcpy(nomeArvore, "ABP");
    else
        strcpy(nomeArvore, "AVL");

    // Escreve os resultados no arquivo
    if (!(ptr_resultados = fopen(ARQUIVO_RESULTADOS, "a")))
        printf("Nao foi possivel escrever os resultados\n");
    else
    {
        if (operacao == CONSULTA)
            fprintf(ptr_resultados,
                    "Arquivo lido para consultar a %s: %s \n"
                    "Numero de comparacoes realizadas: %d \n"
                    "Numero de usuarios nao encontrados: %d \n"
                    "Numero de senhas incorretas: %d \n"
                    "Numero de senhas corretas: %d \n"
                    "Tempo decorrido: %lf \n\n",
                    nomeArvore, nome_arq_entrada, comparacoes, n_encontrados,
                    senha_incorreta, senha_correta, tempo_cpu);
        if (operacao == INSERE)
            fprintf(ptr_resultados,
                    "Arquivo lido para carregar a %s: %s \n"
                    "Numero de comparacoes realizadas: %d \n"
                    "Tempo decorrido: %lf \n"
                    "Altura da arvore: %d \n\n",
                    nomeArvore, nome_arq_entrada, comparacoes, tempo_cpu,
                    Altura(ptr_arvore, &comparacoes));

        fclose(ptr_resultados);
    }
}

int carregaSenhaTXT(FILE *prt_arq, char *senha_usuario)
{
    char entrada[128];
    int id_usuario;
    char *leitura;
    int i;

    leitura = fgets(entrada, 128, prt_arq);
    if (leitura == NULL) return -1;

    for (i = 0; entrada[i] != ','; i++);
    entrada[i] = '\0';
    senha_usuario = &entrada[i+1];

    id_usuario = atoi(entrada);

    return id_usuario;
}


// Consulta
pNodoA *consultaArvore(pNodoA *a, int chave, int *comparacoes)
{
    while (a != NULL)
    {
        if (a->id_usuario == chave)
        {
            *comparacoes += 1;
            return a;
        }
        else if (a->id_usuario > chave)
        {
            *comparacoes += 2;
            a = a->esq;
        }
        else
        {
            *comparacoes += 2;
            a = a->dir;
        }
    }
    return NULL;
}

//  ABP

pNodoA *InsereABP(pNodoA *a, int id, char *senha_usuario, int *comparacoes)
{
    if (a == NULL)
    {
        *comparacoes += 1;
        a = (pNodoA *)malloc(sizeof(pNodoA));

        a->id_usuario = id;
        strcpy(a->senha, senha_usuario);

        a->esq = NULL;
        a->dir = NULL;
        return a;

    }
    else if (id < a->id_usuario)
    {
        *comparacoes += 2;
        a->esq = InsereABP(a->esq, id, senha_usuario, comparacoes);
    }
    else if (id > a->id_usuario)
    {
        *comparacoes += 3;
        a->dir = InsereABP(a->dir, id, senha_usuario, comparacoes);
    }
    return a;
}

// AVL

int Altura(pNodoA *a, int *comparacoes)
{
    int Alt_Esq, Alt_Dir;
    if (a == NULL)
        return 0;
    else
    {
        Alt_Esq = Altura(a->esq, comparacoes);
        Alt_Dir = Altura(a->dir, comparacoes);
        if (Alt_Esq > Alt_Dir)
        {
            *comparacoes += 1;
            return (1 + Alt_Esq);
        }
        else
        {
            *comparacoes += 1;
            return (1 + Alt_Dir);
        }
    }
}

int Calcula_FB(pNodoA *a, int *comparacoes)
{
    return (Altura(a->esq, comparacoes) - Altura(a->dir, comparacoes));
}

pNodoA *rotacao_direita(pNodoA *pt)
{
    pNodoA *ptu;

    ptu = pt->esq;
    pt->esq = ptu->dir;
    ptu->dir = pt;
    pt->FB = 0;
    pt = ptu;
    return pt;
}

pNodoA *rotacao_esquerda(pNodoA *pt)
{
    pNodoA *ptu;

    ptu = pt->dir;
    pt->dir = ptu->esq;
    ptu->esq = pt;
    pt->FB = 0;
    pt = ptu;
    return pt;
}

pNodoA *rotacao_dupla_direita(pNodoA *pt, int *comparacoes)
{
    pNodoA *ptu, *ptv;

    ptu = pt->esq;
    ptv = ptu->dir;
    ptu->dir = ptv->esq;
    ptv->esq = ptu;
    pt->esq = ptv->dir;
    ptv->dir = pt;
    if (ptv->FB == 1)
    {
        *comparacoes += 1;
        pt->FB = -1;
    }
    else
    {
        *comparacoes += 1;
        pt->FB = 0;
    }
    if (ptv->FB == -1)
    {
        *comparacoes += 1;
        ptu->FB = 1;
    }
    else
    {
        *comparacoes += 1;
        ptu->FB = 0;
    }
    pt = ptv;
    return pt;
}

pNodoA *rotacao_dupla_esquerda(pNodoA *pt, int *comparacoes)
{
    pNodoA *ptu, *ptv;

    ptu = pt->dir;
    ptv = ptu->esq;
    ptu->esq = ptv->dir;
    ptv->dir = ptu;
    pt->dir = ptv->esq;
    ptv->esq = pt;
    if (ptv->FB == -1)
    {
        *comparacoes += 1;
        pt->FB = 1;
    }
    else
    {
        *comparacoes += 1;
        pt->FB = 0;
    }
    if (ptv->FB == 1)
    {
        *comparacoes += 1;
        ptu->FB = -1;
    }
    else
    {
        *comparacoes += 1;
        ptu->FB = 0;
    }
    pt = ptv;
    return pt;
}

pNodoA *Caso1(pNodoA *a, int *ok, int *comparacoes)
{
    pNodoA *ptu;

    ptu = a->esq;
    if (ptu->FB == 1)
    {
        *comparacoes += 1;
        a = rotacao_direita(a);
    }
    else
    {
        *comparacoes += 1;
        a = rotacao_dupla_direita(a, comparacoes);
    }

    a->FB = 0;
    *ok = 0;
    return a;
}

pNodoA *Caso2(pNodoA *a, int *ok, int *comparacoes)
{
    pNodoA *ptu;

    ptu = a->dir;
    if (ptu->FB == -1)
    {
        a = rotacao_esquerda(a);
    }
    else
    {
        a = rotacao_dupla_esquerda(a, comparacoes);
    }
    a->FB = 0;
    *ok = 0;
    return a;
}

pNodoA *InsereAVL(pNodoA *a, int id, char *senha_usuario, int *ok,
                  int *comparacoes)
{
    if (a == NULL)
    {
        *comparacoes += 1;
        a = (pNodoA *)malloc(sizeof(pNodoA));

        a->id_usuario = id;
        strcpy(a->senha, senha_usuario);

        a->esq = NULL;
        a->dir = NULL;
        a->FB = 0;
        *ok = 1;
    }
    else if (id < a->id_usuario)
    {
        a->esq = InsereAVL(a->esq, id, senha_usuario, ok, comparacoes);
        if (*ok)
        {
            switch (a->FB)
            {
            case -1:
                *comparacoes += 1;
                a->FB = 0;
                *ok = 0;
                break;
            case 0:
                *comparacoes += 2;
                a->FB = 1;
                break;
            case 1:
                *comparacoes += 3;
                a = Caso1(a, ok, comparacoes);
                break;
            }
        }
    }
    else
    {
        a->dir = InsereAVL(a->dir, id, senha_usuario, ok, comparacoes);
        if (*ok)
        {
            switch (a->FB)
            {
            case 1:
                *comparacoes += 1;
                a->FB = 0;
                *ok = 0;
                break;
            case 0:
                *comparacoes += 2;
                a->FB = -1;
                break;
            case -1:
                *comparacoes += 3;
                a = Caso2(a, ok, comparacoes);
                break;
            }
        }
    }
    return a;
}
