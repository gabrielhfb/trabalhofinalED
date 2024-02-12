#include "avalia_senha.h"

bool carregaSenhaTXT(FILE *prt_arq, int *id_usuario, char *senha_usuario) {
  char entrada[128];
  char string_id[16];
  char *leitura;
  int i;

  leitura = fgets(entrada, 128, prt_arq);
  if (leitura == NULL) return false;

  for (i = 0; entrada[i] != ','; i++) {
    string_id[i] = entrada[i];
  }

  string_id[i] = '/0';
  entrada[strlen(entrada) - 1] = '\0';

  *id_usuario = atoi(string_id);

  strcpy(senha_usuario, &entrada[i + 1]);

  return true;
}

// Consulta
pNodoA *consultaArvore(pNodoA *a, int chave) {
  while (a != NULL) {
    if (a->id_usuario == chave) {
      comparacoes++;
      return a;
    } else if (a->id_usuario > chave) {
      comparacoes += 2;
      a = a->esq;
    } else {
      comparacoes += 3;
      a = a->dir;
    }
  }
  return NULL;
}

//  ABP

pNodoA *InsereABP(pNodoA *a, int id, char *senha_usuario) {
  if (a == NULL) {
    comparacoes++;
    a = (pNodoA *)malloc(sizeof(pNodoA));

    a->id_usuario = id;
    strcpy(a->senha, senha_usuario);

    a->esq = NULL;
    a->dir = NULL;
    return a;

  } else if (id < a->id_usuario) {
    comparacoes += 2;
    a->esq = InsereABP(a->esq, id, senha_usuario);
  } else if (id > a->id_usuario) {
    comparacoes += 3;
    a->dir = InsereABP(a->dir, id, senha_usuario);
  }
  return a;
}

// AVL

int Altura(pNodoA *a) {
  int Alt_Esq, Alt_Dir;
  if (a == NULL)
    return 0;
  else {
    Alt_Esq = Altura(a->esq);
    Alt_Dir = Altura(a->dir);
    if (Alt_Esq > Alt_Dir) {
      comparacoes++;
      return (1 + Alt_Esq);
    } else {
      comparacoes++;
      return (1 + Alt_Dir);
    }
  }
}

int Calcula_FB(pNodoA *a) { return (Altura(a->esq) - Altura(a->dir)); }

/* int is_avl(pNodoA *a) {
  int alt_esq, alt_dir;

  if (a != NULL) {
    comparacoes++;
    alt_esq = Altura(a->esq);
    alt_dir = Altura(a->dir);
    return ((alt_esq - alt_dir < 2) && (alt_dir - alt_esq < 2) &&
            (is_avl(a->esq)) && (is_avl(a->dir)));
  } else
    comparacoes++;
  return 1;
} */

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

pNodoA *rotacao_dupla_direita(pNodoA *pt) {
  pNodoA *ptu, *ptv;

  ptu = pt->esq;
  ptv = ptu->dir;
  ptu->dir = ptv->esq;
  ptv->esq = ptu;
  pt->esq = ptv->dir;
  ptv->dir = pt;
  if (ptv->FB == 1) {
    comparacoes++;
    pt->FB = -1;
  } else {
    comparacoes++;
    pt->FB = 0;
  }
  if (ptv->FB == -1) {
    comparacoes++;
    ptu->FB = 1;
  } else {
    comparacoes++;
    ptu->FB = 0;
  }
  pt = ptv;
  return pt;
}

pNodoA *rotacao_dupla_esquerda(pNodoA *pt) {
  pNodoA *ptu, *ptv;

  ptu = pt->dir;
  ptv = ptu->esq;
  ptu->esq = ptv->dir;
  ptv->dir = ptu;
  pt->dir = ptv->esq;
  ptv->esq = pt;
  if (ptv->FB == -1) {
    comparacoes++;
    pt->FB = 1;
  } else {
    comparacoes++;
    pt->FB = 0;
  }
  if (ptv->FB == 1) {
    comparacoes++;
    ptu->FB = -1;
  } else {
    comparacoes++;
    ptu->FB = 0;
  }
  pt = ptv;
  return pt;
}

pNodoA *Caso1(pNodoA *a, int *ok) {
  pNodoA *ptu;

  ptu = a->esq;
  if (ptu->FB == 1) {
    comparacoes++;
    a = rotacao_direita(a);
  } else {
    comparacoes++;
    a = rotacao_dupla_direita(a);
  }

  a->FB = 0;
  *ok = 0;
  return a;
}

pNodoA *Caso2(pNodoA *a, int *ok) {
  pNodoA *ptu;

  ptu = a->dir;
  if (ptu->FB == -1) {
    a = rotacao_esquerda(a);
  } else {
    a = rotacao_dupla_esquerda(a);
  }
  a->FB = 0;
  *ok = 0;
  return a;
}

pNodoA *InsereAVL(pNodoA *a, int id, char *senha_usuario, int *ok) {
  if (a == NULL) {
    comparacoes++;
    a = (pNodoA *)malloc(sizeof(pNodoA));

    a->id_usuario = id;
    strcpy(a->senha, senha_usuario);

    a->esq = NULL;
    a->dir = NULL;
    a->FB = 0;
    *ok = 1;
  } else if (id < a->id_usuario) {
    a->esq = InsereAVL(a->esq, id, senha_usuario, ok);
    if (*ok) {
      switch (a->FB) {
        case -1:
          comparacoes++;
          a->FB = 0;
          *ok = 0;
          break;
        case 0:
          comparacoes += 2;
          a->FB = 1;
          break;
        case 1:
          comparacoes += 3;
          a = Caso1(a, ok);
          break;
      }
    }
  } else {
    a->dir = InsereAVL(a->dir, id, senha_usuario, ok);
    if (*ok) {
      switch (a->FB) {
        case 1:
          comparacoes++;
          a->FB = 0;
          *ok = 0;
          break;
        case 0:
          comparacoes += 2;
          a->FB = -1;
          break;
        case -1:
          comparacoes += 3;
          a = Caso2(a, ok);
          break;
      }
    }
  }
  return a;
}