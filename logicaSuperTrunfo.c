#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Função para mudar a codificação para UTF-8 no CMD
void configurar_codificacao() {
    system("chcp 65001"); // Altera a codificação para UTF-8
}

// Estrutura para armazenar os dados das cidades
typedef struct {
    char estado[3];
    char codigo[10];
    char nome[50];
    int populacao;
    double pib;
    double area;
    int pontos_turisticos;
    float densidade;
    float pib_per_capita;
} Cidade;

// Função para calcular densidade populacional e PIB per capita
void calcular_propriedades(Cidade* c) {
    if (c->area > 0) {
        c->densidade = c->populacao / c->area;
    }
    else {
        c->densidade = 0; // Se a área for zero ou negativa, define densidade como 0
    }

    if (c->populacao > 0) {
        c->pib_per_capita = c->pib / c->populacao;
    }
    else {
        c->pib_per_capita = 0; // Se a população for zero ou negativa, define PIB per capita como 0
    }
}

// Função para registrar uma cidade
void registrar_cidade(Cidade* c) {
    printf("\nDigite o estado (sigla, ex: MG): ");
    if (scanf("%2s", c->estado) != 1) {
        printf("Erro ao ler o estado!\n");
        exit(1);
    }
    printf("Digite o codigo da cidade: ");
    if (scanf("%9s", c->codigo) != 1) {
        printf("Erro ao ler o código da cidade!\n");
        exit(1);
    }
    printf("Digite o nome da cidade: ");
    getchar(); // Consumir o '\n' pendente
    if (fgets(c->nome, sizeof(c->nome), stdin) == NULL) {
        printf("Erro ao ler o nome da cidade!\n");
        exit(1);
    }
    c->nome[strcspn(c->nome, "\n")] = 0; // Remover o '\n' do fgets
    printf("Digite a população: ");
    if (scanf("%d", &c->populacao) != 1) {
        printf("Erro ao ler a população!\n");
        exit(1);
    }
    printf("Digite o PIB (em bilhões): ");
    if (scanf("%lf", &c->pib) != 1) {
        printf("Erro ao ler o PIB!\n");
        exit(1);
    }
    printf("Digite a área (km²): ");
    if (scanf("%lf", &c->area) != 1) {
        printf("Erro ao ler a área!\n");
        exit(1);
    }
    printf("Digite o número de pontos turísticos: ");
    if (scanf("%d", &c->pontos_turisticos) != 1) {
        printf("Erro ao ler o número de pontos turísticos!\n");
        exit(1);
    }

    calcular_propriedades(c);
}

// Função para exibir os dados de uma cidade
void exibir_cidade(Cidade c) {
    printf("\nCarta:\n");
    printf("Estado: %s\n", c.estado);
    printf("Código: %s\n", c.codigo);
    printf("Nome da Cidade: %s\n", c.nome);
    printf("População: %d\n", c.populacao);
    printf("Área: %.2f km²\n", c.area);
    printf("PIB: %.2f bilhões de reais\n", c.pib);
    printf("Número de Pontos Turísticos: %d\n", c.pontos_turisticos);
    printf("Densidade Populacional: %.2f hab/km²\n", c.densidade);
    printf("PIB per Capita: %.2f reais\n", c.pib_per_capita);
}

// Função para comparar os atributos escolhidos
void comparar_atributos(Cidade c1, Cidade c2, int atributo1, int atributo2) {
    double soma1 = 0, soma2 = 0;

    // Comparação para o primeiro atributo escolhido
    if (atributo1 == 1) { // PIB per capita
        soma1 += c1.pib_per_capita;
        soma2 += c2.pib_per_capita;
    }
    else if (atributo1 == 2) { // Densidade Populacional
        soma1 += c1.densidade;
        soma2 += c2.densidade;
    }

    // Comparação para o segundo atributo escolhido
    if (atributo2 == 1) { // PIB per capita
        soma1 += c1.pib_per_capita;
        soma2 += c2.pib_per_capita;
    }
    else if (atributo2 == 2) { // Densidade Populacional
        soma1 += c1.densidade;
        soma2 += c2.densidade;
    }

    // Ajuste caso um dos atributos seja densidade (menor é melhor)
    if (atributo1 == 2) {
        soma1 = c1.densidade < c2.densidade ? soma1 : soma2;
    }

    if (atributo2 == 2) {
        soma2 = c2.densidade < c1.densidade ? soma2 : soma1;
    }

    // Exibição do vencedor
    if (soma1 > soma2) {
        printf("\nCarta 1 (%s) venceu! (Soma dos atributos: %.2f)\n", c1.nome, soma1);
    }
    else if (soma1 < soma2) {
        printf("\nCarta 2 (%s) venceu! (Soma dos atributos: %.2f)\n", c2.nome, soma2);
    }
    else {
        printf("\nEmpate! (Soma dos atributos: %.2f)\n", soma1);
    }
}

int main() {
    // Configura a codificação UTF-8
    configurar_codificacao();

    Cidade carta1, carta2;
    int atributo1, atributo2;

    // Cadastro das cartas
    printf("Cadastro da Carta 1:\n");
    registrar_cidade(&carta1);
    printf("\nCadastro da Carta 2:\n");
    registrar_cidade(&carta2);

    // Exibir as cartas cadastradas
    printf("\nCartas cadastradas:\n");
    exibir_cidade(carta1);
    exibir_cidade(carta2);

    // Escolher atributos para comparação
    do {
        printf("\nEscolha o primeiro atributo para comparar (1 = PIB per capita, 2 = Densidade Populacional): ");
        if (scanf("%d", &atributo1) != 1) {
            printf("Erro ao ler a escolha do primeiro atributo!\n");
            exit(1);
        }
    } while (atributo1 != 1 && atributo1 != 2);

    do {
        printf("Escolha o segundo atributo para comparar (1 = PIB per capita, 2 = Densidade Populacional): ");
        if (scanf("%d", &atributo2) != 1) {
            printf("Erro ao ler a escolha do segundo atributo!\n");
            exit(1);
        }
    } while (atributo2 != 1 && atributo2 != 2 && atributo1 != atributo2);

    // Comparar os atributos escolhidos
    comparar_atributos(carta1, carta2, atributo1, atributo2);

    return 0;
}
