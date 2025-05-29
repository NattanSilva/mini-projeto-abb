#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct {
  int rgm;
  char nome[80];
} t_elemento;

typedef struct no {
  struct no * esq;
  int dado;
  struct no * dir;
} t_no;

typedef t_no * t_arvore;

t_no * criarNo () {
  t_no * no = (t_no*) malloc(sizeof(t_no));

  if (no) {
    no->dado = -1;
    no->esq = no->dir = NULL;
  }

  return no;
}

int inserirNaArvore (int rgm, t_no * raiz) {
  if(raiz == NULL) {
    printf("No invalido ou nulo\n");
    return -1;
  }

  if(rgm < 0) {
    printf("RGM invalido\n");
    return -1;
  }

  if(rgm > raiz->dado) {
    if(raiz->dir == NULL) {
      raiz->dir = criarNo();
      raiz->dir->dado = rgm;
      printf("RGM %d inserido na direita com sucesso\n", rgm);
      return 1;
    } else {
      return inserirNaArvore(rgm, raiz->dir);
    }
  } else if(rgm < raiz->dado) {
    if(raiz->esq == NULL) {
      raiz->esq = criarNo();
      raiz->esq->dado = rgm;
      printf("RGM %d inserido na esquerda com sucesso\n", rgm);
      return 1;
    } else {
      return inserirNaArvore(rgm, raiz->esq);
    }
  } else {
    printf("RGM %d ja existe na arvore\n", rgm);
    return 0;
  }

  return 1;
}

int pesquisarNaArvore (int rgm, t_no * raiz) {
  if(raiz == NULL || raiz->dado < 0) {
    return -1;
  }
  
  if (raiz->dado == rgm) {
    return raiz->dado;
  } else if(rgm > raiz->dado) {
    return pesquisarNaArvore(rgm, raiz->dir);
  } else {
    return pesquisarNaArvore(rgm, raiz->esq);
  }
  
}

t_no* encontrarSucessor(t_no* no) {
  t_no* atual = no->dir;
  while (atual->esq != NULL) {
    atual = atual->esq;
  }
  
  return atual;
}

// Função para remover um valor da arvore
t_no * removerValor(t_no * raiz, int rgm) {
  if (raiz == NULL) {
    return NULL;
  }

  if (rgm < raiz->dado) {
    raiz->esq = removerValor(raiz->esq, rgm);
  } else if (rgm > raiz->dado) {
    raiz->dir = removerValor(raiz->dir, rgm);
  } else {
    // Caso 1: Nó sem filhos
    if (raiz->esq == NULL && raiz->dir == NULL) {
      free(raiz);
      return NULL;
    }
    
    // Caso 2: Nó com um filho
    if (raiz->esq == NULL) {
      t_no * temp = raiz->dir;
      free(raiz);
      return temp;
    }
      
    if (raiz->dir == NULL) {
      t_no * temp = raiz->esq;
      free(raiz);
      return temp;
    }

    // Caso 3: Nó com dois filhos
    t_no * sucessor = encontrarSucessor(raiz);
    raiz->dado = sucessor->dado;
    raiz->dir = removerValor(raiz->dir, sucessor->dado);
  }
    
  return raiz;
}
  
void menu(t_arvore raiz) {
  int opcao = 0, rgm = 0;

  printf("------------------------------------\n\n");
  printf("ALUNO: %s\n", "NATTAN SILVA");
  printf("DISCIPLINA: ESTRUTURA DE DADOS I\n");
  printf("PROFESSOR: WALACE BONFIM\n\n");
  printf("----------EDITOR DE ÁRVORE----------\n");
  printf("1 - INSERIR - fornecer RGM e Nome\n");
  printf("2 - REMOVER UM NO - fornecer o RGM a remover\n");
  printf("3 - PESQUISAR - fornecer o RGM a pesquisar\n");
  printf("4 - ESVAZIAR A ARVORE\n");
  printf("5 - EXIBIR A ARVORE - tres opcoes: PRE, IN ou POS\n");
  printf("0 - SAIR\n");
  printf("------------------------------------\n");
  printf("DIGITE SUA OPCAO: ");
  scanf("%d", &opcao);
  fflush(stdin);

  switch (opcao) {
    case 1:
      printf("------------------------------------\n");
      printf("INSERIR UM NO\n");
      printf("Digite o RGM: ");
      scanf("%d", &rgm);
      
      if(raiz == NULL) {
        raiz = criarNo();
        raiz->dado = rgm;
        printf("RGM %d inserido na raiz com sucesso\n", rgm);
      }else {
        inserirNaArvore(rgm, raiz);
      }

      menu(raiz);
      break;
    case 2:
      printf("------------------------------------\n");
      printf("REMOVER UM NO\n");
      
      if(raiz == NULL) {
        printf("Arvore vazia\n");
      } else {
        printf("Digite o RGM: ");
        scanf("%d", &rgm);
        removerValor(raiz, rgm);
      }

      menu(raiz);
      break;
    case 3:
      printf("------------------------------------\n");
      printf("PESQUISAR UM NO\n");
      printf("Digite o RGM: ");
      scanf("%d", &rgm);
      int valorBuscado = pesquisarNaArvore(rgm, raiz);

      if (valorBuscado < 0) {
        printf("RGM %d nao encontrado na arvore\n", rgm);
      } else {
        printf("RGM %d encontrado na arvore\n", valorBuscado);
      }

      menu(raiz);
      break;
    case 4:
      printf("------------------------------------\n");
      printf("ESVAZIAR A ARVORE\n");
      break;
    case 5:
      printf("------------------------------------\n");
      printf("EXIBIR A ARVORE\n");
      break;
    case 0:
      printf("------------------------------------\n");
      printf("SAIR\n");
      break;
    default:
      printf("------------------------------------\n");
      printf("OPCAO INVALIDA\n");
      menu(raiz);
      break;
  }
}

int main() {
  setlocale(LC_ALL, "Portuguese_Brazil");
  FILE *arquivo = fopen("dados.txt", "w");

  if(arquivo == NULL) {
    printf("Erro ao abrir o arquivo\n");
    return 1;
  }

  t_arvore raiz = NULL;
  menu(raiz);

  fclose(arquivo);
  
  return 0;
}