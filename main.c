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
  t_elemento dado;
  struct no * dir;
} t_no;

typedef t_no * t_arvore;

t_no * criarNo () {
  t_no * no = (t_no*) malloc(sizeof(t_no));

  if (no) {
    no->dado.rgm = -1;
    no->esq = no->dir = NULL;
  }

  return no;
}

int inserirNaArvore (int rgm, char * nome, t_no * raiz) {
  if(raiz == NULL) {
    printf("No invalido ou nulo\n");
    return -1;
  }

  if(rgm < 0) {
    printf("RGM invalido\n");
    return -1;
  }

  if(rgm > raiz->dado.rgm) {
    if(raiz->dir == NULL) {
      raiz->dir = criarNo();
      raiz->dir->dado.rgm = rgm;
      strcpy(raiz->dir->dado.nome, nome);
      return 1;
    } else {
      return inserirNaArvore(rgm, nome, raiz->dir);
    }
  } else if(rgm < raiz->dado.rgm) {
    if(raiz->esq == NULL) {
      raiz->esq = criarNo();
      raiz->esq->dado.rgm = rgm;
      strcpy(raiz->esq->dado.nome, nome);
      return 1;
    } else {
      return inserirNaArvore(rgm, nome, raiz->esq);
    }
  } else {
    printf("RGM %d ja existe na arvore\n", rgm);
    return 0;
  }

  return 1;
}




//pesquisa por 1 aluno
t_no * pesquisaNo (int rgm, t_no * arvore) {

  if(arvore == NULL || arvore->dado.rgm < 0)
    return NULL;

  if (arvore->dado.rgm == rgm) {
    return arvore;
  }

  else if(rgm > arvore->dado.rgm)
     return pesquisaNo(rgm, arvore->dir);

  else
    return pesquisaNo(rgm, arvore->esq);
}

t_no * encontrarSucessor(t_no *raiz) {
  if (raiz == NULL) return NULL;

  t_no *atual = raiz;
  while (atual->esq != NULL) {
    atual = atual->esq;
  }

  return atual;
}

// Responsável por remover um aluno da árvore dado o RGM
void removerAlunoPorRGM(t_no ** raiz, int rgm) {
    if (*raiz == NULL) {
        printf("Aluno com RGM %d não encontrado na árvore.\n", rgm);
        return;
    }

    if (rgm < 0) {
        printf("RGM inválido.\n");
        return;
    }

    if (rgm < (*raiz)->dado.rgm) {
        removerAlunoPorRGM(&((*raiz)->esq), rgm);
    } else if (rgm > (*raiz)->dado.rgm) {
        removerAlunoPorRGM(&((*raiz)->dir), rgm);
    } else {
        // Encontrou o nó a ser removido
        t_no *no = *raiz;

        // Caso 1: Sem filhos
        if (no->esq == NULL && no->dir == NULL) {
            printf("Aluno com RGM %d removido com sucesso.\n", no->dado.rgm);
            free(no);
            *raiz = NULL;
        }

        // Caso 2: Um filho à direita
        else if (no->esq == NULL) {
            printf("Aluno com RGM %d removido com sucesso.\n", no->dado.rgm);
            *raiz = no->dir;
            free(no);
        }

        // Caso 2: Um filho à esquerda
        else if (no->dir == NULL) {
            printf("Aluno com RGM %d removido com sucesso.\n", no->dado.rgm);
            *raiz = no->esq;
            free(no);
        }

        // Caso 3: Dois filhos
        else {
            t_no *sucessor = encontrarSucessor(no->dir);
            no->dado = sucessor->dado;
            removerAlunoPorRGM(&(no->dir), sucessor->dado.rgm);
        }
    }
}

void listagemPreOrdem(t_no * raiz) {
  if (raiz != NULL && raiz->dado.rgm >= 0) {
    printf("%d - %s\n", raiz->dado.rgm, raiz->dado.nome);
    listagemPreOrdem(raiz->esq);
    listagemPreOrdem(raiz->dir);
  }
}

void listagemInOrdem(t_no * raiz) {
  if (raiz != NULL && raiz->dado.rgm >= 0) {
    listagemInOrdem(raiz->esq);
    printf("%d - %s\n", raiz->dado.rgm, raiz->dado.nome);
    listagemInOrdem(raiz->dir);
  }
}

void listagemPosOrdem(t_no * raiz) {
  if (raiz != NULL && raiz->dado.rgm >= 0) {
    listagemPosOrdem(raiz->esq);
    listagemPosOrdem(raiz->dir);
    printf("%d - %s\n", raiz->dado.rgm, raiz->dado.nome);
  }
}

void listagemGraficamente(t_no * raiz, int espaco) {
  if (raiz == NULL || raiz->dado.rgm < 0) return;

  espaco += 12;
  listagemGraficamente(raiz->dir, espaco);

  printf("\n");
  for (int i = 12; i < espaco; i++) {
    printf(" ");
  }
  printf("%d - %s\n", raiz->dado.rgm, raiz->dado.nome);

  listagemGraficamente(raiz->esq, espaco);
}

void menuDeListagem(t_no * raiz) {
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

t_no * carregarArvoreDoArquivo(FILE * arquivo) {
  char linha[150];
  int rgm;
  char nome[80];

  t_no * raiz = criarNo();
  raiz->dado.rgm = -1;

  while (fgets(linha, sizeof(linha), arquivo) != NULL) {
    linha[strcspn(linha, "\n")] = '\0';

    // Lê a linha no formato "1234 - Nome do Aluno"
    if (sscanf(linha, "%d - %[^\n]", &rgm, nome) == 2) {
      if (raiz->dado.rgm == -1) {
        raiz->dado.rgm = rgm;
        strcpy(raiz->dado.nome, nome);
      } else {
        inserirNaArvore(rgm, nome, raiz);
      }
    }
  }

  if (raiz->dado.rgm == -1) {
    return NULL;
  }

  return raiz;
}

void menu() {
  FILE * arquivo = fopen("dados.txt", "r");

  if(arquivo == NULL) {
    arquivo = fopen("dados.txt", "w");
    if (arquivo == NULL) {
      printf("Erro ao criar o arquivo '%s'\n", "dados.txt");
      return 1;
    } else {
      printf("Arquivo '%s' criado com sucesso (estava ausente)\n", "dados.txt");
      fclose(arquivo);
      arquivo = fopen("dados.txt", "r");
    }
  }

  int opcao = 0, rgm = 0;
  char nome[80];
  t_no * raiz = carregarArvoreDoArquivo(arquivo);

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
      printf("Digite o nome: ");
      fflush(stdin);
      fgets(nome, sizeof(nome), stdin);
      nome[strcspn(nome, "\n")] = 0; // Remove o \n

      if(raiz == NULL) {
        raiz = criarNo();
        raiz->dado.rgm = rgm;
        strcpy(raiz->dado.nome, nome);
      }else {
        inserirNaArvore(rgm, nome, raiz);
      }

      printf("RGM %d - %s inserido com sucesso\n", rgm, nome);

      menu(arquivo);
      break;
    case 2:
      printf("------------------------------------\n");
      printf("REMOVER UM NO\n");
      
      if(raiz == NULL) {
        printf("Arvore vazia\n");
      } else {
        printf("Digite o RGM: ");
        scanf("%d", &rgm);
        removerAlunoPorRGM(&raiz, rgm);  // Chama a função remover RGM
      }

      menu(arquivo);
      break;
    case 3:

      printf("------------------------------------\n");
      printf("Pesquisar um Aluno\n");
      printf("Digite o RGM:");
      scanf("%d", &rgm);

      t_no * valorBuscado = pesquisaNo(rgm, raiz);

      if (valorBuscado == NULL)
        printf("RGM %d nao foi encontrado na lista de aluno\n", rgm);

      else
        printf("Nome %s - RGM: %d foi encontrado na lista de alunos\n", valorBuscado->dado.nome, valorBuscado->dado.rgm);


      menu(arquivo);
      break;
    case 4:
      printf("------------------------------------\n");
      printf("ESVAZIAR A ARVORE\n");
      break;
    case 5:
      menuDeListagem(raiz);
      menu(arquivo);
      break;
    case 0:
      printf("------------------------------------\n");
      printf("SAIR\n");
      break;
    default:
      printf("------------------------------------\n");
      printf("OPCAO INVALIDA\n");
      menu(arquivo);
      break;
  }
}

int main() {
  setlocale(LC_ALL, "Portuguese_Brazil");

  menu();

  return 0;
}