#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_INVESTIDORES 50

typedef struct {
  char nome[50];
  char cpf[12];
  char senha[7];
  float saldo_reais;
} Investidor;

Investidor investidores1[MAX_INVESTIDORES];
int total_investidores = 0; // Total de investidores carregados

void clear_buffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

//void depositar(int indice_investidor){
//  printf("Digite o valor a ser depositado: ");
//  scanf("%f",&investidores[indice_investidor].saldo_reais)
//}


// Função para pegar dados do arquivo de texto
void carregar_dados_txt_investidor() {
  FILE *arquivo = fopen("investidores.txt", "r");
  if (arquivo == NULL) {
    printf("Arquivo de investidores não encontrado. Nenhum investidor "
           "carregado.\n");
    return;
  }

  total_investidores = 0;
  while (fscanf(arquivo, "%s %s %s %f",
                investidores1[total_investidores].nome,
                investidores1[total_investidores].cpf,
                investidores1[total_investidores].senha,
                &investidores1[total_investidores].saldo_reais) == 4) {
    total_investidores++;
    if (total_investidores >= MAX_INVESTIDORES) {
      break;
    }
  }

  fclose(arquivo);
  printf("%d investidores carregados do arquivo.\n", total_investidores);
}

// Função de consulta de saldo
void consultar_saldo(int indice_investidor) {
  char senha_acesso_saldo[7]; // 6 dígitos + 1 para o caractere nulo
  // Laço de validação
  while (1) {
    printf("==----------------------------==\n");
    printf("Digite sua senha: ");
    scanf("%s", senha_acesso_saldo);
    if (strcmp(investidores1[indice_investidor].senha, senha_acesso_saldo) ==
        0) {
      printf("==----------------------------==\n");
      printf("Nome: %s\n", investidores1[indice_investidor].nome);
      printf("CPF: %c%c%c.%c%c%c.%c%c%c-%c%c\n", // Formatação do CPF
             investidores1[indice_investidor].cpf[0],
             investidores1[indice_investidor].cpf[1],
             investidores1[indice_investidor].cpf[2],
             investidores1[indice_investidor].cpf[3],
             investidores1[indice_investidor].cpf[4],
             investidores1[indice_investidor].cpf[5],
             investidores1[indice_investidor].cpf[6],
             investidores1[indice_investidor].cpf[7],
             investidores1[indice_investidor].cpf[8],
             investidores1[indice_investidor].cpf[9],
             investidores1[indice_investidor].cpf[10]);
      printf("\nReais (R$): %.2f\n",
             investidores1[indice_investidor].saldo_reais);
      return;
    } else {
      printf("Senha incorreta. Digite novamente.\n");
    }
  }
}

// Núcleo da lógica de interação
void menu_completo(int indice_investidor) {
  int opcao_menu;
  // Laço infinito até que o cliente decida deslogar
  while (1) {
    printf("==----------------------------==\n");
    printf("Menu: \n");
    printf("1. Consultar saldo\n");
    printf("2. Consultar extrato\n");
    printf("3. Depositar\n");
    printf("4. Sacar\n");
    printf("5. Comprar criptomoedas\n");
    printf("6. Vender criptomoedas\n");
    printf("7. Atualizar cotação\n");
    printf("8. Sair\n");
    printf("==----------------------------==\n");
    printf("Escolha sua opção: ");
    scanf("%d", &opcao_menu);
    // Executa a operação escolhida
    switch (opcao_menu) {
    case 1:
      consultar_saldo(indice_investidor);
      break;
    case 2:
      break;
    case 3:
      break;
    case 4:
      break;
    case 5:
      break;
    case 6:
      break;
    case 7:
      break;
    case 8:
      return; // Sai do laço e retorna à função 'efetuar_login'
    default:
      printf("Opção inválida. Tente novamente.\n");
      break;
    }
  }
}

void encerrar_programa() {
  printf("==--------------------------------------------------==\n");
  printf("Encerrando o Programa. Obrigado por trabalhar conosco!\n");
  printf("==--------------------------------------------------==\n");
  exit(0);
}

void efetuar_login() {
  char cpf_login[12];  // 11 dígitos + 1 para o caractere nulo
  char senha_login[7]; // 6 dígitos + 1 para o caractere nulo
  int opcao_login;
  int indice_investidor = -1;
  // Laço infinito para o processo de login dos clientes
  while (1) {
    printf("==--------------------------------------==\n");
    printf("Seja bem-vindo à Exchange de Criptomoedas!\n");
    printf("1 - Efetuar Login\n");
    printf("2 - Sair\n");
    printf("==--------------------------------------==\n");
    printf("Por favor, selecione a opção desejada: ");
    scanf("%d", &opcao_login);
    clear_buffer();

    if (opcao_login == 2) {
      encerrar_programa(); // Saída
    } else if (opcao_login != 1) {
      printf("Opção irreconhecível. Tente novamente.\n");
    } else {
      printf("Digite seu CPF (Somente números): ");
      scanf("%s", cpf_login);
      printf("Digite sua senha (Somente números): ");
      scanf("%s", senha_login);

      for (int i = 0; i < total_investidores; i++) {
        if (strcmp(investidores1[i].cpf, cpf_login) == 0 &&
            strcmp(investidores1[i].senha, senha_login) == 0) {
          indice_investidor = i;
          break;
        }
      }

      if (indice_investidor != -1) {
        printf("==--------------------------------------==\n");
        printf("É bom te ter de volta, %s :)\n",
               investidores1[indice_investidor].nome);
        menu_completo(indice_investidor);
        return;
      } else {
        printf("CPF ou senha inválidos. Tente novamente.\n");
      }
    }
  }
}

int main_investidor() {
  carregar_dados_txt_investidor();
  while (1) {
    efetuar_login();
  }
  return 0;
}
