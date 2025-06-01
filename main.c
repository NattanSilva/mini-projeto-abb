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

t_no * encontrarSucessor(t_no *raiz) {
  if (raiz == NULL) return NULL;

  t_no *atual = raiz;
  while (atual->esq != NULL) {
    atual = atual->esq;
  }

  return atual;
}

// Função para remover um valor da arvore
void removerValor(t_no ** raiz, int valor) {
  if (*raiz == NULL) {
    printf("Valor não encontrado na árvore.\n");
    return;
  }

  if (valor < 0) {
    printf("Valor inválido\n");
    return;
  }

  if (valor < (*raiz)->dado) {
    removerValor(&((*raiz)->esq), valor);
  } else if (valor > (*raiz)->dado) {
    removerValor(&((*raiz)->dir), valor);
  } else {
    // Encontrou o nó a ser removido
    t_no *no = *raiz;

    // Caso 1: Sem filhos
    if (no->esq == NULL && no->dir == NULL) {
      printf("Valor removido: %d\n", no->dado);
      free(no);
      *raiz = NULL;
    }

    // Caso 2: Um filho à direita
    else if (no->esq == NULL) {
      printf("Valor removido: %d\n", no->dado);
      *raiz = no->dir;
      free(no);
    }

    // Caso 2: Um filho à esquerda
    else if (no->dir == NULL) {
      printf("Valor removido: %d\n", no->dado);
      *raiz = no->esq;
      free(no);
    }

    // Caso 3: Dois filhos
    else {
      t_no *sucessor = encontrarSucessor(no->dir);
      no->dado = sucessor->dado;
      removerValor(&(no->dir), sucessor->dado);
    }
  }
}

void listagemPreOrdem(t_no * raiz) {
  if (raiz != NULL) {
    printf("%d ", raiz->dado);
    listagemPreOrdem(raiz->esq);
    listagemPreOrdem(raiz->dir);
  }
}

void listagemInOrdem(t_no * raiz) {
  if (raiz != NULL) {
    listagemInOrdem(raiz->esq);
    printf("%d ", raiz->dado);
    listagemInOrdem(raiz->dir);
  }
}

void listagemPosOrdem(t_no * raiz) {
  if (raiz != NULL) {
    listagemPosOrdem(raiz->esq);
    listagemPosOrdem(raiz->dir);
    printf("%d ", raiz->dado);
  }
}

void listagemGraficamente(t_no* raiz, int espaco) {
  if (raiz == NULL) return;

  espaco += 5;

  // Primeiro desenha o lado direito
  listagemGraficamente(raiz->dir, espaco);

  // Imprime o nó atual com indentação
  printf("\n");
  for (int i = 5; i < espaco; i++) {
    printf(" ");
  }
  
  printf("%d\n", raiz->dado);

  // Depois desenha o lado esquerdo
  listagemGraficamente(raiz->esq, espaco);
}

void menuDeListagem(t_arvore raiz) {
  int opcao = 0;
  printf("------------------------------------\n");
  printf("EXIBIR A ARVORE\n");
  printf("1 - PRE\n");
  printf("2 - IN\n");
  printf("3 - POS\n");
  printf("4 - GRAFICAMENTE\n");
  printf("Digite a opcao: ");
  scanf("%d", &opcao);
  fflush(stdin);

  switch (opcao) {
    case 1:
      printf("------------------------------------\n");
      printf("PRE\n");
      
      if(raiz == NULL) {
        printf("Arvore vazia\n");
        break;
      } else {
        listagemPreOrdem(raiz);
        printf("\n");
      }
      
      break;
    case 2:
      printf("IN\n");

      if(raiz == NULL) {
        printf("Arvore vazia\n");
        break;
      } else {
        listagemInOrdem(raiz);
        printf("\n");
      }
      
      break;
    case 3:
      printf("POS\n");

      if(raiz == NULL) {
        printf("Arvore vazia\n");
        break;
      } else {
        listagemPosOrdem(raiz);
        printf("\n");
      }

      break;
    case 4:
      printf("GRAFICAMENTE\n");

      if(raiz == NULL) {
        printf("Arvore vazia\n");
        break;
      } else {
        listagemGraficamente(raiz, 0);
      }

      break;
    default:
      printf("Opcao invalida\n");
      menuDeListagem(raiz);
      break;
  }
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
        removerValor(&raiz, rgm);
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
      menuDeListagem(raiz);
      menu(raiz);
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