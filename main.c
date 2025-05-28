#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    printf("Nó inválido ou nulo\n");
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
    printf("RGM %d já existe na árvore\n", rgm);
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
  
void menu(t_arvore raiz) {
  int opcao = 0, rgm = 0;

  printf("------------------------------------\n\n");
  printf("ALUNO: %s\n", "NATTAN SILVA");
  printf("DISCIPLINA: ESTRUTURA DE DADOS I\n");
  printf("PROFESSOR: WALACE BONFIM\n\n");
  printf("----------EDITOR DE ÁRVORE----------\n");
  printf("1 – INSERIR – fornecer RGM e Nome\n");
  printf("2 – REMOVER UM NÓ – fornecer o RGM a remover\n");
  printf("3 – PESQUISAR – fornecer o RGM a pesquisar\n");
  printf("4 – ESVAZIAR A ÁRVORE\n");
  printf("5 – EXIBIR A ÁRVORE – três opções: PRÉ, IN ou PÓS\n");
  printf("0 – SAIR\n");
  printf("------------------------------------\n");
  printf("DIGITE SUA OPÇÃO: ");
  scanf("%d", &opcao);
  fflush(stdin);

  switch (opcao) {
    case 1:
      printf("------------------------------------\n");
      printf("INSERIR UM NÓ\n");
      printf("Digite o RGM: ");
      scanf("%d", &rgm);
      
      if(raiz->dado < 0) {
        raiz->dado = rgm;
        printf("RGM %d inserido na raiz com sucesso\n", rgm);
      }else {
        inserirNaArvore(rgm, raiz);
      }

      menu(raiz);
      break;
    case 2:
      printf("------------------------------------\n");
      printf("REMOVER UM NÓ\n");
      break;
    case 3:
      printf("------------------------------------\n");
      printf("PESQUISAR UM NÓ\n");
      printf("Digite o RGM: ");
      scanf("%d", &rgm);
      int valorBuscado = pesquisarNaArvore(rgm, raiz);

      if (valorBuscado < 0) {
        printf("RGM %d não encontrado na árvore\n", rgm);
      } else {
        printf("RGM %d encontrado na árvore\n", rgm);
      }

      menu(raiz);
      break;
    case 4:
      printf("------------------------------------\n");
      printf("ESVAZIAR A ÁRVORE\n");
      break;
    case 5:
      printf("------------------------------------\n");
      printf("EXIBIR A ÁRVORE\n");
      break;
    case 0:
      printf("------------------------------------\n");
      printf("SAIR\n");
      break;
    default:
      printf("------------------------------------\n");
      printf("OPÇÃO INVÁLIDA\n");
      menu(raiz);
      break;
  }
}

int main() {
  FILE *arquivo = fopen("dados.txt", "w");

  if(arquivo == NULL) {
    printf("Erro ao abrir o arquivo\n");
    return 1;
  }

  t_arvore raiz = criarNo();
  menu(raiz);

  fclose(arquivo);
  
  return 0;
}