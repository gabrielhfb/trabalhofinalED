#include <avalia_senha.h>

int main(void) {
  FILE *ptr_entrada, *ptr_resultados;
  char arq_entrada[32] = "entrada.txt";
  char arq_resultados[32] = "results.txt";

  int id_lido;
  char senha_lida[128];
  int ok;

  clock_t inicio, fim;
  double tempo_cpu;

  pNodoA *ABP = NULL;
  pNodoA *AVL = NULL;

  ptr_resultados = fopen(
      arq_resultados, "w");  // Abre o arquivo para armazenamento dos resultados
  //////

  // Montagem da ABP
  comparacoes = 0;
  ptr_entrada = fopen(arq_entrada, "r");

  inicio = clock();  // Inicia a contagem do tempo

  while (!feof(ptr_entrada)) {
    if (carregaSenhaTXT(ptr_entrada, &id_lido, senha_lida)) {
      InsereABP(ABP, id_lido, senha_lida);
    }
  }

  fim = clock();  // Encerra a contagem do tempo
  tempo_cpu = ((double)(fim - inicio) /
               CLOCKS_PER_SEC);  // Transforma a contagem de tempo em segundos

  fclose(ptr_entrada);
  fprintf(ptr_resultados,
          "Arquivo lido para carregamento da ABP: %s \n Numero de comparacoes "
          "realizadas: %d \n Tempo decorrido: %lf \n Altura da arvore: %d \n\n",
          arq_entrada, comparacoes, tempo_cpu, Altura(ABP));

  // Consultas na ABP
  comparacoes = 0;
  ptr_entrada = fopen(arq_entrada, "r");

  inicio = clock();  // Inicia a contagem do tempo

  while (!feof(ptr_entrada)) {
    if (carregaSenhaTXT(ptr_entrada, &id_lido, senha_lida)) {
      // Procura na ABP o que acabou de ser lido
    }
  }

  fim = clock();  // Encerra a contagem do tempo
  tempo_cpu = ((double)(fim - inicio) /
               CLOCKS_PER_SEC);  // Transforma a contagem de tempo em segundos

  fclose(ptr_entrada);
  fprintf(ptr_resultados,
          "Arquivo lido para consulta na ABP: %s \n Numero de comparacoes "
          "realizadas: %d \n Tempo decorrido: %lf \n\n",
          arq_entrada, comparacoes, tempo_cpu);

  // Montagem da AVL
  comparacoes = 0;
  ptr_entrada = fopen(arq_entrada, "r");

  inicio = clock();  // Inicia a contagem do tempo

  while (!feof(ptr_entrada)) {
    if (carregaSenhaTXT(ptr_entrada, &id_lido, senha_lida)) {
      InsereAVL(ABP, id_lido, senha_lida, &ok);
    }
  }

  fim = clock();  // Encerra a contagem do tempo
  tempo_cpu = ((double)(fim - inicio) /
               CLOCKS_PER_SEC);  // Transforma a contagem de tempo em segundos

  fclose(ptr_entrada);
  fprintf(ptr_resultados,
          "Arquivo lido para carregamento da AVL: %s \n Numero de comparacoes "
          "realizadas: %d \n Tempo decorrido: %lf \n Altura da arvore: %d\n\n",
          arq_entrada, comparacoes, tempo_cpu, Altura(AVL));

  // Consultas na AVL
  comparacoes = 0;
  ptr_entrada = fopen(arq_entrada, "r");

  inicio = clock();  // Inicia a contagem do tempo

  while (!feof(ptr_entrada)) {
    if (carregaSenhaTXT(ptr_entrada, &id_lido, senha_lida)) {
      // Procura na AVL o que acabou de ser lido
    }
  }

  fim = clock();  // Encerra a contagem do tempo
  tempo_cpu = ((double)(fim - inicio) /
               CLOCKS_PER_SEC);  // Transforma a contagem de tempo em segundos

  fclose(ptr_entrada);
  fprintf(ptr_resultados,
          "Arquivo lido para consulta na AVL: %s \n Numero de comparacoes "
          "realizadas: %d \n Tempo decorrido: %lf\n",
          arq_entrada, comparacoes, tempo_cpu);

  return 0;
}
