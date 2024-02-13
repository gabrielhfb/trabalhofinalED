#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "avalia_senha.h"

void leDadosDoArquivoEManipulaArvore(char nome_arq_entrada[], pNodoA *ptr_arvore, int arvore, int operacao){
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

    if(!(ptr_arquivo = fopen(nome_arq_entrada, "r")))
        printf("Nao foi possivel ler os dados do arquivo\n");
    else{                                                                               // Se conseguiu abrir o arquivo para leitura
        inicio = clock();                                                               // Inicia a contagem do tempo

        while (!feof(ptr_arquivo))
        {
            if (carregaSenhaTXT(ptr_arquivo, &id_lido, senha_lida))                     // Se conseguiu ler o usuario e a senha e
            {
                if(operacao == INSERE){                                                 // Se a operacao for insere,
                    if(arvore == ARVORE_ABP)
                        ptr_arvore = InsereABP(ptr_arvore, id_lido, senha_lida, &comparacoes);        // Insere o dado na ABP ou
                    else if(arvore == ARVORE_AVL)
                        ptr_arvore = InsereAVL(ptr_arvore, id_lido, senha_lida, &ok, &comparacoes);   // Insere o dado na AVL
                }
                else if(operacao == CONSULTA){                                          // Se a operacao for consulta,
                    pt_aux = consultaArvore(ptr_arvore, id_lido, &comparacoes);
                    if(pt_aux != NULL){                                                 // Verifica se o usuario existe
                        if(strcmp(pt_aux->senha, senha_lida) == 0)                      // Se sim, verifica se a senha est� correta
                            senha_correta++;
                        else
                            senha_incorreta++;
                    }else
                        n_encontrados++;
                }
            }
        }
        fclose(ptr_arquivo);                                            // Fecha o arquivo
        fim = clock();                                                  // Encerra a contagem do tempo
        tempo_cpu = ((double)(fim - inicio) / CLOCKS_PER_SEC);          // Transforma a contagem de tempo em segundos

        //Salva os resultados no arquivo
        salvaResultados(nome_arq_entrada, tempo_cpu, ptr_arvore, arvore, operacao, comparacoes, n_encontrados, senha_incorreta, senha_correta);
    }
}

void salvaResultados(char nome_arq_entrada[], double tempo_cpu, pNodoA *ptr_arvore, int arvore, int operacao,
                     int comparacoes, int n_encontrados, int senha_incorreta, int senha_correta){
    FILE *ptr_resultados;
    char nomeArvore[5];

    if(arvore == ARVORE_ABP)
        strcpy(nomeArvore, "ABP");
    else
        strcpy(nomeArvore, "AVL");


    // Escreve os resultados no arquivo
    if(!(ptr_resultados = fopen(ARQUIVO_RESULTADOS, "a")))
        printf("Nao foi possivel escrever os resultados\n");
    else{
        if(operacao == CONSULTA)
            fprintf(ptr_resultados,
                    "Arquivo lido para consultar a %s: %s \n"
                    "Numero de comparacoes realizadas: %d \n"
                    "Numero de usuarios nao encontrados: %d \n"
                    "Numero de senhas incorretas: %d \n"
                    "Numero de senhas corretas: %d \n"
                    "Tempo decorrido: %lf \n",
                    nomeArvore, nome_arq_entrada, comparacoes, n_encontrados, senha_incorreta, senha_correta, tempo_cpu);
        if(operacao == INSERE)
            fprintf(ptr_resultados,
                    "Arquivo lido para carregar a %s: %s \n"
                    "Numero de comparacoes realizadas: %d \n"
                    "Tempo decorrido: %lf \n"
                    "Altura da arvore: %d \n\n",
                    nomeArvore, nome_arq_entrada, comparacoes, tempo_cpu, Altura(ptr_arvore, &comparacoes));

        fclose(ptr_resultados);
    }
}

bool carregaSenhaTXT(FILE *prt_arq, int *id_usuario, char *senha_usuario) {
  char entrada[128];
  char string_id[16];
  char *leitura;
  int i;

  leitura = fgets(entrada, 128, prt_arq);
  if (leitura == NULL) return false;

  for (i = 0; entrada[i] != ','; i++)
    string_id[i] = entrada[i];

  string_id[i] = '\0';
  entrada[strlen(entrada) - 1] = '\0';

  *id_usuario = atoi(string_id);

  strcpy(senha_usuario, &entrada[i + 1]);

  return true;
}

// Consulta
pNodoA *consultaArvore(pNodoA *a, int chave, int *comparacoes) {
  while (a != NULL) {
    if (a->id_usuario == chave) {
      *comparacoes += 1;
      return a;
    } else if (a->id_usuario > chave) {
      *comparacoes += 2;
      a = a->esq;
    } else {
      *comparacoes += 2;
      a = a->dir;
    }
  }
  return NULL;
}

//  ABP

pNodoA *InsereABP(pNodoA *a, int id, char *senha_usuario, int *comparacoes) {
  if (a == NULL) {
    *comparacoes += 1;
    a = (pNodoA *)malloc(sizeof(pNodoA));

    a->id_usuario = id;
    strcpy(a->senha, senha_usuario);

    a->esq = NULL;
    a->dir = NULL;
    return a;

  } else if (id < a->id_usuario) {
    *comparacoes += 2;
    a->esq = InsereABP(a->esq, id, senha_usuario, comparacoes);
  } else if (id > a->id_usuario) {
    *comparacoes += 3;
    a->dir = InsereABP(a->dir, id, senha_usuario, comparacoes);
  }
  return a;
}

// AVL

int Altura(pNodoA *a, int *comparacoes) {
  int Alt_Esq, Alt_Dir;
  if (a == NULL)
    return 0;
  else {
    Alt_Esq = Altura(a->esq, comparacoes);
    Alt_Dir = Altura(a->dir, comparacoes);
    if (Alt_Esq > Alt_Dir) {
      *comparacoes += 1;
      return (1 + Alt_Esq);
    } else {
      *comparacoes += 1;
      return (1 + Alt_Dir);
    }
  }
}

int Calcula_FB(pNodoA *a, int *comparacoes) { return (Altura(a->esq, comparacoes) - Altura(a->dir, comparacoes)); }

pNodoA *rotacao_direita(pNodoA *pt) {
  pNodoA *ptu;

  ptu = pt->esq;
  pt->esq = ptu->dir;
  ptu->dir = pt;
  pt->FB = 0;
  pt = ptu;
  return pt;
}

pNodoA *rotacao_esquerda(pNodoA *pt) {
  pNodoA *ptu;

  ptu = pt->dir;
  pt->dir = ptu->esq;
  ptu->esq = pt;
  pt->FB = 0;
  pt = ptu;
  return pt;
}

pNodoA *rotacao_dupla_direita(pNodoA *pt, int *comparacoes) {
  pNodoA *ptu, *ptv;

  ptu = pt->esq;
  ptv = ptu->dir;
  ptu->dir = ptv->esq;
  ptv->esq = ptu;
  pt->esq = ptv->dir;
  ptv->dir = pt;
  if (ptv->FB == 1) {
    *comparacoes += 1;
    pt->FB = -1;
  } else {
    *comparacoes += 1;
    pt->FB = 0;
  }
  if (ptv->FB == -1) {
    *comparacoes += 1;
    ptu->FB = 1;
  } else {
    *comparacoes += 1;
    ptu->FB = 0;
  }
  pt = ptv;
  return pt;
}

pNodoA *rotacao_dupla_esquerda(pNodoA *pt, int *comparacoes) {
  pNodoA *ptu, *ptv;

  ptu = pt->dir;
  ptv = ptu->esq;
  ptu->esq = ptv->dir;
  ptv->dir = ptu;
  pt->dir = ptv->esq;
  ptv->esq = pt;
  if (ptv->FB == -1) {
    *comparacoes += 1;
    pt->FB = 1;
  } else {
    *comparacoes += 1;
    pt->FB = 0;
  }
  if (ptv->FB == 1) {
    *comparacoes += 1;
    ptu->FB = -1;
  } else {
    *comparacoes += 1;
    ptu->FB = 0;
  }
  pt = ptv;
  return pt;
}

pNodoA *Caso1(pNodoA *a, int *ok, int *comparacoes) {
  pNodoA *ptu;

  ptu = a->esq;
  if (ptu->FB == 1) {
    *comparacoes += 1;
    a = rotacao_direita(a);
  } else {
    *comparacoes += 1;
    a = rotacao_dupla_direita(a, comparacoes);
  }

  a->FB = 0;
  *ok = 0;
  return a;
}

pNodoA *Caso2(pNodoA *a, int *ok, int *comparacoes) {
  pNodoA *ptu;

  ptu = a->dir;
  if (ptu->FB == -1) {
    a = rotacao_esquerda(a);
  } else {
    a = rotacao_dupla_esquerda(a, comparacoes);
  }
  a->FB = 0;
  *ok = 0;
  return a;
}

pNodoA *InsereAVL(pNodoA *a, int id, char *senha_usuario, int *ok, int *comparacoes) {
  if (a == NULL) {
    *comparacoes += 1;
    a = (pNodoA *)malloc(sizeof(pNodoA));

    a->id_usuario = id;
    strcpy(a->senha, senha_usuario);

    a->esq = NULL;
    a->dir = NULL;
    a->FB = 0;
    *ok = 1;
  } else if (id < a->id_usuario) {
    a->esq = InsereAVL(a->esq, id, senha_usuario, ok, comparacoes);
    if (*ok) {
      switch (a->FB) {
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
  } else {
    a->dir = InsereAVL(a->dir, id, senha_usuario, ok, comparacoes);
    if (*ok) {
      switch (a->FB) {
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
