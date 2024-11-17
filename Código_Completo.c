#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 

#define MAX_CRIPTOMOEDAS 100
#define MAX_INVESTIDORES 100

// Estrutura para criptomoedas
typedef struct {
    char nome[50];
    float cotacao_inicial;
    float taxa_compra;
    float taxa_venda;
} Criptomoeda;

Criptomoeda criptomoedas[MAX_CRIPTOMOEDAS];
int total_criptomoedas = 0;

// Dados administrador
const char cpf_gerente[] = "51616468882";
const char senha_gerente[] = "admin1";

// Dados investidores
char cpfs[10][12] = {
    "12345678910",
    "22124085611",
    "52124009312",
    "22124071613"
};
char senhas[10][7] = {
    "123456",
    "234567",
    "345678",
    "456789"
};
char nomes[10][20] = {
    "Analiza Julia",
    "Ana Lima",
    "Elizabeth Kruger",
    "Julia Barreto"
};
// Saldos dos investidores
float reais[10] = {0.00, 0.00, 0.00, 0.00};
float bitcoin[10] = {0.00, 0.00, 0.00, 0.00};
float ethereum[10] = {0.00, 0.00, 0.00, 0.00};
float ripple[10] = {0.00, 0.00, 0.00, 0.00};
int total_investidores = 4;

void clear_buffer();
void cadastrar_investidor();
void excluir_investidor();
void menu_gerente();
void efetuar_login();
void menu_completo(int cliente);
void consultar_saldo(int cliente);
void cadastrar_criptomoedas();
void excluir_criptomoeda();
void consultar_saldo_geral();

// Função para limpar o buffer
void clear_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
// Cadastrar investidores
void cadastrar_investidor() {
    if (total_investidores >= MAX_INVESTIDORES) {
        printf("Não é possível cadastrar novos investidores.\n");
        return;
    }
    printf("Digite o CPF do novo investidor: ");
    scanf("%s", cpfs[total_investidores]);
    printf("Digite a senha do novo investidor: ");
    scanf("%s", senhas[total_investidores]);
    printf("Digite o nome do novo investidor: ");
    scanf(" %[^\n]%*c", nomes[total_investidores]);
    reais[total_investidores] = 0.0;
    bitcoin[total_investidores] = 0.0;
    ethereum[total_investidores] = 0.0;
    ripple[total_investidores] = 0.0;
    total_investidores++;
    printf("Investidor cadastrado.\n");
}
// Excluir investidores
void excluir_investidor() {
    char cpf_excluir[12];
    printf("Digite o CPF do investidor a ser deletado: ");
    scanf("%11s", cpf_excluir);  

    int encontrado = -1;
    for (int i = 0; i < total_investidores; i++) {
        if (strcmp(cpfs[i], cpf_excluir) == 0) {
            encontrado = i;
            break;
        }
    }
    if (encontrado == -1) {
        printf("O Investidor não existe.\n");
        return;
    }

    for (int i = encontrado; i < total_investidores - 1; i++) {
        strcpy(cpfs[i], cpfs[i + 1]);
        strcpy(senhas[i], senhas[i + 1]);
        strcpy(nomes[i], nomes[i + 1]);
        reais[i] = reais[i + 1];
        bitcoin[i] = bitcoin[i + 1];
        ethereum[i] = ethereum[i + 1];
        ripple[i] = ripple[i + 1];
    }

    total_investidores--;
    printf("Investidor excluído.\n");
}

// Menu gerente
void menu_gerente() {
    int opcao;
    while (1) {
        printf("==----------------------------==\n");
        printf("Menu: \n");
        printf("1. Cadastrar novo investidor\n");
        printf("2. Excluir investidor\n");
        printf("3. Cadastrar criptomoedas\n");
        printf("4. Excluir criptomoedas\n");
        printf("5. Consultar saldo geral\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrar_investidor();
                break;
            case 2:
                excluir_investidor();
                break;
            case 3:
                cadastrar_criptomoedas();
                break;
            case 4:
                excluir_criptomoeda();
                break;
            case 5:
                break;
            case 6:
                printf("==----------------------------==\n");
                return; // Retorna
            default:
                printf("Opção inválida.\n");
        }
    }
}

// Consultar saldo investidor
void consultar_saldo(int cliente) {
    char senha_acesso_saldo[7]; 
    while (1) {  // Laço de validação
        printf("Digite sua senha: ");
        scanf("%s", senha_acesso_saldo);
        if (strcmp(senhas[cliente], senha_acesso_saldo) == 0) {
            printf("==----------------------------==\n");
            printf("Nome: %s\n", nomes[cliente]);
            printf("CPF: %c%c%c.%c%c%c.%c%c%c-%c%c\n", // Formatação do CPF
                cpfs[cliente][0], cpfs[cliente][1], cpfs[cliente][2],
                cpfs[cliente][3], cpfs[cliente][4], cpfs[cliente][5],
                cpfs[cliente][6], cpfs[cliente][7], cpfs[cliente][8],
                cpfs[cliente][9], cpfs[cliente][10]);
            printf("\nReais (R$): %.2f\n", reais[cliente]);
            printf("Bitcoin (BTC): %.6f\n", bitcoin[cliente]);
            printf("Ethereum (ETH): %.6f\n", ethereum[cliente]);
            printf("Ripple (XRP): %.6f\n", ripple[cliente]);
            return;
        } else {
            printf("Senha incorreta. Digite novamente.\n");
        }
    }
}


// Cadastrar criptomoedas
void cadastrar_criptomoedas() {
    if (total_criptomoedas >= MAX_CRIPTOMOEDAS) {
        printf("Limite de criptomoedas atingido.\n");
        return;
    }

    Criptomoeda nova;
    printf("Digite o nome da criptomoeda: ");
    scanf(" %[^\n]", nova.nome);
    printf("Digite a cotação inicial: ");
    scanf("%f", &nova.cotacao_inicial);
    printf("Digite a taxa de compra: ");
    scanf("%f", &nova.taxa_compra);
    printf("Digite a taxa de venda: ");
    scanf("%f", &nova.taxa_venda);

    criptomoedas[total_criptomoedas] = nova;
    total_criptomoedas++;
    printf("Criptomoeda cadastrada com sucesso!\n");
}

// Excluir criptomoeda
void excluir_criptomoeda() {
    char nome_excluir[50];
    printf("Digite o nome da criptomoeda: ");
    scanf(" %[^\n]", nome_excluir);
    int encontrado = -1;
    for (int i = 0; i < total_criptomoedas; i++) {
        if (strcmp(criptomoedas[i].nome, nome_excluir) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("Criptomoeda não encontrada.\n");
        return;
    }
    for (int i = encontrado; i < total_criptomoedas - 1; i++) {
        criptomoedas[i] = criptomoedas[i + 1];
    }
    total_criptomoedas--;
    printf("Criptomoeda excluída com sucesso.\n");
}



void salvar_saldos() {
    FILE *arquivo = fopen("saldos.bin", "wb");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo para salvar os saldos");
        return;
    }
    fwrite(reais, sizeof(float), 4, arquivo);
    fwrite(bitcoin, sizeof(float), 4, arquivo);
    fwrite(ethereum, sizeof(float), 4, arquivo);
    fwrite(ripple, sizeof(float), 4, arquivo);
    fclose(arquivo);
}

void carregar_saldos() {
    FILE *arquivo = fopen("saldos.bin", "rb");
    if (arquivo == NULL) {
        return;
    }
    fread(reais, sizeof(float), 4, arquivo);
    fread(bitcoin, sizeof(float), 4, arquivo);
    fread(ethereum, sizeof(float), 4, arquivo);
    fread(ripple, sizeof(float), 4, arquivo);
    fclose(arquivo);
}

void salvar_dados(int cliente, char operacao, float valor, const char* qual_moeda, const char* cotacao, float valor_cotacao, const char* taxa, float valor_taxa, float valor_reais, float valor_bitcoin, float valor_ethereum, float valor_ripple) {
    FILE *dados = fopen("dados_arq.bin", "ab");
    if (dados == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    char cpf_cliente[12];
    strncpy(cpf_cliente, cpfs[cliente], sizeof(cpf_cliente));

    // Gravar dados
    fwrite(&tm, sizeof(tm), 1, dados);
    fwrite(&operacao, sizeof(char), 1, dados);
    fwrite(&valor, sizeof(float), 1, dados);
    fwrite(cpf_cliente, sizeof(char), sizeof(cpf_cliente), dados); // Grava o CPF
    fwrite(qual_moeda, sizeof(char), 10, dados); // Tamanho fixo
    fwrite(cotacao, sizeof(char), 10, dados); // Tamanho fixo
    fwrite(&valor_cotacao, sizeof(float), 1, dados);
    fwrite(taxa, sizeof(char), 10, dados); // Tamanho fixo
    fwrite(&valor_taxa, sizeof(float), 1, dados);
    fwrite(&valor_reais, sizeof(float), 1, dados);
    fwrite(&valor_bitcoin, sizeof(float), 1, dados);
    fwrite(&valor_ethereum, sizeof(float), 1, dados);
    fwrite(&valor_ripple, sizeof(float), 1, dados);

    fclose(dados);
}

void ler_dados(int cliente) {
    FILE *dados = fopen("dados_arq.bin", "rb");
    if (dados == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    struct tm tm; // Estrutura para armazenar informações de data/hora
    char operacao, cpf_cliente[12];
    float valor, valor_cotacao, valor_taxa, valor_reais, valor_bitcoin, valor_ethereum, valor_ripple;
    char qual_moeda[10], cotacao[10], taxa[10];

    // Lê o arquivo até que não haja mais dados
    while (fread(&tm, sizeof(tm), 1, dados) == 1) {
        fread(&operacao, sizeof(char), 1, dados);
        fread(&valor, sizeof(float), 1, dados);
        fread(cpf_cliente, sizeof(char), sizeof(cpf_cliente), dados); // Lê o CPF
        fread(qual_moeda, sizeof(char), sizeof(qual_moeda), dados);
        fread(cotacao, sizeof(char), sizeof(cotacao), dados);
        fread(&valor_cotacao, sizeof(float), 1, dados);
        fread(taxa, sizeof(char), sizeof(taxa), dados);
        fread(&valor_taxa, sizeof(float), 1, dados);
        fread(&valor_reais, sizeof(float), 1, dados);
        fread(&valor_bitcoin, sizeof(float), 1, dados);
        fread(&valor_ethereum, sizeof(float), 1, dados);
        fread(&valor_ripple, sizeof(float), 1, dados);

        // Verifica se o CPF corresponde ao cliente logado
        if (strcmp(cpf_cliente, cpfs[cliente]) == 0) {
            printf("Data: %02d-%02d-%d %02d:%02d\n", 
                   tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, 
                   tm.tm_hour, tm.tm_min);
            printf("Operação: %c \tValor: %.2f\n", operacao, valor);
            printf("Moeda: %s \tCotação: %.2f\n", qual_moeda, valor_cotacao);
            printf("Taxa: %.2f\n", valor_taxa);
            printf("Reais: %.2f \tBitcoin: %.2f \tEthereum: %.2f \tRipple: %.2f\n", 
                   valor_reais, valor_bitcoin, valor_ethereum, valor_ripple);
            printf("--------------------------------------------------------------\n");
        }
    }

    fclose(dados);
}


void extrato(int cliente) {
    char senha1[7];
    printf("Digite sua senha: ");
    scanf("%s", senha1);

    if (strcmp(senha1, senhas[cliente]) == 0) {
        printf("--------------------------------------------------------------\n");
        printf("Extrato de %s:\n", nomes[cliente]);
        ler_dados(cliente);
    } else {
        printf("Senha incorreta. Digite novamente.\n");
    }
}


void depositar(int cliente) {
    float v_d;

    printf("Valor do depósito (R$): ");
    scanf("%f", &v_d);
    reais[cliente] += v_d; // Atualiza o saldo
    printf("Depósito realizado. Saldo atual: R$ %.2f\n", reais[cliente]);

    // Grava os dados do depósito
    salvar_dados(cliente,'+', v_d, "REAL", "COT", 0.0, "TAXA", 0.0, reais[cliente], bitcoin[cliente], ethereum[cliente], ripple[cliente]);
}

void sacar(int cliente) {
    char senha1[7];
    float v_s;
    printf("Digite sua senha: ");
    scanf("%s", senha1);

    if (strcmp(senha1, senhas[cliente]) == 0) {
        printf("Valor do saque (R$): ");
        scanf("%f", &v_s);

        if (v_s > reais[cliente]) {
            printf("Saldo inferior ao saque solicitado.\n");
        } else {
            reais[cliente] -= v_s; // Atualiza o saldo
            printf("Saque realizado. Saldo atual: R$ %.2f\n", reais[cliente]);
        }
    } else {
        printf("Senha incorreta. Digite novamente.\n");
    }
    salvar_dados(cliente,'-', v_s, "REAL", "COT", 0.0, "TAXA", 0.0, reais[cliente], bitcoin[cliente], ethereum[cliente], ripple[cliente]);

}

// Menu investidor
void menu_completo(int cliente) {
    int opcao;
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
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                consultar_saldo(cliente);
                break;
            case 2:
                extrato(cliente);
                break;
            case 3:
                depositar(cliente);
                break;
            case 4:
                sacar(cliente);
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                return; 
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    }
}

// Função de login
void efetuar_login() {
    char cpf_login[12];
    char senha_login[7];
    printf("Digite seu CPF: ");
    scanf("%s", cpf_login);
    printf("Digite sua senha: ");
    scanf("%s", senha_login);
    // Verifica login administrador
    if (strcmp(cpf_login, cpf_gerente) == 0 && strcmp(senha_login, senha_gerente) == 0) {
        printf("Acesso concedido ao menu de gerenciamento.\n");
        menu_gerente();
        return;
    }
// Verifica login investidores 
    for (int i = 0; i < total_investidores; i++) {
        if (strcmp(cpfs[i], cpf_login) == 0 && strcmp(senhas[i], senha_login) == 0) {
            printf("Bem-vindo, %s!\n", nomes[i]);
            menu_completo(i);
            return;
        }
    }

    printf("CPF ou senha inválidos.\n");
}
// Função principal
int main() {
    carregar_saldos();
    while (1) { 
        efetuar_login();
        int opcao;
        printf("Deseja fazer um novo login? (1. Sim / 2. Não): ");
        scanf("%d", &opcao);
        if (opcao == 2) {
            printf("==----------------------------==\n");
            break; 
        }
    }
    return 0;
}
