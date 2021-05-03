#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct user User;

struct user {
  long long cpf;
  long int senha;

  char status;
};


User* preencheUser(void);
void exibeUser(User*);
int menuPrincipal(void);
void gravaUser(User*);
User* buscaUser(void);

int menuPrincipal(void) {
  int op;
  printf("\nMenu Principal\n");
  printf("1 - Cadastrar Usuário\n");
  printf("2 - Pesquisar Usuário\n");
  scanf("%d", &op);
  return op;
}

int main(void) {
  User* fulano;
  char opcao;
  printf("Programa Cadastro de User\n\n");
  opcao = menuPrincipal();
  while (opcao != 0) {
    switch (opcao) {
      case 1 :  fulano = preencheUser();
                gravaUser(fulano);
                break;
      case 2 :  fulano = buscaUser();
                exibeUser(fulano);
                break;
    }
    opcao = menuPrincipal();
  }
  free(fulano);
  return 0;
}


User* preencheUser(void) {
  User* aln;
  aln = (User*) malloc(sizeof(User));
  printf("\nInforme seu CPF: ");
  scanf("%lld", &aln->cpf);
  printf("Senha: ");
  scanf("%ld", &aln->senha);
  aln->status = 'm';
  return aln;
}


void exibeUser(User* al) {
  char situacao[20];
  if ((al == NULL) || (al->status == 'x')) {
    printf("\n= = = Usuário Inexistente = = =\n");
  } else {
    printf("\n= = = Usuário Cadastrado = = =\n");
    printf("CPF: %lld\n", al->cpf);
    getchar();
    printf("senha: %ld\n", al->senha);
    getchar();

    if (al->status == 'm') {
      strcpy(situacao, "Usuário Ativo");
    } else if (al->status == 't') {
      strcpy(situacao, "Trancado");
    } else {
      strcpy(situacao, "Não informada");
    }
    printf("Situação do Usuário: %s\n", situacao);
  }
}



void gravaUser(User* aln) {
  FILE* fp;
  fp = fopen("User.dat", "ab");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar este programa...\n");
    exit(1);
  }
  fwrite(aln, sizeof(User), 1, fp);
  fclose(fp);
}


User* buscaUser(void) {
  FILE* fp;
  User* aln;
  long long id;
  int auxSenha;
  printf("\n = Busca Usuário = \n"); 
  printf("Informe seu CPF: "); 
  scanf("%lld", &id);
  printf("Informe sua senha: "); 
  scanf("%d", &auxSenha);
  aln = (User*) malloc(sizeof(User));
  fp = fopen("User.dat", "rb");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar este programa...\n");
    exit(1);
  }
  while(!feof(fp)) {
    fread(aln, sizeof(User), 1, fp);
    if ((aln->cpf == id) && (aln->senha == auxSenha) && (aln->status != 'x')) {
      fclose(fp);
      return aln;
    }
  }
  fclose(fp);
  return NULL;
}
